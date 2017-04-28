CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(p2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES answer/test_main.cpp)

add_executable(p2 ${SOURCE_FILES})
