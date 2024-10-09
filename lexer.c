#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *file;
    char ch;

    if (argc == 1)
    {
        perror("Missing filename command-line argument!");
        return 1;
    }

    file = fopen(argv[1], 'r');

    if (file == NULL)
    {
        perror("Error opening file!");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
    }

    return 0;
}