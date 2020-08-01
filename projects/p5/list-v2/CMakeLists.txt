cmake_minimum_required(VERSION 3.5)
project(p5-new)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(p5-list-v2-test answer/test.cpp)
add_executable(p5-list-v2-rpn answer/rpn.cpp)
add_executable(p5-list-v2-cache answer/cache.cpp)

add_executable(p5-list-v2-test-stl answer-stl/test.cpp)
add_executable(p5-list-v2-rpn-stl answer-stl/rpn.cpp)
add_executable(p5-list-v2-cache-stl answer-stl/cache.cpp)
