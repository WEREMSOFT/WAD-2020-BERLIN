cmake_minimum_required(VERSION 3.15)
project(c99 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -O3 -Ofast")

add_executable(c99 main.c)