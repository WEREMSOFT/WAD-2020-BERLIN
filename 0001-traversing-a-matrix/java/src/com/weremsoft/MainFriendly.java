package com.weremsoft;

public class MainFriendly {
    public static void main(String[] args) {

        final int MATRIX_SIZE = 10000;

        long result = 0;

        char[][] arrNumbers = new char[MATRIX_SIZE][MATRIX_SIZE];

        long begin = System.currentTimeMillis();
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                result += arrNumbers[i][j];
            }
        }
        long end = System.currentTimeMillis();

        double cache_unfriendly = (end - begin);

        System.out.println("Cache Friendly elapsed time: " + cache_unfriendly);
        System.out.println("Result: " + result);
    }
}
