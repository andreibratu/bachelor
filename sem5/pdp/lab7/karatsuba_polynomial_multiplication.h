//
// Created by bratu on 11/14/2020.
//

#ifndef LAB5_KARATSUBA_POLYNOMIAL_MULTIPLICATION_H
#define LAB5_KARATSUBA_POLYNOMIAL_MULTIPLICATION_H

#include <memory>
#include <thread>
#include <future>
#include "Polynomial.h"
#include "karatsuba_aux.h"
#include "mpl.hpp"

std::vector<int> karatsubaSequential(const std::vector<int> &A, const std::vector<int> &B)
{
    std::vector<int> product = std::vector<int>(2 * B.size(), 0);

    if (B.size() == 1)
    {
        product[0] = A[0] * B[0];
        return product;
    }

    int halfSize = A.size() / 2; // NOLINT(cppcoreguidelines-narrowing-conversions)

    auto aLow = std::vector<int>(halfSize, 0);
    auto aHigh = std::vector<int>(halfSize, 0);
    auto bLow = std::vector<int>(halfSize, 0);
    auto bHigh = std::vector<int>(halfSize, 0);

    auto aLowHigh = std::vector<int>(halfSize, 0);
    auto bLowHigh = std::vector<int>(halfSize, 0);

    // Fill in divisions
    for (int i = 0; i < halfSize; ++i)
    {
        aLow[i] = A[i];
        aHigh[i] = A[halfSize + i];
        aLowHigh[i] = aHigh[i] + aLow[i];

        bLow[i] = B[i];
        bHigh[i] = B[halfSize + i];
        bLowHigh[i] = bHigh[i] + bLow[i];
    }

    //Recursively call method on smaller arrays
    auto productLow = karatsubaSequential(aLow, bLow);
    auto productHigh = karatsubaSequential(aHigh, bHigh);

    auto productLowHigh = karatsubaSequential(aLowHigh, bLowHigh);

    //Construct middle portion of the product
    auto productMiddle = std::vector<int>(A.size(), 0);
    for (int i = 0; i < A.size(); i++)
    {
        productMiddle[i] = productLowHigh[i] - productLow[i] - productHigh[i];
    }

    //Assemble the product from the low, middle and high parts
    int midOffset = A.size() / 2; // NOLINT(cppcoreguidelines-narrowing-conversions)
    for (int i = 0; i < A.size(); ++i)
    {
        product[i] += productLow[i];
        product[i + A.size()] += productHigh[i];
        product[i + midOffset] += productMiddle[i];
    }

    return product;
}

std::shared_ptr<std::vector<int>> firstPlusSecondPart(
    const std::shared_ptr<std::vector<int>> &arr,
    int start, int stop)
{

    int middle = (stop + start) / 2;
    std::shared_ptr<std::vector<int>> result = std::make_shared<std::vector<int>>(
        std::max(middle - start, stop - middle), 0);
    for (int i = start; i < middle; i++)
    {
        (*result)[i - start] = (*arr)[i];
    }
    for (int i = middle; i < stop; i++)
    {
        (*result)[i - middle] += (*arr)[i];
    }
    return result;
}

Polynomial karatsubaSequentialMultiplication(const Polynomial &A, const Polynomial &B)
{
    auto result = karatsubaSequential(A.getCoefficients(), B.getCoefficients());
    result.pop_back();
    return Polynomial(result);
}

void sequentialProduct(
    const std::shared_ptr<std::vector<int>> &a, int startA, int stopA,
    const std::shared_ptr<std::vector<int>> &b, int startB, int stopB,
    std::shared_ptr<std::vector<int>> &result)
{

    std::vector<int> res = std::vector<int>((stopA - startA) * 2, 0);

    for (int i = startB; i < stopB; i++)
    {
        int carry = 0;
        for (int j = startA; j < stopA; j++)
        {
            int prod = (*a)[j] * (*b)[i] + carry;

            (*result)[i + j - startA - startB] += prod;
        }
    }
}

void multiplyKaratsubaParallelMain(
    std::shared_ptr<std::vector<int>> a, int startA, int stopA,
    std::shared_ptr<std::vector<int>> b, int startB, int stopB,
    std::shared_ptr<std::vector<int>> result,
    const mpl::communicator &comm_world
) {
    /*
     * When targetLevel of recursion tree is reached, all children
     * nodes will be spawned on different process.
     */

    // If the lengths are short enough
    if (stopA - startA < 5 || stopB - stopA < 5 || num_threads == 0) {
        sequentialProduct(a, startA, stopA, b, startB, stopB, result);
        return;
    }

    // Else we split into independent sub-problems
    int middleA = (stopA + startA) / 2;
    int middleB = (stopB + startB) / 2;

    vector<int> stepOneWorkerResult(*result);
    comm_world.send(std::vector<int>(a), 1)
    comm_world.send(startA, 1)
    comm_world.send(stopA, 1)
    comm_world.send(std::vector<int>(b), 1)
    comm_world.send(startB, 1)
    comm_world.send(stopB, 1)
    comm_world.send(std::vector<int>((stopA - middleA) * 2, 0))

    vector<int> stepOneWorkerResult(*result);
    comm_world.send(std::vector<int>(a), 1)
    comm_world.send(startA, 1)
    comm_world.send(middleA, 1)
    comm_world.send(std::vector<int>(b), 1)
    comm_world.send(startB, 1)
    comm_world.send(middleB, 1)
    comm_world.send(std::vector<int>((middleA - startA) * 2, 0))
}

void multiplyKaratsubaParallelWorker(
    std::shared_ptr<std::vector<int>> a, int startA, int stopA,
    std::shared_ptr<std::vector<int>> b, int startB, int stopB,
    std::shared_ptr<std::vector<int>> result)
{
    // If the lengths are short enough
    if (stopA - startA < 5 || stopB - stopA < 5 || num_threads == 0)
    {
        sequentialProduct(a, startA, stopA, b, startB, stopB, result);
        return;
    }

    // Else we split into independent sub-problems
    int middleA = (stopA + startA) / 2;
    int middleB = (stopB + startB) / 2;

    // 1. Add A0 * B0, with 2 * (n/2) offset
    auto stepOneResult = std::make_shared<std::vector<int>>((stopA - middleA) * 2, 0);
    auto strategy = std::launch::deferred;
    if (num_threads != 0)
    {
        num_threads -= 1;
        strategy = std::launch::async;
    }
    auto stepOneFuture = std::async(
        strategy, [&a, middleA, stopA, &b, middleB, stopB, &num_threads, &stepOneResult]() {
                multiplyKaratsubaParallelMain(a, middleA, stopA, b, middleB, stopB, stepOneResult, num_threads);
        });

    strategy = std::launch::deferred;
    if (num_threads != 0)
    {
        num_threads -= 1;
        strategy = std::launch::async;
    }
    // 3. Add A1 * B1, with no offset
    auto stepThreeResult = std::make_shared<std::vector<int>>((middleA - startA) * 2, 0);
    auto stepThreeFuture = std::async(
        strategy, [&a, startA, middleA, &b, startB, middleB, &stepThreeResult, &num_threads]() {
                multiplyKaratsubaParallelMain(a, startA, middleA, b, startB, middleB, stepThreeResult, num_threads);
        });

    // Step 2:
    //A1 + A0
    std::shared_ptr<std::vector<int>> a1plus0 = firstPlusSecondPart(a, startA, stopA);
    //B1 + B0
    std::shared_ptr<std::vector<int>> b1plus0 = firstPlusSecondPart(b, startB, stopB);
    //(A1 + A0) * (B1 + B0)
    auto productStepTwo = std::make_shared<std::vector<int>>(2 * std::max(a1plus0->size(), b1plus0->size()), 0);

    strategy = std::launch::deferred;
    if (num_threads != 0)
    {
        num_threads -= 1;
        strategy = std::launch::async;
    }
    auto stepTwoFuture = std::async(strategy, [&a1plus0, &b1plus0, &productStepTwo, &num_threads]() {
        multiplyKaratsubaParallelMain(
                a1plus0, 0, a1plus0->size(),
                b1plus0, 0, b1plus0->size(),
                productStepTwo, num_threads);
    });
    stepOneFuture.get();
    stepTwoFuture.get();
    stepThreeFuture.get();

    numberDifference(productStepTwo, stepOneResult);
    numberDifference(productStepTwo, stepThreeResult);

    // Sum the individual results of each step into the result array
    auto res = std::make_shared<std::vector<int>>((stopA - startA) * 2, 0);

    // Sum step1
    for (int i = middleA * 2; i - middleA * 2 < stepOneResult->size(); i++)
    {
        (*res)[i] += (*stepOneResult)[i - middleA * 2];
    }

    // Sum step2
    for (int i = middleA; i - middleA < productStepTwo->size(); i++)
    {
        (*res)[i] += (*productStepTwo)[i - middleA];
    }

    // Sum step3
    for (int i = 0; i < stepThreeResult->size(); i++)
    {
        (*res)[i] += (*stepThreeResult)[i];
    }

    *result = *res;
}

Polynomial karatsubaParallelMultiplication(const Polynomial &A, const Polynomial &B)
{
    auto result = std::make_shared<std::vector<int>>(A.getCoefficients().size() * 2, 0);
    auto a = std::make_shared<std::vector<int>>(A.getCoefficients());
    auto b = std::make_shared<std::vector<int>>(B.getCoefficients());
    std::atomic<int> value(num_threads);
    multiplyKaratsubaParallelMain(a, 0, a->size(), b, 0, b->size(), result, value, 1);
    result->pop_back();
    return Polynomial(*result);
}

#endif //LAB5_KARATSUBA_POLYNOMIAL_MULTIPLICATION_H
