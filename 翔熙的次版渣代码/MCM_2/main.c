#include <stdio.h>
#include <stdlib.h>
#include "lib2.h"

int main()
{
    kInitialize(5);
    printf("%d\n", pointerInitialize());
    printf("%d\n", fileOpen("DataOutput.txt"));
    printf("%d\n", writeData());
    fileClose();
    getchar();
    return 0;
}
