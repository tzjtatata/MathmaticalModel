#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib2.h"
static int kNumber;
static int kMerNumber;
static int kMerSingle;
static int **pptr;
static int *pList;
static int *kMerBlock;
static FILE* fpRead;
static FILE* fpWrite;
static FILE* fpRefer;
static FILE* fpMeta;
static int count;
//pptr is a pointer represents a list of kMerNumber pointers, each refers to a memory area of 2*BUF_LEN int numbers

void kInitialize(int k)
{
    kNumber = k;
    kMerSingle = RECORD_LENGTH - kNumber + 1;
    FILE *fp = fopen("leafCount.dat", "rb+");
    fread(&kMerNumber, sizeof(int), 1, fp);
    fclose(fp);
    return;
}

status pointerInitialize(void)
{
    int i;
    if ((pptr = (int **)calloc(kMerNumber, sizeof(int *))) == NULL)
    {
        printf("ERROR: failed to allocate memory!\n");
        return ERROR;
    }
    if ((pList = (int*)calloc(kMerNumber, sizeof(int))) == NULL)
    {
        printf("ERROR: failed to allocate memory!\n");
        return ERROR;
    }
    if ((kMerBlock = (int*)calloc(kMerSingle, sizeof(int))) == NULL)
    {
        printf("ERROR: failed to allocate memory!\n");
        return ERROR;
    }
    for (i = 0; i < kMerNumber; i++)
    {
        if ((pptr[i] = (int *)calloc(BUF_LEN * 2, sizeof(int))) == NULL)
        {
            printf("ERROR: failed to allocate memory!\n");
            return ERROR;
        }
        memset(pptr[i], -1, BUF_LEN * 2 * sizeof(int));
        pList[i] = 0;
    }
    return FINE;
}

status fileOpen(char *s)
{
    if ((fpRead = fopen(s, "rb+")) == NULL)
    {
        printf("ERROR: Can't open %s!\n", s);
        return ERROR;
    }
    if ((fpWrite = fopen("dataInverse.txt", "wb+")) == NULL)
    {
        printf("ERROR: Can't open file!\n");
        return ERROR;
    }
    if ((fpRefer = fopen("dataReference.txt", "wb+")) == NULL)
    {
        printf("ERROR: Can't open file!\n");
        return ERROR;
    }
    if ((fpMeta = fopen("metaData.txt", "wb+")) == NULL)
    {
        printf("ERROR: Can't open file!\n");
        return ERROR;
    }
    return FINE;
}

void fileClose(void)
{
    fclose(fpRead);
    fclose(fpRefer);
    fclose(fpWrite);
    fclose(fpMeta);
    return;
}

status writeData(void)
{
    int* recordOrder = (int*)malloc(sizeof(int));
    int pos;
    int kMerOrder;
    int i;
    count = 0;
    while (1)
    {
        if (fread(recordOrder, sizeof(int), 1, fpRead) != 1)
        {
            if (ferror(fpRead))
            {
                printf("ERROR: file failed");
                return ERROR;
            }
            if (feof(fpRead))
                goto Out;
        }
        if (fread(kMerBlock, sizeof(int), kMerSingle, fpRead) != kMerSingle)
        {
            if (ferror(fpRead))
            {
                printf("ERROR: file failed");
                return ERROR;
            }
            if (feof(fpRead))
                goto Out;
        }
        for (pos = 0; pos < kMerSingle; pos++)
        {
            kMerOrder = kMerBlock[pos];
            pptr[kMerOrder][pList[kMerOrder]++] = *recordOrder;

            pptr[kMerOrder][pList[kMerOrder]++] = pos;
            if (pList[kMerOrder] == 2 * BUF_LEN)//When bug is full,pour in the data
            {
                fwrite(pptr[kMerOrder], sizeof(int), 2*BUF_LEN, fpWrite);
                fwrite(&kMerOrder, sizeof(int), 1, fpRefer);
                pList[kMerOrder] = 0;
                memset(pptr[kMerOrder], -1, 2*BUF_LEN*sizeof(int));
                count++;
            }
        }
    }
Out:
    for (i = 0; i < kMerNumber; i++)
    {
        fwrite(pptr[i], sizeof(int), 2*BUF_LEN, fpWrite);
        fwrite(&i, sizeof(int), 1, fpRefer);
        count++;
    }
    fwrite(&count, sizeof(int), 1, fpMeta);
    return FINE;
}

void printFile(char *s)
{
    FILE *fp = fopen(s, "rb+");
    int i;
    while (fread(&i,sizeof(int),1,fp) == 1)
    {
        printf("%d\t",i);
    }
    fclose(fp);
    return;
}
