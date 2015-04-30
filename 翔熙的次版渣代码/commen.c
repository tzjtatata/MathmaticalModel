#include <stdlib.h>
#include <stdio.h>
#include "commen.h"

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

int stringToNum(char *pch)
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

