cmake_minimum_required(VERSION 3.17)
project(lab8)

set(CMAKE_CXX_STANDARD 17)

FIND_PACKAGE(MPI REQUIRED)
FIND_PACKAGE(Boost COMPONENTS mpi serialization REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${MPI_INCLUDE_PATH})

add_executable(lab8 main.cpp DSMChannel.h DSMValue.h DSMSupervisor.h DSMOpResult.h DSMOp.h DSMListener.h DSMOpResult.h)

TARGET_LINK_LIBRARIES( lab8 ${MPI_LIBRARIES} ${Boost_LIBRARIES} )

if(MPI_COMPILE_FLAGS)
    set_target_properties(lab8 PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()
if(MPI_LINK_FLAGS)
    set_target_properties(lab8 PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()