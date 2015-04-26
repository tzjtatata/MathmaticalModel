#include <stdio.h>
#include <stdlib.h>
#include "lib4.h"
static int listLength;
static FILE *fpIn;
static FILE *fpOut;

status openFile(char *from, char *to)
{
    if ((fpIn = fopen(from, "rb+")) == NULL)
    {
        printf("ERROR: can't opne %s\n", from);
        return ERROR;
    }
    if ((fpOut = fopen(to, "wb+")) == NULL)
    {
        printf("ERROR: can't opne %s\n", to);
        return ERROR;
    }
    return FINE;
}

void closeFile(void)
{
    fclose(fpIn);
    fclose(fpOut);
    return;
}

status getLength(void)
{
    FILE *fp;
    if ((fp = fopen("metaData.txt", "wb+")) == NULL)
    {
        printf("ERROR: file can't opne");
        return ERROR;
    }
    fseek(fpIn, -(long)sizeof(int), SEEK_END);
    if ((fread(&listLength, sizeof(int), 1, fpIn)) != 1)
    {
        printf("ERROR: failed to read length data\n");
        return ERROR;
    }
    listLength++;
    fseek(fpIn, 0L, SEEK_SET);
    fwrite(&listLength, sizeof(int), 1, fp);
    fclose(fp);
    return FINE;
}

status writeInData(void)
{
    int listCount[listLength];
    int listPos[listLength];
    int order;
    int repeat;
    int pos;
    int current;
    if ((fread(&current, sizeof(int), 1, fpIn)) != 1)
    {
        printf("ERROR: fail to read in data");
        return ERROR;
    }
    for (order = 0, pos = 0; order < listLength; order++)
    {
        listPos[order] = pos;
        repeat = 0;
        while (current == order)
        {
            repeat++;
            pos ++;
            if ((fread(&current, sizeof(int), 1, fpIn)) != 1)
            {
                listCount[order] = repeat;
                goto out;
            }
        }
        listCount[order] = repeat;
    }
out :
    fwrite(listCount, sizeof(int), listLength, fpOut);
    fwrite(listPos, sizeof(int), listLength, fpOut);
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
