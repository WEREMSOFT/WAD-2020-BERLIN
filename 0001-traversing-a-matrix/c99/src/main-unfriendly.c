#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int main() {
    printf("allocating %ld kbytes\n", (sizeof(matrix_t) * MATRIX_SIZE * MATRIX_SIZE) / 1024);
    matrix_t *matrix = (matrix_t *) malloc(sizeof(matrix_t) * MATRIX_SIZE * MATRIX_SIZE);

    if (matrix == NULL) {
        perror("Error allocation memory: ");
        return -1;
    }

    for (int j = 0; j < MATRIX_SIZE; j++) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            matrix[i * MATRIX_SIZE + j] = i + j;
        }
    }

    matrix_t result = matrix[(MATRIX_SIZE - 1) * (MATRIX_SIZE - 1) + MATRIX_SIZE - 1];

    free(matrix);
    return result;
}
