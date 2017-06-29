CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(2017_p2_test)

include_directories(../../../libs/googletest/googletest/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES unittest.cpp list_test.h ../answer/p2.cpp recursive.cpp)

add_executable(2017_p2_test ${SOURCE_FILES})
target_link_libraries(2017_p2_test gtest)

