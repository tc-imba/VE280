cmake_minimum_required(VERSION 3.5)
project(p4-huffman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES answer/binaryTree.cpp answer/huffmanTree.cpp)

add_executable(p4-huffman-compress ${SOURCE_FILES} answer/compress.cpp)
add_executable(p4-huffman-decompress ${SOURCE_FILES} answer/decompress.cpp)
