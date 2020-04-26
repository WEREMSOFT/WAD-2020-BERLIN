#include "config.h"

#define GRAVITY (Vector3){0, GRAVITY_SCALAR, 0}

Vector3 velocity_create() {
    return (Vector3){GetRandomValue(-10, 10) / 100.0f, GetRandomValue(-100, 100) / 100.0f, GetRandomValue(-10, 10) / 100.0f};
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Energy Consumption - UNOPTIMIOZED");

    Image checked = GenImageChecked(2, 2, 2, 1, RED, GREEN);
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);



    Vector3 *particles = (Vector3*) calloc(sizeof(Vector3), PARTICLES_COUNT);
    Vector3 *particles_speed = (Vector3*) calloc(sizeof(Vector3), PARTICLES_COUNT);

    for(unsigned long int i = 0; i < PARTICLES_COUNT; i++){
        particles_speed[i] = velocity_create();
    }

    Camera3D camera = {{55, 54, 55}, {0, 0.2, 0}, {0, 1, 0}, 45.0f, CAMERA_PERSPECTIVE};

    SetCameraMode(camera, CAMERA_ORBITAL);

    SetTargetFPS(FRAMES_PER_SECOND);

    while(!WindowShouldClose()){
        ClearBackground(RED);
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
#ifdef DRAW_PARTICLES
                 BeginMode3D(camera);
                 {
                     for(int i = 0; i < MAX_PARTICLES_TO_DRAW; i++){
                         DrawBillboard(camera, texture, particles[i], 1.0f, WHITE);
                     }
                 }EndMode3D();
#endif
            BeginMode3D(camera);
                DrawGrid(10, 10);
            EndMode3D();

            DrawFPS(10, 10);
            DrawText("UNOPTIMIZED", 10, 50, 24, BLACK);
        }EndDrawing();
    }

    return 0;
}
