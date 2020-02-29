cmake_minimum_required(VERSION 3.15)
project(c99 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS_DEFAULT "-v -Wall")

file(GLOB sources ./src/*)


message("Building for ${CMAKE_BUILD_TYPE}")

if(CMAKE_BUILD_TYPE MATCHES "Release")
    message("Es release")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEFAULT} -Os -s -DNDEBUG")
    add_executable(${PROJECT_NAME} ${sources})
    target_link_libraries(${PROJECT_NAME} "pthread")
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
    message("Es Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEFAULT} -O0")
    add_executable(${PROJECT_NAME} ${sources})
    target_link_libraries(${PROJECT_NAME} "pthread")
elseif(CMAKE_BUILD_TYPE MATCHES "HTML")
    message("Es html")
    set(CC_PATH $ENV{CC})
    message("Path to emscripten compiler: ${CC_PATH}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEFAULT} -O0 -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/html")
    add_executable(${PROJECT_NAME}.html ${sources})
    target_link_libraries(${PROJECT_NAME}.html "pthread")
endif()





