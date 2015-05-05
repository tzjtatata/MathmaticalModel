#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main()
{
    printf("Reading records...\n");
    writeInMultipleRecord_Shell("testCase.txt", K_VALUE);
    if (writeInTree("tree.dat") == FINE)
        printf("Tree written in.\n");
    printf("enter to exit:");
    getchar();
    return 0;
}
