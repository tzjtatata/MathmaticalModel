#ifndef LIB2_H_INCLUDED
#define LIB2_H_INCLUDED

typedef int status;
#define ERROR -1
#define FINE 1
#define END -2

typedef int _kMerOrder;

#define BUF_LEN 50
#define RECORD_LENGTH 100

void kInitialize(int k);
status pointerInitialize(void);
status fileOpen(char *s);
void fileClose(void);
status writeData(void);
void printFile(char *s);

#endif // LIB2_H_INCLUDED
