#ifndef LIB4_H_INCLUDED
#define LIB4_H_INCLUDED

#include "../commen.h"

status openFile(char *from, char *to);
void closeFile(void);
status getLength(void);
status writeInData(void);
status binaryFilePrint(char *name);

#endif // LIB4_H_INCLUDED
