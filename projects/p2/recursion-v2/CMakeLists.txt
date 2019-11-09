CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(p2-recursion-v2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES answer/simple_test.cpp answer/p2.cpp answer/recursive.cpp)

add_executable(p2-recursion-v2 ${SOURCE_FILES})

