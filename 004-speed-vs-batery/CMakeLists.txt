cmake_minimum_required(VERSION 3.15)
set(CMAKE_C_STANDARD 99)
project(004_speed_vs_batery_AOS C)
project(004_speed_vs_batery_SOA C)

find_library(COCOA_LIBRARY Cocoa)
find_library(LIB_GLUT GLUT)
find_library(OPEN_GL_LIBRARY OpenGL)
find_library(CORE_VIDEO_LIBRARY CoreVideo)

include_directories(${CMAKE_SOURCE_DIR}/libs/include)
file(GLOB sources "${CMAKE_SOURCE_DIR}/src/*")
link_directories(${CMAKE_SOURCE_DIR}/libs/static)

set(CMAKE_C_FLAGS "-framework IOKit -v")


message("BUILDING BINARY")
message("CC compiler : $ENV{CC}")

add_executable(test__AOS ./src/main_aos.c)
target_link_libraries(test__AOS raylib flecs_static ${OPEN_GL_LIBRARY} ${LIB_GLUT} ${COCOA_LIBRARY} ${CORE_VIDEO_LIBRARY})


add_executable(test__SOA ./src/main_soa.c)
target_link_libraries(test__SOA raylib flecs_static ${OPEN_GL_LIBRARY} ${LIB_GLUT} ${COCOA_LIBRARY} ${CORE_VIDEO_LIBRARY})
