#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

int main(int argc, char *argv[])
{

    FILE *file;
    char *name = argv[1];
    int Nsize = atoi(argv[2]);
    char *Schedule = argv[3];
    int chunkSize = atoi(argv[4]);
    int threadSize = atoi(argv[5]);

    printf("Writing test to %s with N=%d. Shedule:%s, Chunksize:%d Number of threads:%d\n", name, Nsize, Schedule, chunkSize, threadSize);
    file = fopen(name, "a");
    fprintf(file, "N=%d. Shedule:%s, Chunksize: %d Number of threads:%d\n", Nsize, Schedule, chunkSize, threadSize);
    int chunksize = atoi(argv[1]);

    fclose(file);
}

/*
Files:
0 - fopen("Results_without_shedule.txt", "a");
1 - fopen("Results_shedule_auto.txt", "a");
2 - fopen("Results_shedule_dynamic.txt", "a");
3 - fopen("Results_shedule_guided.txt", "a");
4 - fopen("Results_shedule_static.txt", "a");
*/