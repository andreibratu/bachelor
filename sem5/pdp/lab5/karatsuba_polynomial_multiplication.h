//
// Created by bratu on 11/14/2020.
//

#ifndef LAB5_KARATSUBA_POLYNOMIAL_MULTIPLICATION_H
#define LAB5_KARATSUBA_POLYNOMIAL_MULTIPLICATION_H

#include <memory>
#include <thread>
#include "Polynomial.h"
#include "thread_pool.h"
#include "karatsuba_aux.h"

std::vector<int> karatsubaSequential(const std::vector<int> &A, const std::vector<int> &B) {
    std::vector<int> product = std::vector<int>(2 * B.size(), 0);

    if(B.size() == 1) {
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
    for(int i = 0; i < halfSize; ++i) {
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
    for(int i = 0; i < A.size(); i++) {
        productMiddle[i] = productLowHigh[i] - productLow[i] - productHigh[i];
    }

    //Assemble the product from the low, middle and high parts
    int midOffset = A.size() / 2; // NOLINT(cppcoreguidelines-narrowing-conversions)
    for(int i = 0; i < A.size(); ++i){
        product[i] += productLow[i];
        product[i + A.size()] += productHigh[i];
        product[i + midOffset] += productMiddle[i];
    }

    return product;
}

std::shared_ptr<std::vector<int>> firstPlusSecondPart(
        const std::shared_ptr<std::vector<int>>& arr,
        int start, int stop
) {

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

Polynomial karatsubaSequentialMultiplication(const Polynomial &A, const Polynomial &B) {
    auto result = karatsubaSequential(A.getCoefficients(), B.getCoefficients());
    result.pop_back();
    return Polynomial(result);
}

void numberProdSequentialAux(
    const std::shared_ptr<std::vector<int>>& a, int startA, int stopA,
    const std::shared_ptr<std::vector<int>>& b, int startB, int stopB,
    std::shared_ptr<std::vector<int>> &result)
{

    std::vector<int> res = std::vector<int>((stopA - startA) * 2, 0);

    for (int i = startB; i < stopB; i++)
    {
        int carry = 0;
        for (int j = startA; j < stopA; j++)
        {
            int prod = (*a)[j] * (*b)[i] + carry;

            res[i + j - startA - startB] += prod;
        }
    }

    result = std::make_shared<std::vector<int>>(res);
}

void multiplyKaratsubaParallelAux(
        const std::unique_ptr<ThreadPool> &poolPtr,
        std::shared_ptr<std::vector<int>> a, int startA, int stopA,
        std::shared_ptr<std::vector<int>> b, int startB,int stopB,
        std::shared_ptr<std::vector<int>> result
) {
    // If the lengths are short enough, apply the sequential method
    if(stopA - startA < 5 || stopB - stopA < 5 || poolPtr->available_threads() == 0) {
        numberProdSequentialAux(a, startA, stopA, b, startB, stopB, result);
        return;
    }

    // Else we split into independent subproblems
    int middleA = (stopA + startA)/2;
    int middleB = (stopB + startB)/2;

    // 1. Add A0 * B0, with 2 * (n/2) offset
    std::shared_ptr<std::atomic<bool>> stepOneFlag;
    auto stepOneResult = std::make_shared<std::vector<int>>((stopA - middleA) * 2, 0);
    if (poolPtr->available_threads() > 0) {
        stepOneFlag = poolPtr->enqueue([&a, middleA, stopA, &b, middleB, stopB, &stepOneResult, &poolPtr](){
            multiplyKaratsubaParallelAux(
                    poolPtr,
                    a, middleA, stopA,
                    b, middleB, stopB,
                    stepOneResult);
        });
    }
    else {
        multiplyKaratsubaParallelAux(
           poolPtr,
        a, middleA, stopA,
        b, middleB, stopB,
        stepOneResult);
    }

    // 3. Add A1 * B1, with no offset
    std::shared_ptr<std::atomic<bool>> stepThreeFlag;
    auto stepThreeResult = std::make_shared<std::vector<int>>((middleA - startA) * 2, 0);
    if (poolPtr->available_threads() > 0) {
        stepThreeFlag = poolPtr->enqueue([&poolPtr, &a, startA, middleA, &b, startB, middleB, &stepThreeResult](){
            multiplyKaratsubaParallelAux(
                    poolPtr,
                    a, startA, middleA,
                    b, startB, middleB,
                    stepThreeResult
            );
        });
    }
    else {
        multiplyKaratsubaParallelAux(
                poolPtr,
                a, startA, middleA,
                b, startB, middleB,
                stepThreeResult
        );
    }

    // Step 2:
    //A1 + A0
    std::shared_ptr<std::vector<int>> a1plus0 = firstPlusSecondPart(a, startA, stopA);
    //B1 + B0
    std::shared_ptr<std::vector<int>> b1plus0 = firstPlusSecondPart(b, startB, stopB);
    //(A1 + A0) * (B1 + B0)
    auto productStepTwo = std::make_shared<std::vector<int>>(2 * std::max(a1plus0->size(), b1plus0->size()), 0);

    std::shared_ptr<std::atomic<bool>> stepTwoFlag = nullptr;
    if (poolPtr->available_threads() > 0) {
        stepTwoFlag = poolPtr->enqueue([&poolPtr, &a1plus0, b1plus0, &productStepTwo](){
            multiplyKaratsubaParallelAux(
                poolPtr,
                a1plus0, 0, a1plus0->size(),
                b1plus0, 0, b1plus0->size(),
                productStepTwo
            );
        });
    }
    else {
        multiplyKaratsubaParallelAux(
            poolPtr,
            a1plus0, 0, a1plus0->size(),
            b1plus0, 0, b1plus0->size(),
            productStepTwo
        );
    }
    // result = productStepTwo - (A0 * B0 + A1 * B1)
    // Wait for step one and step three to finish
    bool checkOne = false;
    bool checkThree = false;
    while(!checkOne && !checkThree) {
        checkOne = (!stepOneFlag) || (stepOneFlag->load());
        checkThree = (!stepThreeFlag)  || (stepThreeFlag->load());
    }

    numberDifference(productStepTwo, stepOneResult);
    numberDifference(productStepTwo, stepThreeResult);

    // Sum the individual results of each step into the result array
    auto res = std::make_shared<std::vector<int>>((stopA - startA) * 2, 0);

    // Sum step1
    for(int i = middleA * 2; i - middleA * 2 < stepOneResult->size(); i++) {
        (*res)[i] += (*stepOneResult)[i - middleA * 2];
    }

    // Sum step2
    for(int i = middleA; i - middleA < productStepTwo->size(); i++) {
        (*res)[i] += (*productStepTwo)[i - middleA];
    }

    // Sum step3
    for(int i = 0; i < stepThreeResult->size(); i++){
        (*res)[i] += (*stepThreeResult)[i];
    }

    *result = *res;
}

void multiplyKaratsubaParallel(
        const std::shared_ptr<std::vector<int>>& a,
        const std::shared_ptr<std::vector<int>>& b,
        const std::shared_ptr<std::vector<int>>& result, int threads
) {
    auto intermediary = std::make_shared<std::vector<int>>(a->size() * 2, 0);
    auto poolPtr = std::make_unique<ThreadPool>(threads);

    multiplyKaratsubaParallelAux(poolPtr, a, 0, a->size(), b, 0, b->size(), intermediary);

    for(int i=0; i < intermediary->size(); i++) {
        (*result)[i] = (*intermediary)[i];
    }
}

Polynomial karatsubaParallelMultiplication(const Polynomial& A, const Polynomial& B, int numThreads) {
    auto result = std::make_shared<std::vector<int>>(A.getCoefficients().size() * 2, 0);
    auto a = std::make_shared<std::vector<int>>(A.getCoefficients());
    auto b = std::make_shared<std::vector<int>>(B.getCoefficients());
    multiplyKaratsubaParallel(a, b, result, numThreads);
    result->pop_back();
    return Polynomial(*result);
}

#endif //LAB5_KARATSUBA_POLYNOMIAL_MULTIPLICATION_H
