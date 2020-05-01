cmake_minimum_required(VERSION 3.15)
set(CMAKE_C_STANDARD 99)
project(speed_vs_batery_optimized C)
project(speed_vs_batery_unoptimized C)

include_directories(${CMAKE_SOURCE_DIR}/libs/include)
file(GLOB sources "${CMAKE_SOURCE_DIR}/src/*")
link_directories(${CMAKE_SOURCE_DIR}/libs/static)
if (UNIX)
    message("ES UNIX!!!")

    set(CMAKE_C_FLAGS "-O0 -g -flto -v")

    message("CC compiler : $ENV{CC}")

    set(LIBRARIES_TO_INCLUDE m dl raylib-linux pthread X11 xcb GL GLX Xext GLdispatch Xau Xdmcp)

    add_executable(speed_vs_batery_optimized src/main_optimized.c)
    target_link_libraries(speed_vs_batery_optimized ${LIBRARIES_TO_INCLUDE})

    add_executable(speed_vs_batery_unoptimized src/main_unoptimized.c)
    target_link_libraries(speed_vs_batery_unoptimized ${LIBRARIES_TO_INCLUDE})
else(UNIX)
    message("No ES LINUX!!")
    find_library(LIB_GLUT GLUT)
    find_library(OPEN_GL_LIBRARY OpenGL)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(CORE_VIDEO_LIBRARY CoreVideo)

    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        set(CMAKE_C_FLAGS "-O0 -framework IOKit -v")
        message("BUILDING BINARY")
        message("CC compiler : $ENV{CC}")

        add_executable(speed_vs_batery_optimized src/main_optimized.c)
        target_link_libraries(speed_vs_batery_optimized raylib flecs_static ${OPEN_GL_LIBRARY} ${LIB_GLUT} ${COCOA_LIBRARY} ${CORE_VIDEO_LIBRARY})

        add_executable(speed_vs_batery_unoptimized src/main_unoptimized.c)
        target_link_libraries(speed_vs_batery_unoptimized raylib flecs_static ${OPEN_GL_LIBRARY} ${LIB_GLUT} ${COCOA_LIBRARY} ${CORE_VIDEO_LIBRARY})
    elseif(CMAKE_BUILD_TYPE MATCHES "HTML")
        set(RAYLIB_PATH "/Users/pabloweremczuk/Documents/Proyectos/c/raylib")
        set(CMAKE_C_FLAGS_DEFAULT "-O0 -s -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0 -v")
        message("Es html")
        set(CC_PATH $ENV{EMSDK})
        add_compile_definitions(PLATFORM_WEB=${OpenCV_VERSION})
        message("Path to emscripten compiler: ${CC_PATH}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEFAULT} -g4 -s USE_GLFW=3 -s TOTAL_MEMORY=67108864")
        set(CMAKE_EXE_LINKER_FLAGS "../libs/static/libraylib.bc -O0 -g4")
        set(LDLIBS "./libs/static/libraylib.bc")
        add_executable(speed_vs_batery_unoptimized.html ./src/main_unoptimized.c ./libs/static/libraylib.bc)
        add_executable(speed_vs_batery_optimized.html ./src/main_optimized.c ./libs/static/libraylib.bc)
    endif()
endif (UNIX)

