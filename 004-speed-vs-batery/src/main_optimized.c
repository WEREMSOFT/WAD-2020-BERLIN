#include "config.h"

float velocity_x_z_create() {
    return GetRandomValue(-10, 10) / 100.0f;
}

float velocity_y_create() {
    return GetRandomValue(-100, 100) / 100.0f;
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Energy Consumption - OPTIMIZED");

    char STRING_NUMBER_OF_PARTICLES[100];
    snprintf(STRING_NUMBER_OF_PARTICLES, 100, "# of particles: %d", PARTICLES_COUNT);

    Image checked = GenImageChecked(2, 2, 2, 1, RED, GREEN);
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);

    float *particles_x = (float *) calloc(sizeof(float), PARTICLES_COUNT);
    float *particles_y = (float *) calloc(sizeof(float), PARTICLES_COUNT);
    float *particles_z = (float *) calloc(sizeof(float), PARTICLES_COUNT);

    float *particles_speed_x = (float *) calloc(sizeof(float), PARTICLES_COUNT);
    float *particles_speed_y = (float *) calloc(sizeof(float), PARTICLES_COUNT);
    float *particles_speed_z = (float *) calloc(sizeof(float), PARTICLES_COUNT);

    for(int i = 0; i < PARTICLES_COUNT; i++) {
        particles_speed_x[i] = velocity_x_z_create();
        particles_speed_z[i] = velocity_x_z_create();
        particles_speed_y[i] = velocity_y_create();
    }

    Camera3D camera = {{55, 54, 55}, {0, 0.2, 0}, {0, 1, 0}, 45.0f, CAMERA_PERSPECTIVE};

    SetCameraMode(camera, CAMERA_ORBITAL);

    SetTargetFPS(FRAMES_PER_SECOND);

    pthread_t update_x, update_y, update_z;

    while(!WindowShouldClose()){
        UpdateCamera(&camera);
        ClearBackground(DARKBLUE);
        float scalar_delta = GetFrameTime() * GRAVITY_SCALAR;

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
        BeginDrawing();{
#ifdef DRAW_PARTICLES
            BeginMode3D(camera);
            {
                Vector3 particle = {0};
                for(int i = 0; i < MAX_PARTICLES_TO_DRAW; i++){
                    particle.x = particles_x[i];
                    particle.y = particles_y[i];
                    particle.z = particles_z[i];
                    DrawBillboard(camera, texture, particle, 1.0f, WHITE);
                }
            }EndMode3D();
#endif
            BeginMode3D(camera);
                DrawGrid(10, 10);
            EndMode3D();

            DrawText("OPTIMIZED", 10, 50, 24, RED);
            DrawFPS(10, 10);
            DrawText(STRING_NUMBER_OF_PARTICLES, 10, 75, 24, BLACK);
        }EndDrawing();
    }

    return 0;
}
