#include <stdio.h>
#include <stdlib.h>
#include "lib2.h"

int main()
{
    kInitialize(K_VALUE);
    if (pointerInitialize() == FINE)
        printf("Initialize pointers\n");

    if (fileOpen("DataOutput.txt") == FINE)
        printf("Open Files\n");
    if (writeData() == FINE)
        printf("File written in");
    fileClose();
    getchar();
    return 0;
}
