#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

typedef int status;
#define ERROR -1
#define FINE 1
#define END -2

#define nameLength 20
#define RECORD_LENGTH 100
#define OUTPUT_LENGTH 40

status readData_Shell(char *s, int k);
status checkData_Shell(char *s, int k);
status shell(void);

#endif // LIB_H_INCLUDED
