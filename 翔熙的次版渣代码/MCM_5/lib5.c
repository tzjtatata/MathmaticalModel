#include <stdlib.h>
#include <stdio.h>
#include "lib5.h"
static int listLength;
static int *listCount;
static int *listPos;
static FILE *fpFrom;
static FILE *fpTo;
static FILE *fpDict;

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

status initializeFilePointer(char *from, char *to, char *dictionary)
{
    if ((fpFrom = fopen(from, "rb+")) == NULL)
    {
        printf("ERROR: can't open %s\n", from);
        return ERROR;
    }
    if ((fpTo = fopen(to, "w+")) == NULL)
    {
        printf("ERROR: can't open %s\n", to);
        return ERROR;
    }
    if ((fpDict = fopen(dictionary, "rb+")) == NULL)
    {
        printf("ERROR: can't open %s\n", dictionary);
        return ERROR;
    }
    return FINE;
}

void fileClose(void)
{
    fclose(fpFrom);
    fclose(fpTo);
    fclose(fpDict);
}

status readInList(char *name)
{
    FILE *fp;
    listCount = (int *)calloc(listLength, sizeof(int));
    listPos = (int *)calloc(listLength, sizeof(int));
    if ((fp = fopen(name, "rb+")) == NULL)
    {
        printf("ERROR: can't open %s\n", name);
        return ERROR;
    }
    if ((fread(listCount, sizeof(int), listLength, fp)) != listLength)
    {
        printf("ERROR: fail to read file from %s\n", name);
        return ERROR;
    }
    if ((fread(listPos, sizeof(int), listLength, fp)) != listLength)
    {
        printf("ERROR: fail to read file from %s\n", name);
        return ERROR;
    }
    fclose(fp);
    return FINE;
}

static status writeInSingleBlock(int position, int block[])
{
    fseek(fpFrom, 0L, SEEK_SET);
    while (position > 10000)
    {
        fseek(fpFrom, 10000L*2*BUF_LEN*sizeof(int), SEEK_CUR);
        position -= 10000;
    }
    fseek(fpFrom, position*2 * BUF_LEN * sizeof(int), SEEK_CUR);

    if ((fread(block, sizeof(int), 2*BUF_LEN, fpFrom)) != 2*BUF_LEN)
    {
        printf("ERROR: fail to read data from data file.\n");
        return ERROR;
    }
    int i;
    for (i = 0; i < 2*BUF_LEN; i+=2)
    {
        if (block[i] == -1)
            break;
        fprintf(fpTo, "%d: {%d, %d}\n", block[i], block[i+1]+1, block[i+1]+K_VALUE+1);
    }
    return FINE;
}

status checkData(char *input, int k)
{
    int goal = stringToNum(input);
    int count = listCount[goal];
    long midPostion   = (long)(listPos[goal]) - count;

    if (count == 0)
    {
        printf("%s is not in this series\n", input);
        return ERROR;
    }

    fseek(fpDict, 0L, SEEK_SET);
    while (midPostion > 1000000)
    {
        fseek(fpDict, 1000000L * sizeof(int), SEEK_CUR);
        midPostion -= 1000000;
    }
    fseek(fpDict, midPostion*sizeof(int), SEEK_CUR);

    int block[2*BUF_LEN];
    int position;
    while (count > 0)
    {
        if ((fread(&position, sizeof(int), 1, fpDict)) != 1)
        {
            printf("Fail to load position\n");
            return ERROR;
        }

        writeInSingleBlock(position, block);

        count--;
    }
    return FINE;
}
