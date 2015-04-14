#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CHAR_LENGTH 100
#define CHAR_NUMBER 10000

int main()
{
    int i, j;
    srand(time(NULL));
    for (i = 0;i < CHAR_NUMBER; i++)
    {
        for (j = 0; j < CHAR_LENGTH; j++)
        {
            switch (rand() % 4)
            {
            case 0:
                printf("A");
                break;
            case 1:
                printf("C");
                break;
            case 2:
                printf("G");
                break;
            case 3:
                printf("T");
                break;
            }
        }
        printf("\n");
    }
    return 0;
}
