CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(2017_p3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(SOURCE_FILES
        answer/p3.cpp
        answer/world.cpp
        answer/exception.cpp
        answer/species.cpp
        answer/grid.cpp
        answer/controller.cpp
        answer/creature.cpp
        answer/simulation.cpp
        )

add_executable(p3-hard-world-debug ${SOURCE_FILES})


SET(SOURCE_FILES answer/p3.cpp answer/simulation.cpp)
add_executable(p3-hard-world ${SOURCE_FILES})

