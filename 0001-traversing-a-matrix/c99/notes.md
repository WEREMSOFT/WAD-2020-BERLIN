#include <stdio.h>
#include <pthread.h>
#include <time.h>

void *my_turn(void *param) {
    int *i = (int *) param;

    for (*i = 0; *i < 1000000000; (*i)++) {
    }
    return NULL;
}

int main() {
    time_t begin, end;
    int y, m, a, b;

    y = m = b = a = 0;
    begin = time(NULL);
#define __EMSCRIPTEN_PTHREADS__
#undef __EMSCRIPTEN_PTHREADS__
#ifdef __EMSCRIPTEN_PTHREADS__
    pthread_t my_t, your_t, a_t, b_t;
    printf("Threads ARE supported!!!\n");

    if(pthread_create(&my_t, NULL, my_turn, &m)){
        perror("Thread creation failed");
        return 1;
    }

    if(pthread_create(&your_t, NULL, my_turn, &y)){
        perror("Thread creation failed");
        return 1;
    }

    if(pthread_create(&a_t, NULL, my_turn, &a)){
        perror("Thread creation failed");
        return 1;
    }

    if(pthread_create(&b_t, NULL, my_turn, &b)){
        perror("Thread creation failed");
        return 1;
    }

    if(pthread_join(my_t, NULL)){
        perror("Thread join failed");
        return 1;
    }
    if(pthread_join(your_t, NULL)){
        perror("Thread join failed");
        return 1;
    }
    if(pthread_join(a_t, NULL)){
        perror("Thread join failed");
        return 1;
    }
    if(pthread_join(b_t, NULL)){
        perror("Thread join failed");
        return 1;
    }
#else
    printf("Threads NOT supported!!!\n");
    my_turn(&m);
    my_turn(&y);
    my_turn(&a);
    my_turn(&b);
#endif

    end = time(NULL);

    printf("mine value %d\n", m);
    printf("yours value %d\n", y);
    printf("mine value %d\n", a);
    printf("yours value %d\n", b);
    printf("Elapsed time %f\n", difftime(end, begin));

    return 0;
}
