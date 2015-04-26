#ifndef LIB5_H_INCLUDED
#define LIB5_H_INCLUDED

#define BUF_LEN 2000
typedef int status;
#define ERROR -1
#define FINE 1

status getLength(char *s);
status binaryFilePrint(char *name);
status readInList(char *name);
status checkData(char *input, char *from, char *to, int k);

#endif // LIB5_H_INCLUDED
