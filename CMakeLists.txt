cmake_minimum_required(VERSION 3.13)
project(SnakeCube)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lpthread -m64 -fpermissive -Wall -Wextra -Wold-style-cast -Wuseless-cast")

add_executable(SnakeCube src/main.cpp)