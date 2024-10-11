#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

FILE *input;
char *lexeme;

typedef enum
{
    START,
    ERROR,
    IN_WORD,
    IN_REAL,
    IN_INT,
    IN_STR,
    IN_COMMENT,
    IN_ASSOP,

} lexState;

token_t lex()
{
    char ch;
    lexState state = START;
    int line = 1;

    while (ch = fgetc(input))
    {
        switch (state)
        {
        case START:
            if (ch == ' ' || ch == '\t')
            {
            } // do nothing
            if (ch == '\n')
            {
                line++;
            }
            if (ch == '<')
            {
                return LTHAN;
            }
            break;

        case ERROR:

            break;
        case IN_WORD:

            break;
        case IN_REAL:

            break;
        case IN_INT:

            break;
        case IN_STR:

            break;
        case IN_COMMENT:

            break;
        case IN_ASSOP:

            break;
        }
    }
}