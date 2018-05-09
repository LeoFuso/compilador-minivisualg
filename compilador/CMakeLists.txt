cmake_minimum_required(VERSION 3.10)
project(compiladores C)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c token.c compiler.c)