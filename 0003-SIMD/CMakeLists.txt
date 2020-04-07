cmake_minimum_required(VERSION 3.15)
project(0003_SIMD C)

set(CMAKE_C_FLAGS_DEFAULT "-v")

set(CMAKE_C_STANDARD 99)
file(GLOB sources ./src/*)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEFAULT} ${CMAKE_C_FLAGS_PTHREADS}")
    set(CMAKE_EXE_LINKER_FLAGS "-O1 -Wl")
    add_executable(${CMAKE_PROJECT_NAME} ${sources})
else()
    set(CMAKE_C_FLAGS_PTHREADS "-s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEFAULT} -g -s SIMD=1 ${CMAKE_C_FLAGS_PTHREADS}")
    set(CMAKE_EXE_LINKER_FLAGS "-O1 -g4 -s SIMD=1 -Wl --shared-memory --no-check --experimental-wasm-simd")
    add_executable(${CMAKE_PROJECT_NAME}.html ${sources})
endif()
