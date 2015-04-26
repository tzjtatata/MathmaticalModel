#include <stdio.h>
#include <stdlib.h>
#include "lib5.h"

int main()
{
    char s[80];
    printf("Input kMer:");
    gets(s);
    printf("%d\n", getLength("metaData.txt"));
    printf("%d\n", readInList("bisearchTable.txt"));
    printf("%d\n", checkData(s, "dataOrganize.txt", "checkResult.txt", 8));
    getchar();
    return 0;
}
