#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

#include "../commen.h"

#define nameLength 20
#define OUTPUT_LENGTH 40

typedef struct{
    int recordOrder;
    int *kMerOrder;
}SingleRecord;

status writeInMultipleRecord_Shell(char *s, int k);
status showData_Shell(char *name, int k);

#endif // LIB_H_INCLUDED
