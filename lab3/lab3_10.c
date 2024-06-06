#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "omp.h"
#define _USE_MATH_DEFINES
#include <math.h>

int i;

#define M1SIZE (N)
#define M2SIZE (N / 2)

double sum = 0;

void gnomeSort(double *array, int size);
void Generate(double *M1, double *M2, unsigned int seed, int N);
void Map(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize);
void Merge(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize);
void Reduce(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize);
void sort(double *M2, size_t size);
void CompJob();

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Not enough args!\n Exit..");
        return 1;
    }
    int N, j;
    unsigned int seed;

    struct timeval T1, T2;
    double Tstart, Tend;
    long delta_ms;
    N = atoi(argv[1]); // N равен первому параметру командной строки
    int threadCount = atoi(argv[2]);
    int chunkSize = atoi(argv[3]);

    double *restrict M1 = (double *)calloc(M1SIZE, sizeof(double));
    double *restrict M2 = (double *)calloc(M2SIZE, sizeof(double));
    double *restrict M2temp = (double *)calloc(M2SIZE, sizeof(double));
    FILE *resultOfTest = fopen("Results/Results_10.txt", "a");

    gettimeofday(&T1, NULL); // запомнить текущее время T1
#ifdef _OPENMP
    Tstart = omp_get_wtime();
    omp_set_nested(1);
#endif
// #pragma omp parallel for default(none) private(i,seed,j, sum) shared(N) num_threads(threadCount)
#pragma omp parallel sections shared(i) num_threads(threadCount)
    {
#pragma omp section
        {
#ifdef _OPENMP
            CompJob();
#endif
        }
#pragma omp section
        {
            for (i = 0; i < 10; i++)
            {                 // 100 экспериментов
                seed = i * i; // инициализировать начальное значение ГСЧ
                // Заполнить массив исходных данных размером N
                Generate(M1, M2, seed, N);
                // Решить поставленную задачу, заполнить массив с результатами
                Map(M1, M2, M2temp, N, threadCount, chunkSize);

                // Merge
                Merge(M1, M2, M2temp, N, threadCount, chunkSize);

                // Отсортировать массив с результатами указанным методомared(M1, N)
                sort(M2, M2SIZE);

                // REDUCE
                Reduce(M1, M2, M2temp, N, threadCount, chunkSize);
            }
            free(M1);
            free(M2);
            free(M2temp);
#ifdef _OPENMP
            Tend = omp_get_wtime();
#endif
            printf("X: %lf\n", sum);
            gettimeofday(&T2, NULL); // запомнить текущее время T2
            delta_ms = (T2.tv_sec - T1.tv_sec) * 1000 +
                       (T2.tv_usec - T1.tv_usec) / 1000;
            printf("\nN=%d. Milliseconds passed: %ld\n", N, delta_ms);
            printf("Work took %f seconds\n", Tend - Tstart);
            fprintf(resultOfTest, "%ld\n", delta_ms);
            fclose(resultOfTest);
        }
    }

    return 0;
}
void Generate(double *M1, double *M2, unsigned int seed, int N)
{
    int j;
    for (j = 0; j < M1SIZE; j++)
    {
        M1[j] = 1 + rand_r(&seed) % 360;
    }
    for (j = 0; j < M2SIZE; j++)
    {
        M2[j] = 360 + rand_r(&seed) % (10 * 360 - 361);
    }
}

void Map(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize)
{
    int j;
#pragma omp parallel for default(none) private(j) shared(M1, N, chunkSize) schedule(guided, chunkSize) num_threads(threadCount)
    for (j = 0; j < M1SIZE; j++)
    {
        M1[j] = 1.0 / tanh(sqrt(M1[j]));
    }

    // copy m2 array

#pragma omp parallel for default(none) private(j) shared(M2, M2temp, N, chunkSize) schedule(guided, chunkSize) num_threads(threadCount)
    for (j = 0; j < M2SIZE; j++)
    {
        M2temp[j] = M2[j];
    }

// new value in M2mak
#pragma omp parallel for default(none) private(j) shared(M2, M2temp, N, chunkSize) schedule(guided, chunkSize) num_threads(threadCount)
    for (j = 1; j < M2SIZE; j++)
    {
        M2[j] += M2temp[j - 1];
        M2[j] = sqrt(M2[j] * M_E);
    }
}

void Merge(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize)
{
    int j;
#pragma omp parallel for default(none) private(j) shared(M2, M1, N, chunkSize) schedule(guided, chunkSize) num_threads(threadCount)
    for (j = 0; j < M2SIZE; j++)
    {
        M2[j] = M1[j] / M2[j];
    }
}
void Reduce(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize)
{
    int j;
    double min = 10 * 360 + 1;
#pragma omp parallel for default(none) reduction(min : min) private(j) shared(M2, N, chunkSize) schedule(guided, chunkSize) num_threads(threadCount)
    for (j = 0; j < M2SIZE; j++)
    {
        if (M2[j] < min)
        {
            min = M2[j];
        }
    }

#pragma omp parallel for default(none) reduction(+ : sum) private(j) shared(M2, min, N, chunkSize) schedule(guided, chunkSize) num_threads(threadCount)
    for (j = 0; j < M2SIZE; j++)
    {
        if ((int)(M2[j] / min) % 2 == 0)
        {
            sum += sin(M2[j]);
        }
    }
}
void CompJob()
{
#pragma omp single nowait
    while (1)
    {
        if (i == 10)
        {
            printf("Job completed on %d% \n", i);
            break;
        }
        printf("Job completed on %d% \n", i);
        sleep(1);
    }
    return;
}
void gnomeSort(double *arr, int size)
{
    int pos = 0;
    while (pos < size)
    {
        if (pos == 0 || arr[pos] >= arr[pos - 1])
        {
            pos++;
        }
        else
        {
            double temp = arr[pos];
            arr[pos] = arr[pos - 1];
            arr[pos - 1] = temp;
            pos--;
        }
    }
}

void sort(double *M2, size_t size)
{
    size_t mid = size / 2;
#pragma omp parallel sections shared(M2, size)
    {
#pragma omp section
        gnomeSort(M2, mid);
#pragma omp section
        gnomeSort(M2 + mid, mid);
    }
    double temp[size];
    int i = 0, j = mid, k = 0;
    while (i < mid && j < size)
    {
        if (M2[i] <= M2[j])
        {
            temp[k++] = M2[i++];
        }
        else
        {
            temp[k++] = M2[j++];
        }
    }
    while (i < mid)
    {
        temp[k++] = M2[i++];
    }
    while (j < size)
    {
        temp[k++] = M2[j++];
    }

    // Копирование отсортированного массива обратно в исходный
    for (int i = 0; i < size; i++)
    {
        M2[i] = temp[i];
    }
}

// N=12000 минимум при котором накладные расходы превышают выйгрыш в распараллеливании