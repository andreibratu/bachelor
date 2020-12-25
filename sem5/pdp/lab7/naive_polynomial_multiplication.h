//
// Created by bratu on 11/14/2020.
//

#ifndef LAB5_NAIVE_POLYNOMIAL_MULTIPLICATION_H
#define LAB5_NAIVE_POLYNOMIAL_MULTIPLICATION_H

#include <thread>
#include "Polynomial.h"

void multiplicationTask(
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


#endif //LAB5_NAIVE_POLYNOMIAL_MULTIPLICATION_H
