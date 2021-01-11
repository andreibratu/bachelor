#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-exception-baseclass"
#include "utils.h"
#include "iostream"
#include "naive_polynomial_multiplication.h"

#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

namespace mpi = boost::mpi;

int main() {
    mpi::environment env;
    mpi::communicator comm_world;
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
            comm_world.send(i, 0, a);
            comm_world.send(i, 0, b);
            comm_world.send(i, 0, start);
            comm_world.send(i, 0, stop);
        }
        std::vector<int> finalCoefficients(a.size() + b.size() - 1, 0);
        for(int i = 1; i <= workerCount; i++) {
            std::vector<int> partialCoefficients;
            comm_world.recv(i, 0, partialCoefficients);
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
        comm_world.recv(0, 0, a);
        comm_world.recv(0, 0, b);
        comm_world.recv(0, 0, start);
        comm_world.recv(0, 0, stop);
        std::vector<int> result(a.size() + b.size() - 1, 0);
        multiplicationTask(a, b, result, start, stop);
        comm_world.send(0, 0, result);
    }
    return EXIT_SUCCESS;
}

#pragma clang diagnostic pop