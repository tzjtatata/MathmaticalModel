#ifndef LIB3_H_INCLUDED
#define LIB3_H_INCLUDED

#define BUF_LEN 50
typedef int status;
#define ERROR -1
#define FINE 1

status getLength(char *s);
status getVector(char *s);
void shellSort(void);
void vecListPrint(void);
status organizeData(char *from, char *to);
status writeInReference(char *s);
status referPrint(char *s);
status binaryFilePrint(char *name);

#endif // LIB3_H_INCLUDED
