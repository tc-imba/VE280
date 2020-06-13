CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(p3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES answer/p3.cpp answer/simulation.cpp)

add_executable(p3-simple-world ${SOURCE_FILES})
