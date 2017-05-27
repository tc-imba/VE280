cmake_minimum_required(VERSION 3.5)
project(p5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES answer/calc.cpp)

add_executable(p5 ${SOURCE_FILES})