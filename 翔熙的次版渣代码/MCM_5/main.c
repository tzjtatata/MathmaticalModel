#include <stdio.h>
#include <stdlib.h>
#include "lib5.h"

int main()
{
    char s[RECORD_LENGTH+1];
    printf("Input kMer:");
    gets(s);
    if (getLength("countSup.txt") == FINE)
    {
        printf("CountSup gotten.\n");
    }
    if (readInList("binarySearch.txt") == FINE)
    {
        printf("Search list loaded\n");
    }
    if (initializeFilePointer("dataInverse.txt", "checkResult.txt", "dictionary.txt") == FINE)
    {
        printf("File opened\n");
    }
    if (checkData(s, K_VALUE) == FINE)
    {
        printf("Finish checking!\n");
    }
    fileClose();
    getchar();
    return 0;
}
