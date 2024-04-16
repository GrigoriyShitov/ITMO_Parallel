#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define M1SIZE (N)
#define M2SIZE (N / 2)
#define RFACTOR (1.24733)

void gnomeSort(double *array, int size);

int main(int argc, char *argv[])
{
    int i, N, j;
    unsigned int seed;
    double sum = 0;
    struct timeval T1, T2;
    long delta_ms;
    FILE *resultOfTest = fopen("Results.txt", "a");
    N = atoi(argv[1]); // N равен первому параметру командной строки
    double *restrict M1 = (double *)calloc(M1SIZE, sizeof(double));
    double *restrict M2 = (double *)calloc(M2SIZE, sizeof(double));
    double *restrict M2temp = (double *)calloc(M2SIZE, sizeof(double));
    gettimeofday(&T1, NULL); // запомнить текущее время T1

    for (i = 0; i < 100; i++)
    { // 100 экспериментов
      // инициализировать начальное значение ГСЧ
        seed = 50;
        srand(seed);

        // Заполнить массив исходных данных размером N
        for (j = 0; j < M1SIZE; j++)
        {
            M1[j] = 1 + rand_r(&seed) % 360;
            if (j >= M2SIZE)
            {
                continue;
            }
            else
            {
                M2[j] = 360 + rand_r(&seed) % (10 * 360 - 361);
            }
        }
        // Решить поставленную задачу, заполнить массив с результатами
        for (j = 0; j < M1SIZE; j++)
        {
            M1[j] = 1.0 / tanh(sqrt(M1[j]));
        }

        // copy m2 array
        for (j = 0; j < M2SIZE; j++)
        {
            M2temp[j] = M2[j];
        }

        // new value in M2
        for (j = 1; j < M2SIZE; j++)
        {
            M2[j] += M2temp[j - 1];
            M2[j] = sqrt(M2[j] * M_E);
        }

        // Merge
        for (j = 0; j < M2SIZE; j++)
        {
            M2[j] = M1[j] / M2[j];
        }

        // Отсортировать массив с результатами указанным методом

        // gnomeSort(M2, M2SIZE);

        // REDUCE
        double min = 10 * 360 + 1;
        for (j = 0; j < M2SIZE; j++)
        {
            if (M2[j] < min)
            {
                min = M2[j];
            }
        }

        for (j = 0; j < M2SIZE; j++)
        {
            if ((int)(M2[j] / min) % 2 == 0)
            {
                sum += sin(M2[j]);
            }
        }
    }
    printf("X: %f\n", sum);
    gettimeofday(&T2, NULL); // запомнить текущее время T2
    delta_ms = (T2.tv_sec - T1.tv_sec) * 1000 +
               (T2.tv_usec - T1.tv_usec) / 1000;
    printf("\nN=%d. Milliseconds passed: %ld\n", N, delta_ms);
    fprintf(resultOfTest, "\n%d %ld\n", N, delta_ms);
    free(M1);
    free(M2);
    free(M2temp);
    fclose(resultOfTest);
    return 0;
}

void gnomeSort(double *array, int size)
{
    int index = 0;

    while (index < size)
    {
        if (index == 0)
            index++;
        if (array[index] >= array[index - 1])
            index++;
        else
        {
            int temp = array[index];
            array[index] = array[index - 1];
            array[index - 1] = temp;
            index--;
        }
    }
}