#include <stdio.h>
#include <stdlib.h>
#include "lib5.h"

int main()
{
    char s[RECORD_LENGTH+1];
    printf("Input kMer:");
    gets(s);
    printf("%d\n", getLength("countSup.txt"));
    printf("%d\n", readInList("binarySearch.txt"));
    printf("%d\n", checkData(s, "dataOrganize.txt", "checkResult.txt", K_VALUE));
    getchar();
    return 0;
}
