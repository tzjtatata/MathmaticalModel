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
static char buf1[2 * BUF_LEN * sizeof(int)];
static char buf2[2 * BUF_LEN * sizeof(int)];
static int countLength;

void initializeCountLength(int k)
{
    k <<= 1;
    countLength = 1 << k;
    FILE *fp;
    fp = fopen("countSup.txt", "wb+");
    fwrite(&countLength, sizeof(int), 1, fp);
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
    setvbuf(fpIn, buf1, _IOFBF, 2 * BUF_LEN * sizeof(int));
    setvbuf(fpOut, buf2, _IOFBF, 2 * BUF_LEN * sizeof(int));
    if ((dataBlock = (int*)calloc(2*BUF_LEN, sizeof(int))) == NULL)
    {
        printf("ERROR:failed to allocate memory!\n");
        return ERROR;
    }
    int i, pos;
    for (i = 0; i < listLength; i++)
    {
        pos = (vecList[i].x);
        while (pos > 1000)
        {
            fseek(fpIn, 1000L * (2 * BUF_LEN * sizeof(int)), SEEK_CUR);
            pos -= 1000;
        }
        fseek(fpIn, (long)pos*(2 * BUF_LEN * sizeof(int)), SEEK_CUR);
        fread(dataBlock, sizeof(int), 2*BUF_LEN, fpIn);
        fwrite(dataBlock, sizeof(int), 2*BUF_LEN, fpOut);
        fseek(fpIn, 0L, SEEK_SET);
        printf("\r%.6f %%", (float)i / listLength * 100);
    }
    printf("\n");
    fclose(fpIn);
    fclose(fpOut);
    return FINE;
}

