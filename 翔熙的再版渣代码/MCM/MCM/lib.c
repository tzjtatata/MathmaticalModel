#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lib.h"
static int kNumber;
static int kMerNumber;
static treeNode nodeList[NODE_NUMBER];
static int nodeCount = 2;
static int leafCount = 0;


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

static void printSingleRecord(SingleRecord *input)
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

static SingleRecord* constructSingleRecord(int recordOrder)
{
    SingleRecord* input;
    input = (SingleRecord*)malloc(sizeof(SingleRecord));
    (*input).recordOrder = recordOrder;
    (*input).kMerOrder = (int *)calloc(RECORD_LENGTH - kNumber + 1, sizeof(int));
    return input;
}

static int stringToNum(char *s)
{
    int position = 1;
    int flag = 1;
    while (*s != '\0')
    {
        while (nodeList[position].content != *s)
        {
            if (nodeList[position].content == 0)
            {
                nodeList[position].content = *s;
                flag = 0;
                break;
            }//如果此层一个节点都没有，说明这一层是新建的
            if (nodeList[position].brother == 0)
            {
                nodeList[position].brother = nodeCount;
                position = nodeCount;
                nodeCount++;
                nodeList[position].content = *s;
                flag = 0;
                break;
            }//此层未找到该字符，则新建一个节点
            position = nodeList[position].brother;
        }
        if (nodeList[position].child == 0)
        {
            nodeList[position].child = nodeCount;
            nodeCount++;
            if (nodeCount >= NODE_NUMBER)
            {
                printf("node number not enough!\n");
                exit(1);
            }
        }
        position = nodeList[position].child;
        s++;
    }
    if (flag == 0)
    {
        nodeList[position].child = leafCount;
        nodeList[position].content = '\0';
        leafCount++;
    }
    if (nodeList[position].content != '\0')
        return -1;//如果输入字符串过短，被已有字符串覆盖，则输出-1表示错误
    return nodeList[position].child;
}

static SingleRecord * _readSingleRecord(char *s, int recordOrder)
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

static status writeInSingleRecord(FILE* fp, SingleRecord input)
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

static status writeInMultipleRecord(char *recordName, char *outputFile)
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
    return writeInMultipleRecord(s, "DataOutput.txt");
}

static int loadSingleRecord(SingleRecord* SR, FILE *fp)
{
    int out = 1;
    out *= fread(&((*SR).recordOrder), sizeof(int), 1, fp);
    out *= fread((*SR).kMerOrder, sizeof(int), RECORD_LENGTH - kNumber + 1, fp);
    return out;
}

static status showData(char *name)
{
    FILE * fp;
    SingleRecord * SR = NULL;
    SR = constructSingleRecord(0);

    if ((fp = fopen(name, "rb+")) == NULL)
    {
        printf("%s can't open", name);
        return ERROR;
    }
    while (loadSingleRecord(SR, fp) != 0)
    {
        printSingleRecord(SR);
    }
    return FINE;
}

status writeInTree(char *treeName)
{
    FILE *fp = fopen(treeName, "wb+");
    if (fp == NULL)
    {
        printf("ERROR: can't open %s\n", treeName);
        return ERROR;
    }
    if ((fwrite(nodeList, sizeof(treeNode), nodeCount, fp)) != nodeCount)
    {
        printf("ERROR: fail to write data into %s\n", treeName);
        return ERROR;
    }
    fclose(fp);
    fp = fopen("leafCount.dat", "wb+");
    fwrite(&leafCount, sizeof(int), 1, fp);
    fclose(fp);
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
