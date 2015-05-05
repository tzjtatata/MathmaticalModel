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

