CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(2017_p1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES answer/p1.cpp ../p2/answer/p2.cpp)

add_executable(2017_p1 ${SOURCE_FILES})

