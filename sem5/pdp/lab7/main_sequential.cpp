#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-exception-baseclass"
#include "utils.h"
#include "iostream"
#include "mpl.hpp"
#include "naive_polynomial_multiplication.h"

int main() {
    const mpl::communicator &comm_world(mpl::environment::comm_world());
    if (comm_world.size() < 2) comm_world.abort(EXIT_FAILURE);

    if (comm_world.rank() == 0) {
        Polynomial p0 = getRandomPolynomial(500, 1, 60);
        Polynomial p1 = getRandomPolynomial(500, 1, 60);
        Polynomial result;

        const auto& a = p0.getCoefficients();
        const auto& b = p1.getCoefficients();

        int workerCount = comm_world.size() - 1;
        int start = 0, stop = 0;
        int taskSize = b.size() / workerCount;
        int rem = b.size() % workerCount;
        for(int i = 1; i <= workerCount; i++) {
            stop = start + taskSize;
            if (rem) {
                stop += 1;
                rem -= 1;
            }
            comm_world.send(a, i);
            comm_world.send(b, i);
            comm_world.send(start, i);
            comm_world.send(stop, i);
        }
        std::vector<int> finalCoefficients(a.size() + b.size() - 1, 0);
        for(int i = 1; i <= workerCount; i++) {
            std::vector<int> partialCoefficients;
            comm_world.recv(partialCoefficients, i);
            for(int j = 0; j < finalCoefficients.size(); j++) {
                finalCoefficients[j] += partialCoefficients[j];
            }
        }
        printPolynomial(Polynomial(finalCoefficients));
    }
    else {
        std::vector<int> a;
        std::vector<int> b;
        int start, stop;
        comm_world.recv(a, 0);
        comm_world.recv(b, 0);
        comm_world.recv(start, 0);
        comm_world.recv(stop, 0);
        std::vector<int> result(a.size() + b.size() - 1, 0);
        multiplicationTask(a, b, result, start, stop);
        comm_world.send(result, 0);
    }
    return EXIT_SUCCESS;
}

#pragma clang diagnostic pop