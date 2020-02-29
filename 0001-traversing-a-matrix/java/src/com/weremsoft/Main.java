package com.weremsoft;
public class Main {
    public static void main(String[] args) {

        final int ROW_MAX = 10000;
        final int COL_MAX = 10000;

        double result = 0;

        float[][] arrNumbers = new float[ROW_MAX][COL_MAX];

        for (int j = 0; j < COL_MAX; j++) {
            for (int i = 0; i < ROW_MAX; i++) {
                arrNumbers[i][j] = (float) Math.random();
            }
        }

        long begin = System.nanoTime();
        for (int i = 0; i < ROW_MAX; i++) {
            for (int j = 0; j < COL_MAX; j++) {
                result += arrNumbers[i][j];
            }
        }
        long end = System.nanoTime();

        double cache_friendly = (end - begin) / 100000 ;

        System.out.println("Cache firendly lapsed time: " + cache_friendly);

        result = 0;

        begin = System.nanoTime();
        for (int j = 0; j < COL_MAX; j++) {
            for (int i = 0; i < ROW_MAX; i++) {
                result += arrNumbers[i][j];
            }
        }
        end = System.nanoTime();

        double cache_unfriendly = (end - begin) / 100000;

        System.out.println("Cache UNfriendly elapsed time: " + cache_unfriendly);

        System.out.println("Column Mayor / Row Mayor " + cache_unfriendly / cache_friendly);

    }
}
