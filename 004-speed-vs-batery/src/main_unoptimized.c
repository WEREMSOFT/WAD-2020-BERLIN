#include "config.h"
#include "benchmark_utils.h"

#define GRAVITY (Vector3){0, GRAVITY_SCALAR, 0}

Vector3 velocity_create() {
    return (Vector3){GetRandomValue(-5, 5), GetRandomValue(1, 25), GetRandomValue(-5, 5)};
}

typedef struct GameObject {
    int index;
    Vector3 position;
    Vector3 velocity;
	void *next;
    void* cadorna[10];
} GameObject;

GameObject *particles;

void UpdateDrawFrame() {
    ClearBackground(RED);
    float delta_scalar = GetFrameTime();
#ifdef USE_VECTOR_FUNCTIONS
    Vector3 delta = Vector3Scale(GRAVITY, delta_scalar);
#endif
#ifdef UPDATE_CAMERA
    UpdateCamera(&camera);
#endif
    // Update particles position
    GameObject* particle = particles;
    while(particle){
#ifdef USE_VECTOR_FUNCTIONS
        particle->velocity = Vector3Add(particle->velocity, delta);
        particle->position = Vector3Add(particle->position, Vector3Scale(particle->velocity, delta_scalar));
#else
        float G = GRAVITY_SCALAR * delta_scalar;
        particle->velocity.y += GRAVITY_SCALAR * delta_scalar;
        particle->position.x += particle->velocity.x * delta_scalar;
        particle->position.y += particle->velocity.y * delta_scalar;
        particle->position.z += particle->velocity.z * delta_scalar;
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
                particle = particles;
                int max_particles = MAX_PARTICLES_TO_DRAW;
                while(max_particles--){
                    DrawBillboard(camera, texture, particle->position, 1.0f, WHITE);
                    particle = particle->next;
                }
            #endif
            DrawGrid(10, 10);
        }EndMode3D();

        DrawFPS(10, 10);
        DrawText(STRING_NUMBER_OF_PARTICLES, 10, 75, 24, BLACK);

        DrawText("UNOPTIMIZED", 10, 50, 24, BLACK);

        draw_fps_graph();

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
            particle->index = i;
            particle->next = NULL;
            if(i == 0) {
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

    GameObject* particle = particles;

    while(particle){
        particles = particle->next;
        free(particle);
        particle = particles;
    }

    return 0;
}
