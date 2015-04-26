#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main()
{
    printf("Reading records...\n");
    writeInMultipleRecord_Shell("testCase.txt", 8);
    return 0;
}
