#include <iostream>
#include "utils.h"
#include "mpl.hpp"

int main() {
    double executionTime = 0;
    double time = 0;
    double mean;
    int trials = 1000;
    Polynomial p0 = getRandomPolynomial(12, 1, 60);
    Polynomial p1 = getRandomPolynomial(12, 1, 60);
    Polynomial result;

    const mpl::communicator &comm_world(mpl::environment::comm_world());
    int numWorkers = comm_world.size() - 1;

    if (numWorkers != 3) comm_world.abort(EXIT_FAILURE);

    if (comm_world.rank() == 0) {

    }
//    std::cout << "KARATSUBA SEQUENTIAL\n";
//    executionTime = 0;
//    std::vector<double> timings;
//    timings.reserve(trials);
//    for(int i = 0; i < trials; i++) {
//        time = time_execution_seconds([&p0, &p1, &result](){
//            result = karatsubaSequentialMultiplication(p0, p1);
//        });
//        executionTime += time;
//        timings.push_back(time);
//    }
//    mean = executionTime / trials;
//    std::cout << "AVERAGE " << mean << " VARIANCE " << calculate_variance(timings, mean) << '\n';
//    printPolynomial(result);
//
//    timings.resize(0);
//    for (int num_threads = 2; num_threads < 10; num_threads++) {
//        std::cout << "KARATSUBA PARALLEL " << num_threads << "\n";
//        executionTime = 0;
//        for(int i = 0; i < trials; i++) {
//            time = time_execution_seconds([&p0, &p1, &result](){
//                result = karatsubaParallelMultiplication(p0, p1, 6);
//            });
//            executionTime += time;
//            timings.push_back(time);
//        }
//        mean = executionTime / trials;
//        std::cout << "AVERAGE " << mean << " VARIANCE " << calculate_variance(timings, mean) << '\n';
//        printPolynomial(result);
//        timings.resize(0);
//    }
//    return 0;
}
