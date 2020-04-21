#include "config.h"

Camera3D camera = {{55, 54, 55}, {0, 0.2, 0}, {0, 1, 0}, 45.0f, CAMERA_PERSPECTIVE};

float velocity_x_z_create() {
    return GetRandomValue(-10, 10) / 100.0f;
}

float velocity_y_create() {
    return GetRandomValue(-100, 100) / 100.0f;
}


int main() {

    printf("Allocating %lu bytes\n", sizeof(float) * PARTICLES_COUNT * 6);

    float *buffer = (float *) malloc(sizeof(float) * PARTICLES_COUNT * 6);
    if (buffer == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    float *particles_x = buffer;
    float *particles_y = &buffer[PARTICLES_COUNT];
    float *particles_z = &buffer[PARTICLES_COUNT * 2];

    float *particles_speed_x = &buffer[PARTICLES_COUNT * 3];
    float *particles_speed_y = &buffer[PARTICLES_COUNT * 4];
    float *particles_speed_z = &buffer[PARTICLES_COUNT * 5];




    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Energy Consumption - SOA");

    Image checked = GenImageChecked(4, 4, 2, 2, RED, GREEN);
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);

    for (int i = 0; i < PARTICLES_COUNT; i++) {
        particles_speed_x[i] = velocity_x_z_create();
        particles_speed_z[i] = velocity_x_z_create();
        particles_speed_y[i] = velocity_y_create();
    }

    SetCameraMode(camera, CAMERA_ORBITAL);

    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        float scalar_delta = GetFrameTime() * GRAVITY;

        for (uint_fast64_t i = 0; i < PARTICLES_COUNT; i++) {
            particles_speed_y[i] += scalar_delta;
        }

        for (uint_fast64_t i = 0; i < PARTICLES_COUNT; i++) {
            particles_x[i] += particles_speed_x[i];
            particles_y[i] += particles_speed_y[i];
            particles_z[i] += particles_speed_z[i];

            if (particles_y[i] <= 0) {
                particles_y[i] = 0;
                particles_x[i] = 0;
                particles_z[i] = 0;

                particles_speed_x[i] = velocity_x_z_create();
                particles_speed_z[i] = velocity_x_z_create();
                particles_speed_y[i] = velocity_y_create();
            }
        }

        UpdateCamera(&camera);
        ClearBackground(RED);
        BeginDrawing();
        {

            BeginMode3D(camera);
            {
//                for (int i = 0; i < PARTICLES_COUNT; i++) {
//                    DrawBillboard(camera, texture, (Vector3){particles_x[i], particles_y[i], particles_z[i]}, 1.0f, WHITE);
//                }
                DrawGrid(10, 10);
            }
            EndMode3D();

            DrawFPS(10, 10);
            DrawText("SOA - DOD", 10, 50, 24, GREEN);
        }
        EndDrawing();
    }

    free(buffer);

    UnloadTexture(texture);
    return 0;
}
