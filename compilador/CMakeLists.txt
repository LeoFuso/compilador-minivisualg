cmake_minimum_required(VERSION 3.1)
project(compiladores C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES compiler.c token.c)

add_executable(main ${SOURCE_FILES})