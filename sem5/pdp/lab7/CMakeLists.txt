cmake_minimum_required(VERSION 3.17)
project(lab7)

find_package(MPI REQUIRED)

include_directories(mpl)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab7_sequential main_sequential.cpp Polynomial.h Polynomial.cpp utils.h naive_polynomial_multiplication.h)

target_link_libraries(lab7_sequential ${MPI_LIBRARIES})

add_executable(lab7_karatsuba main_karatsuba.cpp Polynomial.h Polynomial.cpp utils.h karatsuba_polynomial_multiplication.h karatsuba_aux.h)

target_link_libraries(lab7_karatsuba ${MPI_LIBRARIES})

include_directories(${MPI_INCLUDE_PATH})
if(MPI_COMPILE_FLAGS)
    set_target_properties(lab7_sequential PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
    set_target_properties(lab7_karatsuba PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()
if(MPI_LINK_FLAGS)
    set_target_properties(lab7_sequential PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
    set_target_properties(lab7_karatsuba PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()