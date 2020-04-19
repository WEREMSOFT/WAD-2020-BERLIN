#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include <pthread.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PARTICLES_COUNT 200000
#define GRAVITY -0.9f

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif

Camera3D camera = {{55, 54, 55}, {0, 0.2, 0}, {0, 1, 0}, 45.0f, CAMERA_PERSPECTIVE};

float particles_x[PARTICLES_COUNT] = {0};
float particles_y[PARTICLES_COUNT] = {0};
float particles_z[PARTICLES_COUNT] = {0};

float particles_speed_x[PARTICLES_COUNT] = {0};
float particles_speed_y[PARTICLES_COUNT] = {0};
float particles_speed_z[PARTICLES_COUNT] = {0};

float velocity_x_z_create() {
    return GetRandomValue(-10, 10) / 100.0f;
}

float velocity_y_create() {
    return GetRandomValue(-100, 100) / 100.0f;
}


int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Energy Consumption - SOA");
    for(int i = 0; i < PARTICLES_COUNT; i++) {
        particles_speed_x[i] = velocity_x_z_create();
        particles_speed_z[i] = velocity_x_z_create();
        particles_speed_y[i] = velocity_y_create();
    }

    SetCameraMode(camera, CAMERA_ORBITAL);

    SetTargetFPS(60);

    pthread_t update_x, update_y, update_z;

    while(!WindowShouldClose()){
        UpdateCamera(&camera);
        ClearBackground(RED);
        float scalar_delta = GetFrameTime() * GRAVITY;

        // Update particles position
        for(int i = 0; i < PARTICLES_COUNT; i++) {
            particles_x[i] += particles_speed_x[i];
        }

        for(int i = 0; i < PARTICLES_COUNT; i++) {
            particles_z[i] += particles_speed_z[i];
        }
        for(int i = 0; i < PARTICLES_COUNT; i++) {
            particles_speed_y[i] += scalar_delta;
        }

        for(int i = 0; i < PARTICLES_COUNT; i++){
            particles_y[i] += particles_speed_y[i];
        }

        for(int i = 0; i < PARTICLES_COUNT; i++) {
            if (particles_y[i] <= 0) {
                particles_y[i] = 0;
                particles_x[i] = 0;
                particles_z[i] = 0;

                particles_speed_x[i] = velocity_x_z_create();
                particles_speed_z[i] = velocity_x_z_create();
                particles_speed_y[i] = velocity_y_create();
            }
        }

        BeginDrawing();
        {

//             unsigned int i = 0;
//             for(int j = 8000; j < PARTICLES_COUNT; j += 8000) {
//                 BeginMode3D(camera);
//                 {
//                     for(; i < j; i++){
//                         DrawBillboard(camera, texture, (Vector3){particles_x[i], particles_y[i], particles_z[i]}, 1.0f, WHITE);
//                     }
//                 }EndMode3D();
//             }
            BeginMode3D(camera);
            DrawGrid(10, 10);
            EndMode3D();

            DrawFPS(10, 10);
            DrawText("SOA", 10, 50, 24, GREEN);
        }
        EndDrawing();
    }

    return 0;
}
