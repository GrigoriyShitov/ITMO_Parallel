#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include "omp.h"
#define _USE_MATH_DEFINES
#include <math.h>

typedef struct
{
    double *M1;
    double *M2;
    double *M2temp;
    int N;
    int chunkSize;
    int threadId;
    int threadCount;
} ThreadArgs;

int percent;
double min;
pthread_mutex_t min_mutex;
pthread_mutex_t sum_mutex;

#define M1SIZE (N)
#define M2SIZE (N / 2)

double sum = 0;

void Generate(double *M1, double *M2, unsigned int seed, int N);
void Map(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize);
void *mapTask1(void *arg);
void *mapTask2(void *arg);
void *mapTask3(void *arg);

void Merge(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize);
void *mergeTask(void *arg);

void Reduce(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize);
void *reduceTask1(void *arg);
void *reduceTask2(void *arg);

void sort(double *M2, int chunkSize, int N, int threadCount, size_t size);
void *gnomeSort(void *arg);
void CompJob();

int main(int argc, char *argv[])
{
    int N, j;
    unsigned int seed;
    struct timeval T1, T2, TstageS, TstageE;
    long delta_ms;
    N = atoi(argv[1]); // N равен первому параметру командной строки
    int threadCount = atoi(argv[2]);
    int chunkSize = M2SIZE / threadCount;
    // printf("%d\n%d\n", chunkSize, M2SIZE);

    double *restrict M1 = (double *)calloc(M1SIZE, sizeof(double));
    double *restrict M2 = (double *)calloc(M2SIZE, sizeof(double));
    double *restrict M2temp = (double *)calloc(M2SIZE, sizeof(double));
    FILE *resultOfTest = fopen("Results/Results.txt", "a");

    pthread_t *compJobTh;
    pthread_mutex_init(&min_mutex, NULL);
    pthread_mutex_init(&sum_mutex, NULL);
    if (pthread_create(&compJobTh, NULL, CompJob, percent) != 0)
    {
        printf("Error to create thread!\n");
        return 1;
    }
    gettimeofday(&T1, NULL); // запомнить текущее время T1
    for (percent = 0; percent < 100; percent++)
    {                             // 100 экспериментов
        seed = percent * percent; // инициализировать начальное значение ГСЧ
        min = 10 * 360 + 1;
        // Заполнить массив исходных данных размером N
        if (percent == 10)
        {

            gettimeofday(&TstageS, NULL);
        }
        Generate(M1, M2, seed, N);
        if (percent == 10)
        {
            gettimeofday(&TstageE, NULL);
            delta_ms = (TstageE.tv_sec - TstageS.tv_sec) * 1000 +
                       (TstageE.tv_usec - TstageS.tv_usec) / 1000;
            printf("\nN=%d. GENERATE: %ld\n\n", N, delta_ms);
        }
        // Решить поставленную задачу, заполнить массив с результатами
        if (percent == 10)
        {

            gettimeofday(&TstageS, NULL);
        }
        Map(M1, M2, M2temp, N, threadCount, chunkSize);
        if (percent == 10)
        {
            gettimeofday(&TstageE, NULL);
            delta_ms = (TstageE.tv_sec - TstageS.tv_sec) * 1000 +
                       (TstageE.tv_usec - TstageS.tv_usec) / 1000;
            printf("\nN=%d. MAP: %ld\n\n", N, delta_ms);
        }
        // Merge
        if (percent == 10)
        {

            gettimeofday(&TstageS, NULL);
        }
        Merge(M1, M2, M2temp, N, threadCount, chunkSize);
        if (percent == 10)
        {
            gettimeofday(&TstageE, NULL);
            delta_ms = (TstageE.tv_sec - TstageS.tv_sec) * 1000 +
                       (TstageE.tv_usec - TstageS.tv_usec) / 1000;
            printf("\nN=%d. MERGE: %ld\n\n", N, delta_ms);
        }
        // Отсортировать массив с результатами указанным методомared(M1, N)
        if (percent == 10)
        {

            gettimeofday(&TstageS, NULL);
        }
        sort(M2, chunkSize, N, threadCount, M2SIZE);
        if (percent == 10)
        {
            gettimeofday(&TstageE, NULL);
            delta_ms = (TstageE.tv_sec - TstageS.tv_sec) * 1000 +
                       (TstageE.tv_usec - TstageS.tv_usec) / 1000;
            printf("\nN=%d. SORT: %ld\n\n", N, delta_ms);
        }
        // REDUCE
        if (percent == 10)
        {

            gettimeofday(&TstageS, NULL);
        }
        Reduce(M1, M2, M2temp, N, threadCount, chunkSize);
        if (percent == 10)
        {
            gettimeofday(&TstageE, NULL);
            delta_ms = (TstageE.tv_sec - TstageS.tv_sec) * 1000 +
                       (TstageE.tv_usec - TstageS.tv_usec) / 1000;
            printf("\nN=%d. REDUCE: %ld\n\n", N, delta_ms);
        }
        // printf("X: %lf\n", sum);
    }
    free(M1);
    free(M2);
    free(M2temp);
    gettimeofday(&T2, NULL); // запомнить текущее время T2
    delta_ms = (T2.tv_sec - T1.tv_sec) * 1000 +
               (T2.tv_usec - T1.tv_usec) / 1000;
    pthread_join(compJobTh, NULL);
    printf("X: %lf\n", sum);
    printf("\nN=%d. Milliseconds passed: %ld\n\n", N, delta_ms);
    fprintf(resultOfTest, "%ld\n", delta_ms);
    fclose(resultOfTest);
    pthread_mutex_destroy(&min_mutex);
    pthread_mutex_destroy(&sum_mutex);
    pthread_exit(NULL);
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

void CompJob()
{
    while (1)
    {
        if (percent == 100)
        {
            printf("Job completed on %d% \n", percent);
            break;
        }
        printf("Job completed on %d% \n", percent);
        sleep(1);
    }
    return;
}

void Map(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize)
{
    pthread_t *threads = (pthread_t *)malloc(threadCount * sizeof(pthread_t));
    ThreadArgs *args = (ThreadArgs *)malloc(threadCount * sizeof(ThreadArgs));

    // Задача 1: Обработка M1
    for (int i = 0; i < threadCount; i++)
    {
        args[i].M1 = M1;
        args[i].M2 = NULL;
        args[i].M2temp = NULL;
        args[i].N = M1SIZE;
        args[i].chunkSize = chunkSize;
        args[i].threadId = i;
        args[i].threadCount = threadCount;
        pthread_create(&threads[i], NULL, mapTask1, &args[i]);
    }

    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Задача 2: Копирование M2 в M2temp
    for (int i = 0; i < threadCount; i++)
    {
        args[i].M1 = NULL;
        args[i].M2 = M2;
        args[i].M2temp = M2temp;
        args[i].N = M2SIZE;
        args[i].chunkSize = chunkSize;
        args[i].threadId = i;
        args[i].threadCount = threadCount;
        pthread_create(&threads[i], NULL, mapTask2, &args[i]);
    }

    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Задача 3: Обновление M2
    for (int i = 0; i < threadCount; i++)
    {
        args[i].M1 = NULL;
        args[i].M2 = M2;
        args[i].M2temp = M2temp;
        args[i].N = M2SIZE;
        args[i].chunkSize = chunkSize;
        args[i].threadId = i;
        args[i].threadCount = threadCount;
        pthread_create(&threads[i], NULL, mapTask3, &args[i]);
    }

    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(args);
}
void *mapTask1(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int start = args->threadId * args->chunkSize;
    int end = (args->threadId == args->threadCount - 1) ? args->N : (args->threadId + 1) * args->chunkSize;
    for (int j = start; j < end; j++)
    {
        args->M1[j] = 1.0 / tanh(sqrt(args->M1[j]));
    }

    return NULL;
}

void *mapTask2(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int start = args->threadId * args->chunkSize;
    int end = (args->threadId == args->threadCount - 1) ? args->N : (args->threadId + 1) * args->chunkSize;

    for (int j = start; j < end; j++)
    {
        args->M2temp[j] = args->M2[j];
    }

    return NULL;
}

void *mapTask3(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int start = args->threadId * args->chunkSize + 1;
    int end = (args->threadId == args->threadCount - 1) ? args->N : (args->threadId + 1) * args->chunkSize;
    // if (args->threadId == args->threadCount - 1)
    // {
    //     printf("end of last chunk: %d\n", end);
    // }
    for (int j = start; j < end; j++)
    {
        args->M2[j] += args->M2temp[j - 1];
        args->M2[j] = sqrt(args->M2[j] * exp(1));
    }

    return NULL;
}

void Merge(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize)
{
    pthread_t *threads = (pthread_t *)malloc(threadCount * sizeof(pthread_t));
    ThreadArgs *args = (ThreadArgs *)malloc(threadCount * sizeof(ThreadArgs));

    for (int i = 0; i < threadCount; i++)
    {
        args[i].M1 = M1;
        args[i].M2 = M2;
        args[i].M2temp = NULL;
        args[i].N = M2SIZE;
        args[i].chunkSize = chunkSize;
        args[i].threadId = i;
        args[i].threadCount = threadCount;
        pthread_create(&threads[i], NULL, mergeTask, &args[i]);
    }

    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(args);
}

void *mergeTask(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int start = args->threadId * args->chunkSize;
    int end = (args->threadId == args->threadCount - 1) ? args->N : (args->threadId + 1) * args->chunkSize;

    for (int j = start; j < end; j++)
    {
        args->M2[j] = args->M1[j] / args->M2[j];
    }

    return NULL;
}

void Reduce(double *M1, double *M2, double *M2temp, int N, int threadCount, int chunkSize)
{
    int j;
    pthread_t *threads = (pthread_t *)malloc(threadCount * sizeof(pthread_t));
    ThreadArgs *args = (ThreadArgs *)malloc(threadCount * sizeof(ThreadArgs));

    for (int i = 0; i < threadCount; i++)
    {
        args[i].M1 = NULL;
        args[i].M2 = M2;
        args[i].M2temp = NULL;
        args[i].N = M2SIZE;
        args[i].chunkSize = chunkSize;
        args[i].threadId = i;
        args[i].threadCount = threadCount;
        pthread_create(&threads[i], NULL, reduceTask1, &args[i]);
    }
    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < threadCount; i++)
    {
        args[i].M1 = NULL;
        args[i].M2 = M2;
        args[i].M2temp = M2temp;
        args[i].N = M2SIZE;
        args[i].chunkSize = chunkSize;
        args[i].threadId = i;
        args[i].threadCount = threadCount;
        pthread_create(&threads[i], NULL, reduceTask2, &args[i]);
    }
    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }
    free(threads);
    free(args);
}

void *reduceTask1(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int start = args->threadId * args->chunkSize;
    int end = (args->threadId == args->threadCount - 1) ? args->N : (args->threadId + 1) * args->chunkSize;
    double local_min = args->M2[start];

    for (int j = start + 1; j < end; j++)
    {
        if (args->M2[j] < local_min)
            local_min = args->M2[j];
    }
    pthread_mutex_lock(&min_mutex);
    if (local_min < min)
    {
        min = local_min;
    }
    pthread_mutex_unlock(&min_mutex);
    return NULL;
}

void *reduceTask2(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int start = args->threadId * args->chunkSize;
    int end = (args->threadId == args->threadCount - 1) ? args->N : (args->threadId + 1) * args->chunkSize;
    double local_sum = 0;

    for (int j = start; j < end; j++)
    {
        if ((int)(args->M2[j] / min) % 2 == 0)
        {
            local_sum += sin(args->M2[j]);
        }
    }
    pthread_mutex_lock(&sum_mutex);
    sum += local_sum;
    pthread_mutex_unlock(&sum_mutex);
    return NULL;
}

void sort(double *M2, int chunkSize, int N, int threadCount, size_t size)
{
    pthread_t *threads = (pthread_t *)malloc(threadCount * sizeof(pthread_t));
    ThreadArgs *args = (ThreadArgs *)malloc(threadCount * sizeof(ThreadArgs));

    for (int i = 0; i < threadCount; i++)
    {
        args[i].M1 = NULL;
        args[i].M2 = M2;
        args[i].M2temp = NULL;
        args[i].N = M2SIZE;
        args[i].chunkSize = chunkSize;
        args[i].threadId = i;
        args[i].threadCount = threadCount;
        pthread_create(&threads[i], NULL, gnomeSort, &args[i]);
    }
    for (int i = 0; i < threadCount; i++)
    {
        pthread_join(threads[i], NULL);
    }

    double temp[size];
    int i = 0, j = 0;
    for (int i = 0; i < size; i++)
    {
        if (i < chunkSize)
        {
            temp[i] = M2[i];
        }
        else
        {
            j = (i / chunkSize) * chunkSize;
            while (j < (i / chunkSize + 1) * chunkSize && i < size)
            {
                temp[i++] = M2[j++];
            }
        }
    }

    // Копирование отсортированного массива обратно в исходный
    for (int i = 0; i < size; i++)
    {
        M2[i] = temp[i];
    }
}

void *gnomeSort(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int pos = 0;
    while (pos < args->chunkSize)
    {
        if (pos == 0 || (args->M2[pos + args->chunkSize * args->threadId]) >= args->M2[pos + args->chunkSize * args->threadId - 1])
        {
            pos++;
        }
        else
        {
            double temp = args->M2[pos + args->chunkSize * args->threadId];
            args->M2[pos + args->chunkSize * args->threadId] = args->M2[pos + args->chunkSize * args->threadId - 1];
            args->M2[pos + args->chunkSize * args->threadId - 1] = temp;
            pos--;
        }
    }
}