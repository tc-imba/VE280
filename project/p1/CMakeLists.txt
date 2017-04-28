CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(p1)

SET(SOURCE_FILES p1.cpp)

add_executable(p1 ${SOURCE_FILES})

SET(SOURCE_FILES tester.cpp)

add_executable(p1.test ${SOURCE_FILES})
