#include <iostream>
#include "config.h"

int main() {
    auto matNumbers = new matrix_t[MATRIX_SIZE][MATRIX_SIZE];

    for (int j = 0; j < MATRIX_SIZE; j++) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            matNumbers[i][j] = i + j;
        }
    }

    return matNumbers[MATRIX_SIZE - 1][MATRIX_SIZE - 1];
}

