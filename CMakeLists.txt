cmake_minimum_required(VERSION 3.15)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)

add_executable(sudoku
        main.cpp generator.h generator.cpp)
add_executable(before
        generator.h generator_origin.cpp main_origin.cpp)
add_executable(Unit
        test.cpp generator.h generator.cpp)

