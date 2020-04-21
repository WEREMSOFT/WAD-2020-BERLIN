#include "config.h"

typedef struct PhysicObject {
    Vector3 position;
    Vector3 velocity;
} PhysicObject;

Vector3 velocity_create() {
    return (Vector3) {
            GetRandomValue(-10, 10) / 100.0f,
            GetRandomValue(-100, 100) / 100.0f,
            GetRandomValue(-10, 10) / 100.0f};
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Energy Consumption - AOS");

    Image checked = GenImageChecked(4, 4, 2, 2, RED, GREEN);
    Texture2D texture = LoadTextureFromImage(checked);
    UnloadImage(checked);
    printf("Allocating %lu bytes\n", sizeof(Vector3) * PARTICLES_COUNT * 2);

    PhysicObject *particles = (PhysicObject *) malloc(sizeof(PhysicObject) * PARTICLES_COUNT);

    for (unsigned long int i = 0; i < PARTICLES_COUNT; i++) {
        particles[i].velocity = velocity_create();
    }

    Camera3D camera = {{55, 54, 55}, {0, 0.2, 0}, {0, 1, 0}, 45.0f, CAMERA_PERSPECTIVE};

    SetCameraMode(camera, CAMERA_ORBITAL);

    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        float scalar_delta = GetFrameTime() * GRAVITY;
        // Update particles position
        for (uint_fast64_t i = 0; i < PARTICLES_COUNT; i++) {
            particles[i].velocity.y += scalar_delta;

            particles[i].position.y += particles[i].velocity.y;
            particles[i].position.x += particles[i].velocity.x;
            particles[i].position.z += particles[i].velocity.z;

            if (particles[i].position.y <= 0) {
                particles[i].position = (Vector3){0, 0, 0, 0};
                particles[i].velocity = velocity_create();
            }
        }

        ClearBackground(GREEN);
        UpdateCamera(&camera);
        BeginDrawing();
        {
            BeginMode3D(camera);
            {
//                for (int j = 0; j < PARTICLES_COUNT; j += 1) {
//                    DrawBillboard(camera, texture, particles[j], 1.0f, WHITE);
//                }
                DrawGrid(10, 10);
            }
            EndMode3D();

            DrawFPS(10, 10);
            DrawText("AOS - OOP", 10, 50, 24, RED);
        }
        EndDrawing();
    }
    free(particles);
    UnloadTexture(texture);
    return 0;
}
