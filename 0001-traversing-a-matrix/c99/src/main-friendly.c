#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"

int main() {
    long double result = 0;

    printf("allocating %ld kbytes\n", (sizeof(matrix_t) * MATRIX_SIZE * MATRIX_SIZE) / 1024);
    matrix_t *matrix = (matrix_t *) malloc(sizeof(matrix_t) * MATRIX_SIZE * MATRIX_SIZE);

    if (matrix == NULL) {
        perror("Error allocation memory: ");
        return -1;
    }
    srand(time(NULL));
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i * MATRIX_SIZE + j] = i + j;
        }
    }
    printf("result: %Lf\n", result);

    free(matrix);
    return 0;
}
