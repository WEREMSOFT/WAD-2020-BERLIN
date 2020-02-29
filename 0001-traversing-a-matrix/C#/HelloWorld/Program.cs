using System;
using System.Diagnostics;

namespace HelloWorld
{
    class Program
    {
        static void Main(string[] args)
        {

            var cad = new Cadorna();

            cad.sarlanga = "sarasa";

            const int MATRIX_SIZE = 20000;
            int[,] matrix = new int[MATRIX_SIZE, MATRIX_SIZE];

            long result = 0;

            Random rnd = new Random();
            Stopwatch sw = new Stopwatch();



            for(int i = 0; i < MATRIX_SIZE; i++)
            {
                for (int j = 0; j < MATRIX_SIZE; j++)
                {
                    matrix[i, j] = rnd.Next();
                }
            }

            sw.Start();

            for (int i = 0; i < MATRIX_SIZE; i++)
            {
                for (int j = 0; j < MATRIX_SIZE; j++)
                {
                    result += matrix[i, j];
                }
            }

            sw.Stop();

            Console.WriteLine("Hello World! {0}. Elapsed: {1}", result, sw.ElapsedMilliseconds);

            sw.Reset();

            sw.Start();

            for (int i = 0; i < MATRIX_SIZE; i++)
            {
                for (int j = 0; j < MATRIX_SIZE; j++)
                {
                    result += matrix[j, i];
                }
            }

            sw.Stop();

            Console.WriteLine("Hello World! {0}. Elapsed: {1}", result, sw.ElapsedMilliseconds);
        }
    }

    class Cadorna
    {
        public String sarlanga;
    }

}
