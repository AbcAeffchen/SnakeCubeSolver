cmake_minimum_required(VERSION 3.13)
project(SnakeCube)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lpthread -m64 -fpermissive -Wall -Wextra -Wold-style-cast -Wuseless-cast")

include(FindOpenMP)
if(NOT OPENMP_FOUND)
    message("OpenMP not found. Trying '-fopenmp=libiomp5'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp=libiomp5")
else()
    message("OpenMP found: ${OpenMP_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

message("Compiler: ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_VERSION}")
message("Flags: ${CMAKE_CXX_FLAGS}")


add_executable(SnakeCube src/main.cpp)