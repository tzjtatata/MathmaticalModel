#include <stdio.h>
#include <stdlib.h>
#include "lib2.h"

int main()
{
    kInitialize(8);
    if (pointerInitialize() == FINE)
        printf("Initialize pointers\n");

    if (fileOpen("DataOutput.txt") == FINE)
        printf("Open Files\n");
    if (writeData() == FINE)
        printf("File ")
    fileClose();
    getchar();
    return 0;
}
