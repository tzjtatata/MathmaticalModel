#include <stdlib.h>
#include <stdio.h>
#include "lib3.h"

typedef struct{
int x;
int y;
}vector;

static int listLength;
static vector* vecList;

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

void vectorAttribute(vector *left, vector right)
{
    (*left).x = right.x;
    (*left).y = right.y;
    return;
}

/*This function returns subscript of the largest number in list smaller than goal*/
int ground(int list[], int goal)
{
    int low = 0;
    int high = 14-1;
    int mid = 14/2;
    while (low <= high)
    {
        if (list[mid] < goal)
            low = mid + 1;
        if (list[mid] > goal)
            high = mid - 1;
        if (list[mid] == goal)
        {
            return (mid)? mid-1:mid;
        }
        mid = low + (high-low)/2;
    }
    return (low)? low-1:low;
}

void shellSort(void)
{
    int shellList[14] = {1, 4, 9, 20, 46, 103, 233, 525, 1182, 2660, 5985, 13467, 30301, 68178};//Tokuda's increment
    int subscript = ground(shellList, listLength);
    int step;
    int start;
    int i, j;
    vector key;
    while (subscript >= 0)
    {
        step = shellList[subscript];

        for (start = 0; start < step; start++)
        {
            j = start + step;
            while (j < listLength)
            {
                vectorAttribute(&key, vecList[j]);
                i = j - step;
                while ((i >= start) && (vecList[i].y > key.y))//Notice:the order of these two judges matters a lot
                {
                    vectorAttribute(vecList+i+step, vecList[i]);
                    i -= step;
                }
                vectorAttribute(vecList+i+step, key);
                j += step;
            }//Insertion sort with the gap of step
        }
        subscript--;//Move on to the next step
    }
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

status writeInReference(char *s)
{
    FILE *fp;
    int *list;
    if ((list = (int*)calloc(listLength, sizeof(int))) == NULL)
    {
        printf("ERROR:failed to allocate memory!\n");
        return ERROR;
    }
    if ((fp = fopen(s, "wb+")) == NULL)
    {
        printf("ERROR:can't open %s\n", s);
        return ERROR;
    }
    int i;
    for (i = 0; i < listLength; i++)
    {
        list[i] = vecList[i].y;
    }
    fwrite(list, sizeof(int), listLength, fp);
    fclose(fp);
    return FINE;
}

status referPrint(char *s)
{
    FILE *fp;
    int *list;
    if ((list = (int*)calloc(listLength, sizeof(int))) == NULL)
    {
        printf("ERROR:failed to allocate memory!\n");
        return ERROR;
    }
    if ((fp = fopen(s, "rb+")) == NULL)
    {
        printf("ERROR:can't open %s\n", s);
        return ERROR;
    }
    if ((fread(list, sizeof(int), listLength, fp)) != listLength)
    {
        printf("ERROR:failed to read in data from %s\n", s);
        return ERROR;
    }
    int i;
    for (i = 0; i < listLength; i++)
    {
        printf("%d\t", list[i]);
    }
    printf("\n");
    return FINE;
}

status organizeData(char *from, char *to)
{
    FILE *fpIn;
    FILE *fpOut;
    int *dataBlock;
    if ((fpIn = fopen(from, "rb+")) == NULL)
    {
        printf("ERROR:can't open %s\n", from);
        return ERROR;
    }
    if ((fpOut = fopen(to, "wb+")) == NULL)
    {
        printf("ERROR:can't open %s\n", to);
        return ERROR;
    }
    if ((dataBlock = (int*)calloc(2*BUF_LEN, sizeof(int))) == NULL)
    {
        printf("ERROR:failed to allocate memory!\n");
        return ERROR;
    }
    int i, pos;
    for (i = 0; i < listLength; i++)
    {
        pos = (vecList[i].x) * 2 * BUF_LEN * sizeof(int);
        fseek(fpIn, (long)pos, SEEK_SET);
        fread(dataBlock, sizeof(int), 2*BUF_LEN, fpIn);
        fwrite(dataBlock, sizeof(int), 2*BUF_LEN, fpOut);
    }
    fclose(fpIn);
    fclose(fpOut);
    return FINE;
}

status binaryFilePrint(char *name)
{
    FILE *fp;
    if ((fp = fopen(name, "rb+")) == NULL)
    {
        printf("ERROR:can't open %s\n", name);
        return ERROR;
    }
    int term;
    while ((fread(&term, sizeof(int), 1, fp)) == 1)
    {
        printf("%d\t", term);
    }
    printf("\n");
    fclose(fp);
    return FINE;
}
