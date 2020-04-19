#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PARTICLES_COUNT 200000
#define GRAVITY (Vector3){0, -0.9f, 0}

Vector3 velocity_create() {
    return (Vector3){GetRandomValue(-10, 10) / 100.0f, GetRandomValue(-100, 100) / 100.0f, GetRandomValue(-10, 10) / 100.0f};
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Energy Consumption - AOS");

    Vector3 particles[PARTICLES_COUNT] = {0};
    Vector3 particles_speed[PARTICLES_COUNT] = {0};

    for(unsigned long int i = 0; i < PARTICLES_COUNT; i++){
        particles_speed[i] = velocity_create();
    }

    Camera3D camera = {{55, 54, 55}, {0, 0.2, 0}, {0, 1, 0}, 45.0f, CAMERA_PERSPECTIVE};

    SetCameraMode(camera, CAMERA_ORBITAL);

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        ClearBackground(GREEN);
        Vector3 delta = Vector3Scale(GRAVITY, GetFrameTime());
        UpdateCamera(&camera);
        // Update particles position
        for(unsigned int i = 0; i < PARTICLES_COUNT; i++){
            particles_speed[i] = Vector3Add(particles_speed[i], delta);
            particles[i] = Vector3Add(particles[i], particles_speed[i]);
            if(particles[i].y <= 0) {
                particles[i] = Vector3Zero();
                particles_speed[i] = velocity_create();
            }
        }

        BeginDrawing();{
//             unsigned int i = 0;
//             for(int j = 8000; j < PARTICLES_COUNT; j += 8000) {
//                 BeginMode3D(camera);
//                 {
//                     for(; i < j; i++){
//                         DrawBillboard(camera, texture, particles[i], 1.0f, WHITE);
//                     }
//                 }EndMode3D();
//             }
            BeginMode3D(camera);
                DrawGrid(10, 10);
            EndMode3D();

            DrawFPS(10, 10);
            DrawText("AOS", 10, 50, 24, RED);
        }EndDrawing();
    }

    return 0;
}
