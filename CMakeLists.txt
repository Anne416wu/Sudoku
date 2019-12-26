cmake_minimum_required(VERSION 3.15)
project(Sudoku)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include .${gtest_SOURCE_DIR})

add_executable(sudoku
        src/main.cpp src/generator.h src/generator.cpp)
add_executable(before
        src/generator.h origin/generator_origin.cpp origin/main_origin.cpp)
add_executable(Unit
        test/test.cpp src/generator.h src/generator.cpp)
add_executable(class
        class/sudoku.h class/main.cpp)

target_link_libraries(Unit gtest gtest_main)