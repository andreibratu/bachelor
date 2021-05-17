cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp Semaphore.cpp Semaphore.h Queue.hpp util.hpp)