#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <pthread.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PARTICLES_COUNT 200000
#define GRAVITY_SCALAR -0.9f

#define MAX_PARTICLES_TO_DRAW 1000
#define DRAW_PARTICLES
#define FRAMES_PER_SECOND 2000

#endif