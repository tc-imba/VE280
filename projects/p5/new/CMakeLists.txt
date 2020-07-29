cmake_minimum_required(VERSION 3.5)
project(p5-new)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(p5-new-test answer/test.cpp)
add_executable(p5-new-rpn answer/rpn.cpp)
add_executable(p5-new-cache answer/cache.cpp)

add_executable(p5-new-test-stl answer-stl/test.cpp)
add_executable(p5-new-rpn-stl answer-stl/rpn.cpp)
add_executable(p5-new-cache-stl answer-stl/cache.cpp)
