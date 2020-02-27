cmake_minimum_required(VERSION 3.15)
project(c99 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-v -O0")

file(GLOB sources ./src/*)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} "pthread")

#set(CMAKE_C_FLAGS "-v -O0 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/html")
add_executable(${PROJECT_NAME}.html ${sources})
target_link_libraries(${PROJECT_NAME}.html "pthread")