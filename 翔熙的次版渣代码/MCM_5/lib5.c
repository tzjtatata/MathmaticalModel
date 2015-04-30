#include <stdlib.h>
#include <stdio.h>
#include "lib5.h"
static int listLength;
static int *listCount;
static int *listPos;

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

status checkData(char *input, char *from, char *to, int k)
{
    int goal = stringToNum(input);
    FILE *fpFrom;
    FILE *fpTo;
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
    int count = listCount[goal];
    long pos   = (long)(listPos[goal]);
    int recordNumber = 2*count*BUF_LEN;
    if (count == 0)
    {
        printf("%s is not in this series\n", input);
        return ERROR;
    }
    int *block = NULL;
    if ((block = (int*)calloc(recordNumber, sizeof(int))) == NULL)
    {
        printf("ERROR: fail to allocate memory\n");
        return ERROR;
    }
    while (pos > 1000L)
    {
        fseek(fpFrom, 1000L*2*BUF_LEN*sizeof(int), SEEK_CUR);
        pos -= 1000;
    }
    fseek(fpFrom, pos*2 * BUF_LEN * sizeof(int), SEEK_CUR);
    if ((fread(block, sizeof(int), recordNumber, fpFrom)) != recordNumber)
    {
        printf("ERROR: fail to read data from %s\n", from);
        return ERROR;
    }
    int i;
    for (i = 0; i < recordNumber; i+=2)
    {
        if (block[i] == -1)
            break;
        fprintf(fpTo, "%d: {%d, %d}\n", block[i], block[i+1]+1, block[i+1]+k+1);
    }
    fclose(fpFrom);
    fclose(fpTo);
    return FINE;
}
