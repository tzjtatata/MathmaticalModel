#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib3.h"

typedef struct{
int x;
int y;
}vector;

static int listLength;
static vector* vecList;
static int countLength;

void initializeCountLength(void)
{
    FILE *fp;
    fp = fopen("leafCount.dat", "rb+");
    fread(&countLength, sizeof(int), 1, fp);
    fclose(fp);
    return;
}

status getLength(char *s)
{
    FILE *fp;
    if ((fp = fopen(s, "rb+")) == NULL)
    {
        printf("ERROR: can't find %s", s);
        return ERROR;
    }
    fread(&listLength, sizeof(int), 1, fp);
    fclose(fp);
    return FINE;
}

status getVector(char *s)
{
    FILE *fp;
    int i;
    vecList = (vector *)calloc(listLength, sizeof(vector));
    if ((fp = fopen(s, "rb+")) == NULL)
    {
        printf("ERROR: can't find %s", s);
        return ERROR;
    }
    for (i = 0; i < listLength; i++)
    {
        vecList[i].x = i;
        fread(&(vecList[i].y), sizeof(int), 1, fp);
    }
    return FINE;
}

void countSort(void)
{
    int count[countLength];
    vector * sort = (vector*)calloc(listLength, sizeof(vector));
    memset(count, 0, sizeof(int)*countLength);
    int i;
    for (i = 0; i < listLength; i++)
    {
        count[vecList[i].y]++;
    }
    FILE* fp = fopen("binarySearch.txt", "wb+");
    fwrite(count, sizeof(int), countLength, fp);
    for (i = 1; i < countLength; i++)
    {
        count[i] += count[i-1];
    }
    fwrite(count, sizeof(int), countLength, fp);
    fclose(fp);
    for (i = listLength-1; i >= 0; i--)
    {
        sort[count[vecList[i].y]-1] = vecList[i];
        count[vecList[i].y]--;
    }
    memcpy(vecList, sort, listLength * sizeof(vector));
    free(sort);
    return;
}

void vecListPrint(void)
{
    int i;
    for (i = 0; i < listLength; i++)
    {
        printf("%4d\t%4d\n", vecList[i].x, vecList[i].y);
    }
    return;
}

status writeInDictionary(char *output)
{
    int position[listLength];
    int i;
    for (i = 0; i < listLength; i++)
    {
        position[i] = vecList[i].x;
    }
    FILE *fp = fopen(output, "wb+");
    if (fp == NULL)
    {
        printf("ERROR:can't open %s\n", output);
        return ERROR;
    }
    if ((fwrite(position, sizeof(int), listLength, fp)) != listLength)
    {
        printf("Fail to write data into %s", output);
        fclose(fp);
        return ERROR;
    }
    fclose(fp);
    return FINE;
}

