CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(2017_p2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES answer/simple_test.cpp answer/p2.cpp answer/recursive.cpp)

add_executable(2017_p2 ${SOURCE_FILES})

