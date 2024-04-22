#include <stdio.h>

int main(int argc, char *argv[])
{

    FILE *file;
    printf("%d", argc);
    char* name = argv[0];
    
    printf("%s",name);
    //file = fopen(argv[1], "a");

    printf("%s",name);
    //fprintf(file,"open successfuly");
    /*switch (atoi(argv[0]))
    {
    case 0:
        file = fopen("Results_without_shedule.txt", "a");
        break;
    case 1:
        file = fopen("Results_shedule_auto.txt", "a");
        break;
    case 2:
        file = fopen("Results_shedule_dynamic.txt", "a");
        break;
    case 3:
        file = fopen("Results_shedule_guided.txt", "a");
        break;
    case 4:
        file = fopen("Results_shedule_static.txt", "a");
        break;
    default:
        break;
    }*/

    //int chunksize = atoi(argv[1]);
    


    //fclose(file);
}

/*
Files:
0 - fopen("Results_without_shedule.txt", "a");
1 - fopen("Results_shedule_auto.txt", "a");
2 - fopen("Results_shedule_dynamic.txt", "a");
3 - fopen("Results_shedule_guided.txt", "a");
4 - fopen("Results_shedule_static.txt", "a");
*/