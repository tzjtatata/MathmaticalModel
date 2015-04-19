#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

static char **fileName;
static int kNumber;
static int kMerNumber;

static void kInitialize(int k)
{
    int product = 1;
    kNumber = k;
    while (k > 0)
    {
        product *= 4;
        k--;
    }
    kMerNumber = product;
}
//When product is larger than the range of int, this function, as well as all those quote it, can't return correct result

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
    case '\0':
        return END;
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

static status setFileName(void)
{
    int i;
    int max = kMerNumber;
    fileName = (char**)calloc(max, sizeof(char *));
    if (fileName == NULL)
        return ERROR;
    for (i = 0; i < max; i++)
    {
        fileName[i] = (char *)calloc(nameLength, sizeof(char));
        sprintf(fileName[i],"%d.txt",i);
    }
    return FINE;
}

static void clearFileName(void)
{
    int max = kMerNumber;
    int i;
    for (i = 0; i < max; i++)
        free(fileName[i]);
    free(fileName);
    return;
}

static status readKMer(char*s, int series, int location)
{
    int order = stringToNum(s);
    FILE* fp;
    if ((fp = fopen(fileName[order],"a+")) == NULL)
        return ERROR;
    fprintf(fp,"%d,(%d,%d)\n", series, location, location + kNumber);
    fclose(fp);
    return FINE;
}

static status readSingleRecord(char*s, int series)
{
    int i = 0;
    char slice[kNumber + 1];
    while (i < RECORD_LENGTH - kNumber + 1)
    {
        strncpy(slice, s, kNumber);
        slice[kNumber] = '\0';
        if (readKMer(slice, series, i) == ERROR)
            return ERROR;
        i++;
        s++;
    }
    return FINE;
}

static status readMultipleRecord(char *recordName)
{
    FILE *fp;
    char line[RECORD_LENGTH + 2];
    int i = 0;
    if ((fp = fopen(recordName,"r")) == NULL)
    {
        printf("File can't find!\n");
        return ERROR;
    }
    while (fgets(line, RECORD_LENGTH+2, fp) != NULL)
    {
        i++;
        if (readSingleRecord(line, i) == ERROR)
        {
            return ERROR;
        }
    }
    return FINE;
}

static status kMerCheck(char *s)
{
    int order = stringToNum(s);
    char line[OUTPUT_LENGTH];
    FILE * fp;
    if ((fp = fopen(fileName[order], "r")) == NULL)
    {
        printf("Can't find that k-mer\n");
        return ERROR;
    }
    while ((fgets(line, OUTPUT_LENGTH, fp)) != NULL)
    {
        fputs(line, stdout);
    }
    return FINE;
}

status readData_Shell(char *s, int k)
{
    kInitialize(k);
    setFileName();
    if (readMultipleRecord(s) == ERROR)
        return ERROR;
    clearFileName();
    printf("enter to exit:");
    getchar();getchar();
    return 0;
}

status checkData_Shell(char *s, int k)
{
    kInitialize(k);
    setFileName();
    if (kMerCheck(s) == ERROR)
        return ERROR;
    clearFileName();
    printf("enter to exit:");
    getchar();getchar();
    return 0;
}

status shell(void)
{
    int mode;
    char s[RECORD_LENGTH+1];
    int k;
    printf("Choose a mode, 1 to read in Data, 2 to search one k-mer, others to prove you are a idiot:");
    scanf("%d", &mode);
    printf("What is that damn k-value?");
    scanf("%d", &k);
    if (mode == 1)
        return readData_Shell(s, k);
    if (mode == 2)
        return checkData_Shell(s, k);
    printf("You are an out-of-mind absolute extraordinary IDOIT indeed\n");
    printf("How I wished I could BURN your computer!\n");
    printf("enter to exit, IDOIT:");
    getchar();getchar();
    return ERROR;
}

