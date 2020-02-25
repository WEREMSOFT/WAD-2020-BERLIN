#include <iostream>
#include <chrono>

#define MATRIX_SIZE 20000

typedef unsigned int matrix_t;

int main() {
    auto matNumbers = new matrix_t[MATRIX_SIZE][MATRIX_SIZE];

    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            matNumbers[i][j] = random();
        }
    }

    float result = 0;

    clock_t begin = std::clock();
    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            result += matNumbers[i][j];
        }
    }

    clock_t end = std::clock();

    const double elapsed_time_row_mayor = ((double)(end - begin)) / CLOCKS_PER_SEC;

    printf("Sum: %f\n", result);

    result = 0;

    begin = std::clock();
    for(int j = 0; j < MATRIX_SIZE; j++){
        for(int i = 0; i < MATRIX_SIZE; i++){
            result += matNumbers[i][j];
        }
    }

    end = std::clock();

    const double elapsed_time_col_mayor = ((double)(end - begin)) / CLOCKS_PER_SEC;

    printf("Sum: %f\n", result);
    printf("elapsed time relation (col_mayor / row mayor) %f seconds\n", elapsed_time_col_mayor / elapsed_time_row_mayor);

    return 0;
}

