cmake_minimum_required(VERSION 3.30)
project(quadratic_bezier_splines_visualizer C)

set(CMAKE_C_STANDARD 11)

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_compile_options(-ansi -pedantic-errors -std=c11 -Wall -Wextra -Wno-incompatible-pointer-types -Wno-deprecated-declarations -Wno-switch)

add_subdirectory(targets/library)
add_subdirectory(targets/demo)