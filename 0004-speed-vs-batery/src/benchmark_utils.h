#ifndef BENCHMARK_UTILS
#define BENCHMARK_UTILS

#include <raylib.h>
#include "config.h" 
#include <cyle_count.h>


void draw_fps_graph()
{
    static int samples[WINDOW_WIDTH];
    static int samples_index;
    static long long int cycles_samples[WINDOW_WIDTH];

    samples_index %= WINDOW_WIDTH;
    samples[samples_index] =  WINDOW_HEIGHT - GetFPS();

    cycles_samples[samples_index] = rdtsc() / 50000000000;

    DrawRectangle(0, WINDOW_HEIGHT - 100, WINDOW_WIDTH, 100, BLACK);
    for(int i = 0; i < WINDOW_WIDTH; i++){

        DrawPixel(i, samples[i], WHITE);
        DrawPixel(i, cycles_samples[i], GREEN);
        if(i == samples_index) {
            DrawLine(i, WINDOW_HEIGHT, i, WINDOW_HEIGHT - 100, RED);
        }
    }
    samples_index++;
}
#endif 