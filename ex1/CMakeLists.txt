cmake_minimum_required(VERSION 2.8.4)
project(ex1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(ex1 ${SOURCE_FILES})