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

namespace mpi = boost::mpi;

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
    const std::shared_ptr<std::vector<int>>& a, int startA, int stopA,
    const std::shared_ptr<std::vector<int>>& b, int startB, int stopB,
    std::shared_ptr<std::vector<int>> result,
    const mpi::communicator &comm_world
) {
    // If the lengths are short enough
    if (stopA - startA < 5 || stopB - stopA < 5) {
        sequentialProduct(a, startA, stopA, b, startB, stopB, result);
        return;
    }

    // Else we split into independent sub-problems
    int middleA = (stopA + startA) / 2;
    int middleB = (stopB + startB) / 2;

    std::vector<int> stepOneWorkerResult((stopA - middleA) * 2, 0);
    comm_world.send(1, 0, *a);
    std::cout << "a\n";
    comm_world.send(1, 0, startA);
    std::cout << "b\n";
    comm_world.send(1, 0, stopA);
    std::cout << "c\n";
    comm_world.send(1, 0, *b);
    std::cout << "d\n";
    comm_world.send(1, 0, startB);
    std::cout << "e\n";
    comm_world.send(1, 0, stopB);
    std::cout << "f\n";
    comm_world.send(1, 0, stepOneWorkerResult);
    std::cout << "MAIN SENT WORK TO 1\n";

    std::vector<int> stepThreeWorkerResult((middleA - startA) * 2, 0);
    comm_world.send(2, 0, *a);
    comm_world.send(2, 0, startA);
    comm_world.send(2, 0, middleA);
    comm_world.send(2, 0, *b);
    comm_world.send(2, 0, startB);
    comm_world.send(2, 0, middleB);
    comm_world.send(2, 0, stepThreeWorkerResult);
    std::cout << "MAIN SENT WORK TO 2\n";

    // Step 2:
    //A1 + A0
    std::shared_ptr<std::vector<int>> a1plus0 = firstPlusSecondPart(a, startA, stopA);
    //B1 + B0
    std::shared_ptr<std::vector<int>> b1plus0 = firstPlusSecondPart(b, startB, stopB);
    //(A1 + A0) * (B1 + B0)
    auto productStepTwo = std::make_shared<std::vector<int>>(2 * std::max(a1plus0->size(), b1plus0->size()), 0);

    std::vector<int> stepTwoWorkerResult(2 * std::max(a1plus0->size(), b1plus0->size()), 0);
    comm_world.send(3, 0, *a1plus0);
    comm_world.send(3, 0, 0);
    comm_world.send(3, 0, a1plus0->size());
    comm_world.send(3, 0, *b1plus0);
    comm_world.send(3, 0, 0);
    comm_world.send(3, 0, b1plus0->size());
    comm_world.send(3, 0, stepTwoWorkerResult);
    std::cout << "MAIN SENT WORK TO 3\n";

    comm_world.recv(1, 0, stepOneWorkerResult);
    comm_world.recv(2, 0, stepThreeWorkerResult);
    comm_world.recv(3, 0, stepTwoWorkerResult);

    std::cout << "MAIN RECEIVED RESULTS\n";

    auto ptrStepOne = std::make_shared<std::vector<int>>(stepOneWorkerResult);
    auto ptrStepThree = std::make_shared<std::vector<int>>(stepThreeWorkerResult);

    numberDifference(productStepTwo, ptrStepOne);
    numberDifference(productStepTwo, ptrStepThree);

    // Sum the individual results of each step into the result array
    auto res = std::make_shared<std::vector<int>>((stopA - startA) * 2, 0);

    // Sum step1
    for (int i = middleA * 2; i - middleA * 2 < ptrStepOne->size(); i++)
    {
        (*res)[i] += (*ptrStepOne)[i - middleA * 2];
    }

    // Sum step2
    for (int i = middleA; i - middleA < productStepTwo->size(); i++)
    {
        (*res)[i] += (*productStepTwo)[i - middleA];
    }

    // Sum step3
    for (int i = 0; i < ptrStepThree->size(); i++)
    {
        (*res)[i] += (*ptrStepThree)[i];
    }

    *result = *res;
}

void multiplyKaratsubaParallelWorker(
        std::shared_ptr<std::vector<int>> a, int startA, int stopA,
        std::shared_ptr<std::vector<int>> b, int startB, int stopB,
        std::shared_ptr<std::vector<int>> result, std::atomic<int> &num_threads)
{
    // If the lengths are short enough
    if (stopA - startA < 5 || stopB - stopA < 5 || num_threads == 0) {
        sequentialProduct(a, startA, stopA, b, startB, stopB, result);
        return;
    }

    // Else we split into independent sub-problems
    int middleA = (stopA + startA) / 2;
    int middleB = (stopB + startB) / 2;

    // 1. Add A0 * B0, with 2 * (n/2) offset
    auto stepOneResult = std::make_shared<std::vector<int>>((stopA - middleA) * 2, 0);
    auto strategy = std::launch::deferred;
    if (num_threads != 0) {
        num_threads -= 1;
        strategy = std::launch::async;
    }
    auto stepOneFuture = std::async(
            strategy, [&a, middleA, stopA, &b, middleB, stopB, &num_threads, &stepOneResult]() {
                multiplyKaratsubaParallelWorker(a, middleA, stopA, b, middleB, stopB, stepOneResult, num_threads);
            });

    strategy = std::launch::deferred;
    if (num_threads != 0) {
        num_threads -= 1;
        strategy = std::launch::async;
    }
    // 3. Add A1 * B1, with no offset
    auto stepThreeResult = std::make_shared<std::vector<int>>((middleA - startA) * 2, 0);
    auto stepThreeFuture = std::async(
            strategy, [&a, startA, middleA, &b, startB, middleB, &stepThreeResult, &num_threads]() {
                multiplyKaratsubaParallelWorker(a, startA, middleA, b, startB, middleB, stepThreeResult, num_threads);
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
        multiplyKaratsubaParallelWorker(
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

void multiplyKaratsubaWorkerEntrypoint(const mpi::communicator &comm_world) {
    std::vector<int> a;
    int startA, stopA;
    std::vector<int> b;
    int startB, stopB;
    std::vector<int> result;
    comm_world.recv(0, 0, a);
    comm_world.recv(0, 0, startA);
    comm_world.recv(0, 0, stopA);
    comm_world.recv(0, 0, b);
    comm_world.recv(0, 0, startB);
    comm_world.recv(0, 0, stopB);
    comm_world.recv(0, 0, result);
    std::cout << "WORKER " << comm_world.rank() << " RECEIVED WORK\n";
    auto ptr_a = std::make_shared<std::vector<int>>(a);
    auto ptr_b = std::make_shared<std::vector<int>>(b);
    auto ptr_r = std::make_shared<std::vector<int>>(result);
    auto num_threads = std::atomic<int>(4);
    multiplyKaratsubaParallelWorker(
            ptr_a, startA, stopA,
            ptr_b, startB, stopB,
            ptr_r, num_threads
    );
    comm_world.send(0, 0, result);
}

Polynomial multiplyKaratsubaParallelMainEntrypoint(const Polynomial &A, const Polynomial &B, const mpi::communicator &comm_world)
{
    auto result = std::make_shared<std::vector<int>>(A.getCoefficients().size() * 2, 0);
    auto a = std::make_shared<std::vector<int>>(A.getCoefficients());
    auto b = std::make_shared<std::vector<int>>(B.getCoefficients());
    std::cout << "STARTING\n";
    multiplyKaratsubaParallelMain(a, 0, a->size(), b, 0, b->size(), result, comm_world);
    result->pop_back();
    return Polynomial(*result);
}

#endif //LAB5_KARATSUBA_POLYNOMIAL_MULTIPLICATION_H
