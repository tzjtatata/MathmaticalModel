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
    if (organizeData("dataInverse.txt", "dataOrganize.txt") == FINE)
    {
        printf("data Organized!");
    }
    getchar();
    return 0;
}
