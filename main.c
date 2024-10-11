#include "token.h"
#include <stdio.h>
extern FILE *input;
extern token_t lex();
extern char *lexeme;
int main(int argc, char **argv)
{
    input = fopen(argv[1], "r");
    if (!input)
    {
        printf("could not open program.c!\n");
        return 1;
    }
    token t;
    while ((t = lex()) != DONE)
    {
        printf("token: %d text: %s\n", t, lexeme);
    }
    printf("token: %d text: %s\n", t, lexeme);
}
