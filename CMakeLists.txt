cmake_minimum_required(VERSION 3.8.2)
project(compilador_minivisualg C)

set(CMAKE_C_STANDARD 99)

add_executable(compilador_minivisualg main.c token.c)