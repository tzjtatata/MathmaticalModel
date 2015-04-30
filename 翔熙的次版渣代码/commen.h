#ifndef COMMEN_H_INCLUDED
#define COMMEN_H_INCLUDED

typedef int status;
#define ERROR -1
#define FINE 1
#define END -2

#define BUF_LEN 2000
#define RECORD_LENGTH 100
#define K_VALUE 8

status binaryFilePrint(char *name);
int stringToNum(char *pch);

#endif // COMMEN_H_INCLUDED
