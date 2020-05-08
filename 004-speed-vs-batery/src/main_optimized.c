#include "config.h"
#include "benchmark_utils.h"

float velocity_x_z_create() {
    return GetRandomValue(-5, 5);
}

float velocity_y_create() {
    return GetRandomValue(1, 25);
}

float *particles_x;
float *particles_y;
float *particles_z;

float *particles_speed_x;
float *particles_speed_y;
float *particles_speed_z;

void UpdateDrawFrame() {
#ifdef UPDATE_CAMERA
    UpdateCamera(&camera);
#endif
    ClearBackground(DARKBLUE);
    float delta_scalar = GetFrameTime();

    // Update particles position
#ifdef SEPARATED_LOOPS
    for(int i = 0; i < PARTICLES_COUNT; i++) {
        particles_x[i] += particles_speed_x[i];
    }

    for(int i = 0; i < PARTICLES_COUNT; i++) {
        particles_z[i] += particles_speed_z[i];
    }

    for(int i = 0; i < PARTICLES_COUNT; i++) {
        particles_speed_y[i] += scalar_delta;
    }

    for(int i = 0; i < PARTICLES_COUNT; i++) {
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
#else
    for (int i = 0; i < PARTICLES_COUNT; i++) {
        particles_x[i] += particles_speed_x[i] * delta_scalar;
        particles_z[i] += particles_speed_z[i] * delta_scalar;
        particles_speed_y[i] += GRAVITY_SCALAR * delta_scalar;
        particles_y[i] += particles_speed_y[i] * delta_scalar;
        if (particles_y[i] <= 0) {
            particles_y[i] = 0;
            particles_x[i] = 0;
            particles_z[i] = 0;

            particles_speed_x[i] = velocity_x_z_create();
            particles_speed_z[i] = velocity_x_z_create();
            particles_speed_y[i] = velocity_y_create();
        }
    }
#endif

    BeginDrawing();
    {
        BeginMode3D(camera);
        {
        #ifdef DRAW_PARTICLES
            Vector3 particle = {0};
            for(int i = 0; i < MAX_PARTICLES_TO_DRAW; i++){
                particle.x = particles_x[i];
                particle.y = particles_y[i];
                particle.z = particles_z[i];
                DrawBillboard(camera, texture, particle, 1.0f, WHITE);
            }
        #endif
            DrawGrid(10, 10);
        }EndMode3D();


        DrawText("OPTIMIZED", 10, 50, 24, RED);
        DrawFPS(10, 10);
        DrawText(STRING_NUMBER_OF_PARTICLES, 10, 75, 24, BLACK);
        draw_fps_graph();
    }
    EndDrawing();
}

int main() {
    particles_x = (float *) calloc(sizeof(float), PARTICLES_COUNT);
    particles_y = (float *) calloc(sizeof(float), PARTICLES_COUNT);
    particles_z = (float *) calloc(sizeof(float), PARTICLES_COUNT);

    particles_speed_x = (float *) calloc(sizeof(float), PARTICLES_COUNT);
    particles_speed_y = (float *) calloc(sizeof(float), PARTICLES_COUNT);
    particles_speed_z = (float *) calloc(sizeof(float), PARTICLES_COUNT);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Energy Consumption - OPTIMIZED");

    snprintf(STRING_NUMBER_OF_PARTICLES, 100, "# of particles: %d", PARTICLES_COUNT);

    Image checked = GenImageChecked(2, 2, 2, 1, RED, GREEN);
    texture = LoadTextureFromImage(checked);
    UnloadImage(checked);

    for (int i = 0; i < PARTICLES_COUNT; i++) {
        particles_speed_x[i] = velocity_x_z_create();
        particles_speed_z[i] = velocity_x_z_create();
        particles_speed_y[i] = velocity_y_create();
    }

    SetCameraMode(camera, CAMERA_ORBITAL);

    SetTargetFPS(TARGET_FRAMES_PER_SECOND);

#if defined(PLATFORM_WEB)
    printf("es web\n");
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
#ifdef RUN_ONLY_COUNT_FRAMES
    int frame_count = COUNT_FRAMES;
    while (!WindowShouldClose() && frame_count--) {
#else
    while (!WindowShouldClose()) {
#endif
        UpdateDrawFrame();
    }
#endif

    free(particles_x);
    free(particles_y);
    free(particles_z);

    free(particles_speed_x);
    free(particles_speed_y);
    free(particles_speed_z);

    return 0;
}
