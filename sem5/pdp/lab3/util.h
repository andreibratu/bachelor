//
// Created by bratu on 10/20/2020.
//

#ifndef LAB3_UTIL_H
#define LAB3_UTIL_H

#include <iostream>
#include <random>
#include "matrix_multiply.h"

bool deep_equal(const Matrix &a, const Matrix &b)
{
    if (a.size() != b.size() || a[0].size() != b[0].size())
        return false;
    for(int i = 0; i < a.size(); i++)
    {
        for(int j = 0; j < a[0].size(); j++)
        {
            if (a[i][j] != b[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

void print_matrix(const Matrix &a)
{
    for(int i = 0; i < a.size(); i++)
    {
        for(int j = 0; j < a[0].size(); j++)
        {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

Matrix make_result_matrix(const Matrix &a, const Matrix &b)
{
    assert(a[0].size() == b.size());
    return Matrix(a.size(), std::vector<double>(b[0].size(), 0));
}

    double make_random_double(double lo, double hi)
    {
        double f = (double)rand() / RAND_MAX; // NOLINT(cert-msc50-cpp)
        return lo + f * (hi - lo);
    }

Matrix make_random_matrix(int h, int w)
{
    Matrix matrix(h, std::vector<double>(w, 0));
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            matrix[i][j] = make_random_double(-50, 50);
        }
    }
    return matrix;
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

#endif //LAB3_UTIL_H
