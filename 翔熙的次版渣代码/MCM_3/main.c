#include <stdio.h>
#include <stdlib.h>
#include "lib3.h"

int main()
{
    if (getLength("metaData.txt") == FINE)
    {
        printf("Length got\n");
    }
    if (getVector("dataReference.txt") == FINE)
    {
        printf("dataReference got\n");
    }
    countSort(65536);
    if (writeInReference("referOrganize.txt") == FINE)
    {
        printf("referOrganize wrote in\n");
    }
    if (organizeData("dataInverse.txt", "dataOrganize.txt") == FINE)
    {
        printf("data Organized!");
    }
    getchar();
    return 0;
}
