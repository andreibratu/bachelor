cmake_minimum_required(VERSION 3.17)
project(lab5)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab5 main.cpp Polynomial.h Polynomial.cpp utils.h naive_polynomial_multiplication.h karatsuba_polynomial_multiplication.h karatsuba_aux.h)