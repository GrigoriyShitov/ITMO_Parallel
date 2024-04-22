#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define M1SIZE (N)
#define M2SIZE (N / 2)

void gnomeSort(double *array, int size);

int main(int argc, char *argv[])
{
    int i, N, j;
    unsigned int seed;
    double sum = 0;
    struct timeval T1, T2;
    long delta_ms;
    N = atoi(argv[1]); // N равен первому параметру командной строки
    int threadCount = atoi(argv[2]);
    double *restrict M1 = (double *)calloc(M1SIZE, sizeof(double));
    double *restrict M2 = (double *)calloc(M2SIZE, sizeof(double));
    double *restrict M2temp = (double *)calloc(M2SIZE, sizeof(double));

    gettimeofday(&T1, NULL); // запомнить текущее время T1
    for (i = 0; i < 100; i++)
    { // 100 экспериментов
        seed = i;
        srand(seed); // инициализировать начальное значение ГСЧ
        // Заполнить массив исходных данных размером N
        for (j = 0; j < M1SIZE; j++)
        {
            M1[j] = 1 + rand_r(&seed) % 360;
        }
        for (j = 0; j < M2SIZE; j++)
        {
            M2[j] = 360 + rand_r(&seed) % (10 * 360 - 361);
        }
// Решить поставленную задачу, заполнить массив с результатами
#pragma omp parallel for default(none) private(j) shared(M1, N) schedule(auto) num_threads(threadCount)
        for (j = 0; j < M1SIZE; j++)
        {
            M1[j] = 1.0 / tanh(sqrt(M1[j]));
        }

// copy m2 array
#pragma omp parallel for default(none) private(j) shared(M2, M2temp, N) schedule(auto) num_threads(threadCount)
        for (j = 0; j < M2SIZE; j++)
        {
            M2temp[j] = M2[j];
        }

// new value in M2mak
#pragma omp parallel for default(none) private(j) shared(M2, M2temp, N) schedule(auto) num_threads(threadCount)
        for (j = 1; j < M2SIZE; j++)
        {
            M2[j] += M2temp[j - 1];
            M2[j] = sqrt(M2[j] * M_E);
        }

// Merge
#pragma omp parallel for default(none) private(j) shared(M2, M1, N) schedule(auto) num_threads(threadCount)
        for (j = 0; j < M2SIZE; j++)
        {
            M2[j] = M1[j] / M2[j];
        }

        // Отсортировать массив с результатами указанным методомared(M1, N)
        // gnomeSort(M2, M2SIZE);

        // REDUCE
        double min = 10 * 360 + 1;
#pragma omp parallel for default(none) private(j) shared(M2, min, N) schedule(auto) num_threads(threadCount)
        for (j = 0; j < M2SIZE; j++)
        {
            if (M2[j] < min)
            {
                min = M2[j];
            }
        }

#pragma omp parallel for default(none) private(j) shared(M2, min, sum, N) schedule(auto) num_threads(threadCount)
        for (j = 0; j < M2SIZE; j++)
        {
            if ((int)(M2[j] / min) % 2 == 0)
            {
                sum += sin(M2[j]);
            }
        }
    }
    free(M1);
    free(M2);
    free(M2temp);
    printf("X: %lf\n", sum);
    gettimeofday(&T2, NULL); // запомнить текущее время T2
    delta_ms = (T2.tv_sec - T1.tv_sec) * 1000 +
               (T2.tv_usec - T1.tv_usec) / 1000;
    printf("\nN=%d. Milliseconds passed: %ld\n", N, delta_ms);

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