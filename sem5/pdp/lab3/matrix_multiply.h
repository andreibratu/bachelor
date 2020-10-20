//
// Created by bratu on 10/20/2020.
//

#ifndef LAB3_MATRIX_MULTIPLY_H
#define LAB3_MATRIX_MULTIPLY_H

#include <vector>
#include <cassert>
#include <iostream>
#include "ThreadPool.h"

typedef std::vector<std::vector<double>> Matrix;

void multiply(const Matrix &a, const Matrix &b, Matrix &result)
{
    int h_a = a.size();
    int w_a = a[0].size();
    int h_b = b.size();
    int w_b = b[0].size();
    assert(w_a == h_b);
    assert(result.size() == h_a && result[0].size() == w_b);

    for(int row_a_idx = 0; row_a_idx < h_a; row_a_idx++)
    {
        for(int col_b_idx = 0; col_b_idx < w_b; col_b_idx++)
        {
            for(int i = 0; i < w_a; i++)
            {
                result[row_a_idx][col_b_idx] += a[row_a_idx][i] * b[i][col_b_idx];
            }
        }
    }
}

void multiply_subtask(const Matrix &a, const Matrix &b, Matrix &result, int row_a_idx, int col_b_idx)
{
    int w_matrices = a[0].size();
    for(int i = 0; i < w_matrices; i++)
    {
        result[row_a_idx][col_b_idx] += a[row_a_idx][i] * b[i][col_b_idx];
    }
}

void multiply_parallel(const Matrix &a, const Matrix &b, Matrix& result)
{
    int h_a = a.size();
    int w_a = a[0].size();
    int h_b = b.size();
    int w_b = b[0].size();
    assert(w_a == h_b);
    assert(result.size() == h_a && result[0].size() == w_b);

    std::vector<std::thread> threads;
    for(int row_a_idx = 0; row_a_idx < h_a; row_a_idx++)
    {
        for(int col_b_idx = 0; col_b_idx < w_b; col_b_idx++)
        {
            threads.emplace_back([row_a_idx, col_b_idx, &a, &b, &result]()
            {
                multiply_subtask(a, b, result, row_a_idx, col_b_idx);
            });
        }
    }
    for (auto& thread: threads) { thread.join(); }
}

void multiply_parallel_pool(const Matrix &a, const Matrix &b, Matrix &result, std::unique_ptr<ThreadPool>& pool_pt)
{
    int h_a = a.size();
    int w_a = a[0].size();
    int h_b = b.size();
    int w_b = b[0].size();
    assert(w_a == h_b);

    for(int row_a_idx = 0; row_a_idx < h_a; row_a_idx++)
    {
        for(int col_b_idx = 0; col_b_idx < w_b; col_b_idx++)
        {
            pool_pt->enqueue([row_a_idx, col_b_idx, &a, &b, &result](){
                multiply_subtask(a, b, result, row_a_idx, col_b_idx);
            });
        }
    }
    pool_pt->close();
}

#endif //LAB3_MATRIX_MULTIPLY_H
