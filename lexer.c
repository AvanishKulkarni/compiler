#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *file;
    char ch;

    if (argc == 1)
    {
        printf("Missing filename command-line argument!\n");
        return 1;
    }

    file = fopen(argv[1], "r");

    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }

    return 0;
}