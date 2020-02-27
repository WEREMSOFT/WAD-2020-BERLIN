cmake_minimum_required(VERSION 3.15)
project(c99 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-O0")

add_executable(c99 main.c)
target_link_libraries(${PROJECT_NAME} "pthread")