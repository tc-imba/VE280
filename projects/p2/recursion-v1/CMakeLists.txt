CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(p2-recursion-v1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES answer/test.cpp  answer/test_main.cpp answer/recursive.cpp answer/p2.cpp)

add_executable(p2-recursion-v1 ${SOURCE_FILES})
