cmake_minimum_required(VERSION 3.5)

project(p4-quarto)

include_directories(problem)

add_executable(p4-quarto solution/exceptions.cpp solution/piece.cpp solution/pool.cpp solution/square.cpp solution/quarto.cpp solution/board.cpp solution/game.cpp solution/player.cpp)
