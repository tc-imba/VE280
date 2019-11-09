cmake_minimum_required(VERSION 3.5)
project(p4-blackjack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES answer/blackjack.cpp answer/deck.cpp answer/card.cpp answer/hand.cpp answer/player.cpp answer/rand.cpp)

add_executable(p4-blackjack ${SOURCE_FILES})