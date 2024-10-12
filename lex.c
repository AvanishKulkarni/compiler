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
    POS_ADD_ASSOP,
    POS_SUB_ASSOP,
    POS_MUL_ASSOP,
    POS_DIV_ASSOP,
    POS_REM_ASSOP,
    POS_EQ,
    POS_NEQ,

} lexState;

token createToken(token_t kind, char *lexeme, int linenum)
{
    token ret;
    ret.kind = kind;
    ret.lexeme = lexeme;
    ret.line = linenum;
    return ret;
}

void appendChar(char *str, char c)
{
    size_t len = strlen(str);
    str = (char *)realloc(str, (len + 1) * sizeof(char));
    str[len] = c;
    str[len + 1] = '\0';
}

token lex()
{
    char ch;
    lexState state = START;
    int line = 1;
    lexeme = malloc(sizeof(char));
    lexeme[0] = '\0';

    while ((ch = fgetc(input)) != EOF)
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
                appendChar(lexeme, ch);
                return createToken(LTHAN, lexeme, line);
            }
            if (ch == '>')
            {
                appendChar(lexeme, ch);
                return createToken(GTHAN, lexeme, line);
            }
            if (ch == ',')
            {
                appendChar(lexeme, ch);
                return createToken(COMMA, lexeme, line);
            }
            if (ch == ';')
            {
                appendChar(lexeme, ch);
                return createToken(SEMICOL, lexeme, line);
            }
            if (ch == '(')
            {
                appendChar(lexeme, ch);
                return createToken(LPAREN, lexeme, line);
            }
            if (ch == ')')
            {
                appendChar(lexeme, ch);
                return createToken(RPAREN, lexeme, line);
            }
            if (ch == '{')
            {
                appendChar(lexeme, ch);
                return createToken(LBRACE, lexeme, line);
            }
            if (ch == '}')
            {
                appendChar(lexeme, ch);
                return createToken(RBRACE, lexeme, line);
            }
            if (ch == '.')
            {
                appendChar(lexeme, ch);
                return createToken(RBRACE, lexeme, line);
            }
            if (ch == '+')
            {
                state = POS_ADD_ASSOP;
            }
            break;

        case ERROR:
            return createToken(ERR, lexeme, line);
            break;
        case POS_ADD_ASSOP:

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
        default:
            state = ERROR;
            break;
        }
    }
    return createToken(DONE, lexeme, line);
}