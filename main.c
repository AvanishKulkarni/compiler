#include "token.h"
#include <stdio.h>
extern FILE *yyin;
extern int yylex();
extern char *yytext;
int main(int argc, char **argv)
{
    yyin = fopen(argv[1], "r");
    if (!yyin)
    {
        printf("could not open program.c!\n");
        return 1;
    }
    token_t t;
    while ((t = yylex()) != DONE)
    {
        printf("token: %d text: %s\n", t, yytext);
    }
    printf("token: %d text: %s\n", t, yytext);
}
