#ifndef LIB4_H_INCLUDED
#define LIB4_H_INCLUDED

typedef int status;
#define FINE 1
#define ERROR -1

#define BUF_LEN 50

status openFile(char *from, char *to);
void closeFile(void);
status getLength(void);
status writeInData(void);
status binaryFilePrint(char *name);

#endif // LIB4_H_INCLUDED
