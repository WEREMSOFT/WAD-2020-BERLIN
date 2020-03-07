#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_SIZE 40000
// if we change this to char, the difference will be smaller
typedef unsigned int matrix_t;

int main() {
    long double result = 0;

    printf("allocating %ld bytes\n", sizeof(matrix_t) * MATRIX_SIZE * MATRIX_SIZE);
    matrix_t *matrix = (matrix_t *) malloc(sizeof(matrix_t) * MATRIX_SIZE * MATRIX_SIZE);

    if (matrix == NULL) {
        perror("Error allocation memory: ");
        return -1;
    }

    srand(time(NULL));
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i * MATRIX_SIZE + j] = (matrix_t) rand();
        }
    }

    time_t begin = clock();
    for (int j = 0; j < MATRIX_SIZE; j++) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            result += matrix[i * MATRIX_SIZE + j];
        }
    }
    time_t end = clock() - begin;
    double time_cache_un_friendly = ((double) end);
    printf("result: %Lf\n", result);

    result = 0;
    begin = clock();
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
                result += matrix[i * MATRIX_SIZE + j];
        }
    }

    end = clock() - begin;
    double time_cache_friendly = ((double) end);
    printf("result: %Lf\n", result);

    printf("elapsed time relation (chache_UNfriendy / chache_friendy) %f\n", time_cache_un_friendly / time_cache_friendly);

    free(matrix);
    return 0;
}
