#include "config.h"

#define GRAVITY (Vector3){0, GRAVITY_SCALAR, 0}

Vector3 velocity_create() {
    return (Vector3){GetRandomValue(-10, 10) / 100.0f, GetRandomValue(-100, 100) / 100.0f, GetRandomValue(-10, 10) / 100.0f};
}

typedef struct GameObject {
    Vector3 position;
    Vector3 velocity;
	void *next;
} GameObject;

GameObject *particles;

void UpdateDrawFrame() {
    ClearBackground(RED);
    Vector3 delta = Vector3Scale(GRAVITY, GetFrameTime());
    UpdateCamera(&camera);
    // Update particles position
    GameObject* particle = particles;
    while(particle){
#ifdef USE_VECTOR_FUNCTIONS
        particle->velocity = Vector3Add(particle->velocity, delta);
        particle->position = Vector3Add(particle->position, particle->velocity);
#else
        particles->velocity.x += delta.x;
        particles->velocity.y += delta.y;
        particles->velocity.z += delta.z;
        particles->position.x += particles->velocity.x;
        particles->position.y += particles->velocity.y;
        particles->position.z += particles->velocity.z;
#endif
        if(particle->position.y <= 0) {
            particle->position = Vector3Zero();
            particle->velocity = velocity_create();
        }
        particle = particle->next;
    }

    BeginDrawing();
    {
        BeginMode3D(camera);
        {
            #ifdef DRAW_PARTICLES
                {
                    int i = MAX_PARTICLES_TO_DRAW;
                    GameObject *particle = particles;
                    while(i--){
                        DrawBillboard(camera, texture, particle->position, 1.0f, WHITE);
                        particle = particle->next;
                    }
                }
            #endif
            DrawGrid(10, 10);
        }EndMode3D();

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

    {
        GameObject* last_particle;
        // TODO: Create pointers instead of arrays
        for(int i = 0; i < PARTICLES_COUNT; i++){
            GameObject* particle = (GameObject *) calloc(sizeof(GameObject), 1);
            particle->next = NULL;
            if(!particles) {
                particles = particle;
                last_particle = particle;
            } else {
                last_particle->next = particle;
                last_particle = particle;
            }
        }
    }

    {
        GameObject* particle = particles;
        while(particle){
            particle->velocity = velocity_create();
            particle = (GameObject *)particle->next;
        }
    }

    SetCameraMode(camera, CAMERA_ORBITAL);

    SetTargetFPS(FRAMES_PER_SECOND);

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

    GameObject* particle = particles;

    while(particle){
        particles = particle->next;
        free(particle);
        particle = particles;
    }

    return 0;
}
