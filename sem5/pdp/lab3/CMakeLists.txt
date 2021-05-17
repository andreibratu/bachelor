cmake_minimum_required(VERSION 3.17)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab3 main.cpp ThreadPool.h matrix_multiply.h util.h)