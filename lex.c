#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
    IN_AND,
    IN_OR,
    POS_NUM_SIGN,
    NEG_NUM_SIGN,
    NUM_WHOLE,
    POS_ASSOP,
    NUM_ICONST,
    NUM_DEC,
    SYM_DOT,
    NUM_FRAC,
    NUM_RCONST

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

token checkKeyword(char *lexeme, int line)
{
    return createToken(IDENT, lexeme, line);
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
            else if (ch == '\n')
            {
                line++;
            }
            else if (ch == '<')
            {
                appendChar(lexeme, ch);
                return createToken(LTHAN, lexeme, line);
            }
            else if (ch == '>')
            {
                appendChar(lexeme, ch);
                return createToken(GTHAN, lexeme, line);
            }
            else if (ch == ',')
            {
                appendChar(lexeme, ch);
                return createToken(COMMA, lexeme, line);
            }
            else if (ch == ';')
            {
                appendChar(lexeme, ch);
                return createToken(SEMICOL, lexeme, line);
            }
            else if (ch == '(')
            {
                appendChar(lexeme, ch);
                return createToken(LPAREN, lexeme, line);
            }
            else if (ch == ')')
            {
                appendChar(lexeme, ch);
                return createToken(RPAREN, lexeme, line);
            }
            else if (ch == '{')
            {
                appendChar(lexeme, ch);
                return createToken(LBRACE, lexeme, line);
            }
            else if (ch == '}')
            {
                appendChar(lexeme, ch);
                return createToken(RBRACE, lexeme, line);
            }
            else if (ch == '.')
            {
                appendChar(lexeme, ch);
                state = NUM_DEC;
            }
            else if (ch == '+')
            {
                appendChar(lexeme, ch);
                state = POS_NUM_SIGN;
            }
            else if (ch == '-')
            {
                appendChar(lexeme, ch);
                state = NEG_NUM_SIGN;
            }
            else if (ch == '*')
            {
                appendChar(lexeme, ch);
                state = POS_MUL_ASSOP;
            }
            else if (ch == '/')
            {
                appendChar(lexeme, ch);
                state = POS_DIV_ASSOP;
            }
            else if (ch == '%')
            {
                appendChar(lexeme, ch);
                state = POS_REM_ASSOP;
            }
            else if (ch == '=')
            {
                appendChar(lexeme, ch);
                state = POS_EQ;
            }
            else if (ch == '!')
            {
                appendChar(lexeme, ch);
                state = POS_NEQ;
            }
            else if (ch == '&')
            {
                appendChar(lexeme, ch);
                state = IN_AND;
            }
            else if (ch == '|')
            {
                appendChar(lexeme, ch);
                state = IN_OR;
            }
            else if (isalpha(ch) || ch == '_')
            {
                appendChar(lexeme, ch);
                state = IN_WORD;
            }
            else if (isdigit(ch)) 
            {
                appendChar(lexeme, ch);
                state = NUM_WHOLE;
            }
            break;

        case ERROR:
            return createToken(ERR, lexeme, line);
            break;
        case POS_NUM_SIGN:
            if (ch == '=')
            {
                appendChar(lexeme, ch);
                return createToken(ADDASSOP, lexeme, line);
            }
            else if (isdigit(ch))
            {
                appendChar(lexeme, ch);
                state = NUM_WHOLE;
            }
            else if (ch == '.')
            {
                appendChar(ch, lexeme);
                state = NUM_DEC;
            }
            else
            {
                ungetc(ch, input);
                return createToken(PLUS, lexeme, line);
            }
            break;
        case NEG_NUM_SIGN:
            if (ch == '=')
            {
                appendChar(lexeme, ch);
                return createToken(SUBASSOP, lexeme, line);
            }
            else if (isdigit(ch))
            {
                appendChar(lexeme, ch);
                state = NUM_WHOLE;
            }
            else if (ch == '.')
            {
                appendChar(ch, lexeme);
                state = NUM_DEC;
            }
            else
            {
                ungetc(ch, input);
                return createToken(MINUS, lexeme, line);
            }
            break;
        case NUM_WHOLE:
            if (isdigit(ch))
            {
                appendChar(ch, lexeme);
                state = NUM_WHOLE;
            }
            else if (ch == '.')
            {
                appendChar(ch, lexeme);
                state = NUM_DEC;
            }
            else
            {
                ungetc(ch, input);
                return createToken(ICONST, lexeme, line);
            }
            break;
        case NUM_DEC:
            if (isdigit(ch))
            {
                appendChar(ch, lexeme);
                state = NUM_FRAC;
            }
            else
            {
                ungetc(ch, input);
                return createToken(DOT, lexeme, line);
            }
            break;
        case NUM_FRAC:
            if (isdigit(ch))
            {
                appendChar(ch, lexeme);
                state = NUM_FRAC;
            }
            else 
            {
                ungetc(ch, input);
                return createToken(RCONST, lexeme, line);
            }
            break;
        case POS_MUL_ASSOP:
            if (ch == '=')
            {
                appendChar(lexeme, ch);
                return createToken(MULASSOP, lexeme, line);
            }
            else
            {
                ungetc(ch, input);
                return createToken(MULT, lexeme, line);
            }
            break;
        case POS_DIV_ASSOP:
            if (ch == '=')
            {
                appendChar(lexeme, ch);
                return createToken(DIVASSOP, lexeme, line);
            }
            else
            {
                ungetc(ch, input);
                return createToken(DIV, lexeme, line);
            }
            break;
        case POS_REM_ASSOP:
            if (ch == '=')
            {
                appendChar(lexeme, ch);
                return createToken(REMASSOP, lexeme, line);
            }
            else
            {
                ungetc(ch, input);
                return createToken(REM, lexeme, line);
            }
            break;
        case POS_EQ:
            if (ch == '=')
            {
                appendChar(lexeme, ch);
                return createToken(EQ, lexeme, line);
            }
            else
            {
                ungetc(ch, input);
                return createToken(ASSOP, lexeme, line);
            }
            break;
        case POS_NEQ:
            if (ch == '=')
            {
                appendChar(lexeme, ch);
                return createToken(NEQ, lexeme, line);
            }
            else
            {
                ungetc(ch, input);
                return createToken(NOT, lexeme, line);
            }
            break;
        case IN_AND:
            if (ch == '&')
            {
                appendChar(lexeme, ch);
                return createToken(AND, lexeme, line);
            }
            else
            {
                ungetc(ch, input);
                state = ERROR;
            }
            break;
        case IN_OR:
            if (ch == '|')
            {
                appendChar(lexeme, ch);
                return createToken(OR, lexeme, line);
            }
            else
            {
                ungetc(ch, input);
                state = ERROR;
            }
            break;
        case IN_WORD: // will be used in conjuction with getKeyword()
            if (isalnum(ch) || ch == '_')
            {
                appendChar(lexeme, ch);
                state = IN_WORD;
            }
            else if (ch == ' ')
            {
                ungetc(ch, input);
                return checkKeyword(lexeme, line);
            }
            else
            {
                ungetc(ch, input);
                state = ERROR;
            }
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