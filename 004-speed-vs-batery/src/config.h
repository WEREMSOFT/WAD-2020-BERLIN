//
// Created by Pablo Weremczuk on 4/20/20.
//

#ifndef INC_004_SPEED_VS_BATERY_SOA_CONFIG_H
#define INC_004_SPEED_VS_BATERY_SOA_CONFIG_H
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <stdlib.h>

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PARTICLES_COUNT 8200
#define GRAVITY -0.9f
#define FPS 60
#endif //INC_004_SPEED_VS_BATERY_SOA_CONFIG_H
