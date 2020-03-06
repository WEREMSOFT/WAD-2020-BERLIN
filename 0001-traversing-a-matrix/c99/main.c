#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_SIZE 40000
// if we change this to char, the difference will be smaller
typedef unsigned int matrix_t;

int main() {

    printf("allocating %ld bytes\n", sizeof(matrix_t) * MATRIX_SIZE * MATRIX_SIZE);

    matrix_t *matrix = (matrix_t *) malloc(sizeof(matrix_t) * MATRIX_SIZE * MATRIX_SIZE);

    if (matrix == NULL) {
        perror("Error allocation memory: ");
        return -1;
    }

    long double result = 0;

    srand(time(NULL));

    long long loops = 0;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i * MATRIX_SIZE + j] = (matrix_t) rand();
            loops++;
        }
    }
    printf("loops: %lld\n", loops);

    time_t begin = clock();
    for (int j = 0; j < MATRIX_SIZE; j++) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            result += matrix[i * MATRIX_SIZE + j];
        }
    }
    time_t end = clock() - begin;
    printf("result: %Lf\n", result);

    double time_col_mayor = ((double) end);

    srand(time(NULL));


    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i * MATRIX_SIZE + j] = (matrix_t) rand();
        }
    }

    result = 0;

    begin = clock();
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
                result += matrix[i * MATRIX_SIZE + j];
        }
    }

    end = clock() - begin;

    printf("result: %Lf\n", result);

    double time_row_mayor = ((double) end);

    printf("elapsed time relation (col_mayor / row mayor) %f\n",   time_col_mayor / time_row_mayor);

    free(matrix);
    return 0;
}
