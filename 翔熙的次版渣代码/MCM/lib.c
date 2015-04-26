#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lib.h"
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
    default:
        return ERROR;
    }
}

static int stringToNum(char *pch)
{
    int result = 0;
    while (*pch != '\0')
    {
        result <<= 2;
        result |= charToNum(*pch);
        pch++;
    }
    return result;
}

void printSingleRecord(SingleRecord *input)
{
    int i;
    printf("%d:\n", (*input).recordOrder);

    for (i = 0; i < RECORD_LENGTH - kNumber + 1; i++)
    {
        printf("%d ", (*input).kMerOrder[i]);
    }
    printf("\n");
    return;
}

SingleRecord* constructSingleRecord(int recordOrder)
{
    SingleRecord* input;
    input = (SingleRecord*)malloc(sizeof(SingleRecord));
    (*input).recordOrder = recordOrder;
    (*input).kMerOrder = (int *)calloc(RECORD_LENGTH - kNumber + 1, sizeof(int));
    return input;
}

void destroySingleRecord(SingleRecord* input)
{
    free((*input).kMerOrder);
    return;
}

SingleRecord * _readSingleRecord(char *s, int recordOrder)
{
    int i;
    char slice[kNumber + 1];
    SingleRecord * output = (SingleRecord *)malloc(sizeof(SingleRecord));
    output = constructSingleRecord(recordOrder);
    for (i = 0; i < RECORD_LENGTH - kNumber + 1; i++, s++)
    {
        strncpy(slice, s, kNumber);
        slice[kNumber] = '\0';
        (*output).kMerOrder[i] = stringToNum(slice);
    }
    return output;
}

status writeInSingleRecord(FILE* fp, SingleRecord input)
{
    int foo = input.recordOrder;
    if (fwrite(&foo, sizeof(int), 1, fp) != 1)
    {
        return ERROR;
    }
    if (fwrite(input.kMerOrder, sizeof(int), (RECORD_LENGTH - kNumber + 1), fp) != (RECORD_LENGTH - kNumber + 1))
    {
        return ERROR;
    }
    return FINE;
}

status writeInMultipleRecord(char *recordName, char *outputFile)
{
    FILE *fpIn;
    FILE *fpOut;
    char line[RECORD_LENGTH + 2];
    int i = 0;
    if ((fpIn = fopen(recordName,"r")) == NULL)
    {
        printf("File can't find!\n");
        return ERROR;
    }
    if ((fpOut = fopen(outputFile,"wb+")) == NULL)
    {
        printf("File can't find!\n");
        return ERROR;
    }
    while (fgets(line, RECORD_LENGTH+2, fpIn) != NULL)
    {
        i++;
        if (writeInSingleRecord(fpOut,*_readSingleRecord(line, i)) == ERROR)
        {
            return ERROR;
        }
        printf("Record:%8d\r", i);
    }
    printf("\n");
    fclose(fpIn);
    fclose(fpOut);
    return FINE;
}

status writeInMultipleRecord_Shell(char *s, int k)
{
    kInitialize(k);
    if (writeInMultipleRecord(s, "DataOutput.txt") == ERROR)
    {
        getchar();
        return ERROR;
    }
    printf("enter to exit:");
    getchar();
    return FINE;
}

int loadSingleRecord(SingleRecord* SR, FILE *fp)
{
    int out = 1;
    out *= fread(&((*SR).recordOrder), sizeof(int), 1, fp);
    out *= fread((*SR).kMerOrder, sizeof(int), RECORD_LENGTH - kNumber + 1, fp);
    return out;
}

status showData(char *name)
{
    FILE * fp;
    SingleRecord * SR = NULL;
    SR = constructSingleRecord(0);

    if ((fp = fopen(name, "rb+")) == NULL)
    {
        printf("%s can't open", name);
        return ERROR;
    }
    int i = 0;
    while (loadSingleRecord(SR, fp) != 0)
    {
        printSingleRecord(SR);
        if (i++ > 1000)
            break;
    }
    return FINE;
}

status showData_Shell(char *name, int k)
{
    kInitialize(k);
    if (showData(name) == ERROR)
    {
        printf("ERROR!");
        getchar();
        return ERROR;
    }
    printf("enter to exit:");
    getchar();
    return FINE;
}
