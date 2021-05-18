cmake_minimum_required(VERSION 3.19)
project(GNL2 C)

set(CMAKE_C_STANDARD 99)

add_executable(GNL2 main.c
        get_next_line.c
        get_next_line_utils.c)