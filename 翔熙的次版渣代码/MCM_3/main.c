#include <stdio.h>
#include <stdlib.h>
#include "lib3.h"

int main()
{
    initializeCountLength(K_VALUE);
    if (getLength("metaData.txt") == FINE)
    {
        printf("Length got\n");
    }
    if (getVector("dataReference.txt") == FINE)
    {
        printf("dataReference got\n");
    }
    countSort();
    if (writeInDictionary("dictionary.txt") == FINE)
    {
        printf("Dictionary written in\n");
    }
    printf("Enter to exit\n");
    getchar();
    return 0;
}
