cmake_minimum_required(VERSION 3.5)
project(p5-containers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_executable(p5-list-v1-call answer/call.cpp)
add_executable(p5-list-v1-calc answer/calc.cpp)
