cmake_minimum_required(VERSION 3.15)
project(c99 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wall")

if(CMAKE_BUILD_TYPE MATCHES "html")
    message("BUILDING HTML")
    message("CC compiler : $ENV{CC}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O1 -g4")
    add_executable(${CMAKE_PROJECT_NAME}.html main.c)
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
    message("BUILDING Binary")
    message("$ENV{CC}")
    add_executable(${CMAKE_PROJECT_NAME} main.c)
endif()


