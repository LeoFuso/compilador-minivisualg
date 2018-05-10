cmake_minimum_required(VERSION 3.1)
project(compiladores C)

set(CMAKE_C_STANDARD 99)

add_executable(main main.c compiler.c token.c stack.c )