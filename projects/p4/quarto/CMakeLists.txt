cmake_minimum_required(VERSION 3.5)

project(p4-quarto)

include_directories(problem)

add_executable(p4-quarto answer/exceptions.cpp answer/piece.cpp answer/pool.cpp answer/square.cpp answer/quarto.cpp answer/board.cpp answer/game.cpp answer/player.cpp)
