#include "token.h"
#include <stdio.h>
extern FILE *input;
extern token lex();
int main(int argc, char **argv)
{
    input = fopen(argv[1], "r");
    if (!input)
    {
        printf("could not open program.c!\n");
        return 1;
    }
    token t;
    while ((t = lex()).kind != DONE)
    {
        printf("token: %d text: %s\n", t.kind, t.lexeme);
    }
    printf("token: %d text: %s\n", t.kind, t.lexeme);
}
