cmake_minimum_required(VERSION 3.16)

project(MedianCalculator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MedianCalculator ../src/main.cpp ../src/self_test.cpp)
target_compile_options(MedianCalculator PRIVATE -Wall)
