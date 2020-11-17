#include <iostream>
#include "naive_polynomial_multiplication.h"
#include "utils.h"
#include "karatsuba_polynomial_multiplication.h"

int main() {
    double executionTime = 0;
    double time = 0;
    double mean;
    int trials = 1000;
    Polynomial p0 = getRandomPolynomial(4, 1, 60);
    Polynomial p1 = getRandomPolynomial(4, 1, 60);
    Polynomial result;

    for(int thread_count = 1; thread_count <= 10; thread_count++) {
        executionTime = 0;
        std::vector<double> timings;
        timings.reserve(trials);
        if (thread_count == 1)
            std::cout << "SEQUENTIAL NAIVE\n";
        else
            std::cout << "PARALLEL NAIVE " << thread_count << "\n";
        for(int i = 0; i < trials; i++) {
            time = time_execution_seconds([&p0, &p1, &result, thread_count](){
                result = naiveParallelMultiplication(p0, p1, thread_count);
            });
            executionTime += time;
            timings.push_back(time);
        }
        mean = executionTime / trials;
        std::cout << "AVERAGE " << mean << " VARIANCE " << calculate_variance(timings, mean) << '\n';
        printPolynomial(result);
    }

    std::cout << "KARATSUBA SEQUENTIAL\n";
    executionTime = 0;
    std::vector<double> timings;
    timings.reserve(trials);
    for(int i = 0; i < trials; i++) {
        time = time_execution_seconds([&p0, &p1, &result](){
            result = karatsubaSequentialMultiplication(p0, p1);
        });
        executionTime += time;
        timings.push_back(time);
    }
    mean = executionTime / trials;
    std::cout << "AVERAGE " << mean << " VARIANCE " << calculate_variance(timings, mean) << '\n';
    printPolynomial(result);

    std::cout << "KARATSUBA PARALLEL\n";
    executionTime = 0;
    timings.resize(0);
    for(int i = 0; i < trials; i++) {
        time = time_execution_seconds([&p0, &p1, &result](){
            result = karatsubaParallelMultiplication(p0, p1, 5);
        });
        executionTime += time;
        timings.push_back(time);
    }
    mean = executionTime / trials;
    std::cout << "AVERAGE " << mean << " VARIANCE " << calculate_variance(timings, mean) << '\n';
    printPolynomial(result);

    return 0;
}
