#include <stdio.h>
#include <stdlib.h>
#include "lib4.h"

int main()
{
    printf("%d\n", openFile("referORganize.txt", "bisearchTable.txt"));
    printf("%d\n", getLength());
    printf("%d\n", writeInData());
    closeFile();
    getchar();
    return 0;
}
