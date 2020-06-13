cmake_minimum_required(VERSION 3.10)
project(p2-simple-twitter)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG")

add_executable(p2-simple-twitter answer/main.cpp answer/simulation.cpp)
add_executable(p2-simple-twitter-only-main answer-only-main/p2.cpp answer-only-main/simulation.cpp)

target_link_libraries(p2-simple-twitter stdc++fs)
