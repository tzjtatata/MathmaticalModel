#ifndef LIB5_H_INCLUDED
#define LIB5_H_INCLUDED

#include "../commen.h"

status getLength(char *s);
status readInList(char *name);
status initializeFilePointer(char *from, char *to, char *dictionary);
status checkData(char *input, int k);
void fileClose(void);

#endif // LIB5_H_INCLUDED
