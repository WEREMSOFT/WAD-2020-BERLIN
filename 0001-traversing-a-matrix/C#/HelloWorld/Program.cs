using System;
using System.Diagnostics;

namespace HelloWorld
{
    class Program
    {
        static int Main(string[] args)
        {


            const uint MATRIX_SIZE = 40000;
            char[,] matrix = new char[MATRIX_SIZE, MATRIX_SIZE];


            for (int i = 0; i < MATRIX_SIZE; i++)
            {
                for (int j = 0; j < MATRIX_SIZE; j++)
                {
                    matrix[j, i] = (char)(i + j);
                }
            }

            return matrix[MATRIX_SIZE - 1, MATRIX_SIZE - 1];
        }
    }


}
