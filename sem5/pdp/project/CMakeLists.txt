cmake_minimum_required(VERSION 3.17)
project(project)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE(MPI REQUIRED)
FIND_PACKAGE(Boost COMPONENTS mpi serialization REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${MPI_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_executable(project main.cpp canny.h hough.h)

TARGET_LINK_LIBRARIES( project ${MPI_LIBRARIES} ${Boost_LIBRARIES} ${OpenCV_LIBS})

if(MPI_COMPILE_FLAGS)
    set_target_properties(project PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()
if(MPI_LINK_FLAGS)
    set_target_properties(project PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()

