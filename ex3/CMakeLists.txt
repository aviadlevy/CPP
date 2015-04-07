cmake_minimum_required(VERSION 2.8.4)
project(ex3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wvla")

set(SOURCE_FILES matrixTest.cpp matrix.h)
add_executable(ex3 ${SOURCE_FILES})