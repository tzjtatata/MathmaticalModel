#include <stdio.h>
#include <stdlib.h>
#define N 120
#define RECORD 500000
#include <string.h>
FILE * OpenFile(const char *s);

int main()
{
    FILE *fp;
    char s[N];
    char empty[N];
    int line;
    fp = OpenFile("part1.txt");
    for (line = 0; line < RECORD; line++)
    {
        fgets(empty, N, fp);
        fgets(s, N, fp);
        printf("%s", s);
    }
    fclose(fp);
    fp = OpenFile("part2.txt");
    for (line = 0; line < RECORD; line++)
    {
        fgets(empty, N, fp);
        fgets(s, N, fp);
        printf("%s", s);
    }
    return 0;
}

FILE * OpenFile(const char *s)
{
    FILE *fp;
    if ((fp = fopen (s, "r")) == NULL)
    {
        printf("Can't open %s\n", s);
        exit(1);
    }
    return fp;
}
