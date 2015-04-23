#include <stdlib.h>
#include <stdio.h>
#include "lib5.h"
static int listLength;
static int *listCount;
static int *listPos;

static int charToNum(char ch)
{
    switch(ch)
    {
    case 'A':
        return 0;
    case 'C':
        return 1;
    case 'G':
        return 2;
    case 'T':
        return 3;
    default:
        return ERROR;
    }
}

static int stringToNum(char *pch)
{
    int result = 0;
    while (*pch != '\0')
    {
        result *= 4;
        result += charToNum(*pch);
        pch++;
    }
    return result;
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

status binaryFilePrint(char *name)
{
    FILE *fp;
    if ((fp = fopen(name, "rb+")) == NULL)
    {
        printf("ERROR: can't open %s\n", name);
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
        printf("ERROR: fail to allocate memory\n");
        return ERROR;
    }
    if ((fread(listPos, sizeof(int), listLength, fp)) != listLength)
    {
        printf("ERROR: fail to allocate memory\n");
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
    long pos   = (long)listPos[goal];
    int recordNumber = 2*count*BUF_LEN;
    if (count == 0)
    {
        printf("%s is not in this series", input);
        return ERROR;
    }
    int *block = NULL;
    if ((block = (int*)calloc(recordNumber, sizeof(int))) == NULL)
    {
        printf("ERROR: fail to allocate memory\n");
        return ERROR;
    }
    fseek(fpFrom, pos, SEEK_SET);
    if ((fread(block, sizeof(int), recordNumber, fpFrom)) != recordNumber)
    {
        printf("ERROR: fail to read data from %s\n", from);
        return ERROR;
    }
    int i;
    for (i = 0; i < recordNumber; i+=2)
    {
        if (block[i] == -1)
        {
            continue;
        }
        fprintf(fpTo, "%d: {%d, %d}\n", block[i], block[i+1]+1, block[i+1]+k+1);
    }
    fclose(fpFrom);
    fclose(fpTo);
    return FINE;
}
