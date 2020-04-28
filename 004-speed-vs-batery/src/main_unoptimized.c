#include "config.h"

#define GRAVITY (Vector3){0, GRAVITY_SCALAR, 0}

Vector3 velocity_create() {
    return (Vector3){GetRandomValue(-10, 10) / 100.0f, GetRandomValue(-100, 100) / 100.0f, GetRandomValue(-10, 10) / 100.0f};
}

typedef struct GameObject {
    Vector3 position;
    Vector3 velocity;
#ifdef USE_LARGE_STRUCTURES
    LARGE_STRUCTURE_TYPE cadorna[LARGE_STRUCTURE_SIZE]
#endif
} GameObject;

GameObject *particles;

void UpdateDrawFrame() {
    ClearBackground(RED);
    Vector3 delta = Vector3Scale(GRAVITY, GetFrameTime());
    UpdateCamera(&camera);
    // Update particles position
    for(unsigned int i = 0; i < PARTICLES_COUNT; i++){
#ifdef USE_VECTOR_FUNCTIONS
        particles[i].velocity = Vector3Add(particles[i].velocity, delta);
        particles[i].position = Vector3Add(particles[i].position, particles[i].velocity);
#else
        particles[i].velocity.x += delta.x;
        particles[i].velocity.y += delta.y;
        particles[i].velocity.z += delta.z;
        particles[i].position.x += particles[i].velocity.x;
        particles[i].position.y += particles[i].velocity.y;
        particles[i].position.z += particles[i].velocity.z;
#endif
        if(particles[i].position.y <= 0) {
            particles[i].position = Vector3Zero();
            particles[i].velocity = velocity_create();
        }
    }

    BeginDrawing();{
#ifdef DRAW_PARTICLES
        BeginMode3D(camera);
        {
            for(int i = 0; i < MAX_PARTICLES_TO_DRAW; i++){
                DrawBillboard(camera, texture, particles[i].position, 1.0f, WHITE);
            }
        }EndMode3D();
#endif
        BeginMode3D(camera);
        DrawGrid(10, 10);
        EndMode3D();

        DrawFPS(10, 10);
        DrawText(STRING_NUMBER_OF_PARTICLES, 10, 75, 24, BLACK);

        DrawText("UNOPTIMIZED", 10, 50, 24, BLACK);

    }EndDrawing();
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Energy Consumption - UNOPTIMIOZED");
    snprintf(STRING_NUMBER_OF_PARTICLES, 100, "# of particles: %d", PARTICLES_COUNT);

    Image checked = GenImageChecked(2, 2, 2, 1, RED, GREEN);
    texture = LoadTextureFromImage(checked);
    UnloadImage(checked);

    // TODO: Create pointers instead of arrays

    particles = (GameObject *) calloc(sizeof(GameObject), PARTICLES_COUNT);

    for(unsigned long int i = 0; i < PARTICLES_COUNT; i++){
        particles[i].velocity = velocity_create();
    }

    SetCameraMode(camera, CAMERA_ORBITAL);

    SetTargetFPS(FRAMES_PER_SECOND);

#if defined(PLATFORM_WEB)
    printf("es web\n");
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif

    return 0;
}
