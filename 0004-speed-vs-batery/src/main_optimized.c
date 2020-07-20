#include "config.h"
#include "benchmark_utils.h"
#include <flecs.h>

ecs_world_t *world;

#define GRAVITY (Vector3){0, GRAVITY_SCALAR, 0}

Vector3 velocity_create() {
    return (Vector3){GetRandomValue(-5, 5), GetRandomValue(1, 25), GetRandomValue(-5, 5)};
}

typedef struct GameObject {
    Vector3 position;
    Vector3 velocity;
} GameObject;

GameObject *particles;

void UpdateDrawFrame() {
    ClearBackground(DARKBLUE);
    float delta_scalar = GetFrameTime();
#ifdef USE_VECTOR_FUNCTIONS
    Vector3 delta = Vector3Scale(GRAVITY, delta_scalar);
#endif
#ifdef UPDATE_CAMERA
    UpdateCamera(&camera);
#endif
    // Update particles position
    for(int i = 0; i < PARTICLES_COUNT; i++){
#ifdef USE_VECTOR_FUNCTIONS
        particles[i].velocity = Vector3Add(particle[i].velocity, delta);
        particles[i].position = Vector3Add(particle[i].position, Vector3Scale(particle[i].velocity, delta_scalar));
#else
        particles[i].velocity.y += GRAVITY_SCALAR * delta_scalar;
        particles[i].position.x += particles[i].velocity.x * delta_scalar;
        particles[i].position.y += particles[i].velocity.y * delta_scalar;
        particles[i].position.z += particles[i].velocity.z * delta_scalar;
#endif
        if(particles[i].position.y <= 0) {
            particles[i].position = Vector3Zero();
            particles[i].velocity = velocity_create();
        }
    }

    BeginDrawing();
    {
        BeginMode3D(camera);
        {
            #ifdef DRAW_PARTICLES
                int max_particles = MAX_PARTICLES_TO_DRAW;
                while(max_particles--){
                    DrawBillboard(camera, texture, particles[max_particles].position, 1.0f, WHITE);
                }
            #endif
            DrawGrid(10, 10);
        }EndMode3D();

        DrawFPS(10, 10);
        DrawText(STRING_NUMBER_OF_PARTICLES, 10, 75, 24, BLACK);

        DrawText("OPTIMIZED", 10, 50, 24, BLACK);

        draw_fps_graph();

    }EndDrawing();
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Energy Consumption - OPTIMIOZED");
    snprintf(STRING_NUMBER_OF_PARTICLES, 100, "# of particles: %d", PARTICLES_COUNT);

    Image checked = GenImageChecked(2, 2, 2, 1, RED, GREEN);
    texture = LoadTextureFromImage(checked);
    UnloadImage(checked);

    particles = (GameObject *) calloc(sizeof(GameObject), PARTICLES_COUNT);

    for(int i = 0; i < PARTICLES_COUNT; i++){
        particles[i].velocity = velocity_create();
    }
    
    SetCameraMode(camera, CAMERA_ORBITAL);

    SetTargetFPS(TARGET_FRAMES_PER_SECOND);

#if defined(PLATFORM_WEB)
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

    free(particles);
    return 0;
}
