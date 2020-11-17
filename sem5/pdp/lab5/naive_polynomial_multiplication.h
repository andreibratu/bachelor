//
// Created by bratu on 11/14/2020.
//

#ifndef LAB5_NAIVE_POLYNOMIAL_MULTIPLICATION_H
#define LAB5_NAIVE_POLYNOMIAL_MULTIPLICATION_H

#include <thread>
#include "Polynomial.h"

void threadMultiplicationTask(
        const std::vector<int> &a, const std::vector<int> &b,
        std::vector<int> &result, int start, int stop
) {
    for(int i = start; i < stop; i++) {
        for(int j = 0; j < a.size(); j++) {
            int prod = a[j] * b[i];
            result[i + j] += prod;
        }
    }
}

void multiplyPolyParallelNaive(
        const std::vector<int> &a,
        const std::vector<int> &b,
        std::vector<int> &result, int threadCount
) {
    int taskSize = b.size() / threadCount; // NOLINT(cppcoreguidelines-narrowing-conversions)
    int rem = b.size() % threadCount; // NOLINT(cppcoreguidelines-narrowing-conversions)

    int start = 0, stop = 0;
    std::vector<std::thread> threads;

    for(int i = 0; i < threadCount; i++) {
        stop = start + taskSize;
        if (rem) {
            stop += 1;
            rem -= 1;
        }
        threads.emplace_back(std::thread([&a, &b, &result, start, stop](){
            threadMultiplicationTask(a, b, result, start, stop);
        }));
        start = stop;
    }

    for(auto& thread: threads) thread.join();
}

Polynomial naiveParallelMultiplication(const Polynomial &A, const Polynomial &B, int numThreads) {
    auto a = A.getCoefficients();
    auto b = B.getCoefficients();
    auto result = std::vector<int>(a.size() + b.size() - 1, 0);
    multiplyPolyParallelNaive(a, b, result, numThreads);
    return Polynomial(result);
}

#endif //LAB5_NAIVE_POLYNOMIAL_MULTIPLICATION_H
