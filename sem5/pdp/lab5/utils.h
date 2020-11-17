//
// Created by bratu on 11/14/2020.
//

#ifndef LAB5_UTILS_H
#define LAB5_UTILS_H

#include <ctime>
#include <functional>
#include <chrono>
#include "Polynomial.h"

inline bool isPowerOf2(uint32_t n) {
    return (n & (n - 1)) == 0;
}

void printPolynomial(const Polynomial& p) {
    std::vector<int> coefficients = p.getCoefficients();
    for(auto& x: coefficients) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

Polynomial getRandomPolynomial(uint32_t n, int min, int max) {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    while(!isPowerOf2(n)) n++;
    std::vector<int> coefficients;
    for(int i = 0; i<n; i++) {
        int currCoefficient = rand() % (max - min) + min; // NOLINT(cert-msc50-cpp)
        coefficients.push_back(currCoefficient);
    }
    return Polynomial(coefficients);
}

double time_execution_seconds(const std::function<void()>& func)
{
    auto start = std::chrono::system_clock::now();
    func();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    return elapsed_seconds.count();
}

double calculate_variance(const std::vector<double>& samples, double mean) {
    double variance = 0;
    for(auto& x : samples) {
        variance += (x - mean) * (x - mean);
    }
    return variance / (samples.size() - 1); // NOLINT(cppcoreguidelines-narrowing-conversions)
}

#endif //LAB5_UTILS_H
