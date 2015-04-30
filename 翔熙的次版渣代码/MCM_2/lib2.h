#ifndef LIB2_H_INCLUDED
#define LIB2_H_INCLUDED

#include "../commen.h"

typedef int _kMerOrder;

void kInitialize(int k);
status pointerInitialize(void);
status fileOpen(char *s);
void fileClose(void);
status writeData(void);
void printFile(char *s);

#endif // LIB2_H_INCLUDED
