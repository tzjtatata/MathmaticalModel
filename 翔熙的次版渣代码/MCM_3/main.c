#include <stdio.h>
#include <stdlib.h>
#include "lib3.h"

int main()
{
    printf("%d\n", getLength("metaData.txt"));
    printf("%d\n", getVector("dataReference.txt"));
    shellSort();
    printf("%d\n", writeInReference("referOrganize.txt"));
    printf("%d\n", organizeData("dataInverse.txt", "dataOrganize.txt"));
    getchar();
    return 0;
}
