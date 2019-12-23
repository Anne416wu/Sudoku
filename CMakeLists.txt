cmake_minimum_required(VERSION 3.15)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)

add_executable(sudoku
        main.cpp generator.h generator.cpp)
