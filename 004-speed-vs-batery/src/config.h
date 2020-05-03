#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <pthread.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PARTICLES_COUNT 100000
#define GRAVITY_SCALAR -0.9f

#define MAX_PARTICLES_TO_DRAW 1000
#define DRAW_PARTICLES
// #define SEPARATED_LOOPS
#define USE_VECTOR_FUNCTIONS
#define FRAMES_PER_SECOND 60
// #define RUN_ONLY_COUNT_FRAMES
#define COUNT_FRAMES 1000

char STRING_NUMBER_OF_PARTICLES[100];
Camera3D camera = {{55, 54, 55}, {0, 0.2, 0}, {0, 1, 0}, 45.0f, CAMERA_PERSPECTIVE};
Texture2D texture;
#endif
