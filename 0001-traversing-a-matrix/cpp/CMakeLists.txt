cmake_minimum_required(VERSION 3.15)
project(cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O3")

add_executable(${CMAKE_PROJECT_NAME}-friendly src/main-friendly.cpp)
add_executable(${CMAKE_PROJECT_NAME}-unfriendly src/main-unfriendly.cpp)

