cmake_minimum_required(VERSION 3.5)
project(Project4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES blackjack.cpp deck.cpp card.cpp hand.cpp player.cpp rand.cpp)

add_executable(Project4 ${SOURCE_FILES})