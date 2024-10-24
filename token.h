typedef enum
{
    IF,
    ELSE,
    PRINT,
    INT,
    FLOAT,
    CHAR,
    STRING,
    BOOL,
    PROGRAM,
    TRUE,
    FALSE,
    IDENT,
    ICONST,
    RCONST,
    SCONST,
    BCONST,
    CCONST,
    PLUS,
    MINUS,
    MULT,
    DIV,
    ASSOP,
    EQ,
    NEQ,
    ADDASSOP,
    SUBASSOP,
    MULASSOP,
    DIVASSOP,
    REMASSOP,
    GTHAN,
    LTHAN,
    AND,
    OR,
    NOT,
    REM,
    COMMA,
    SEMICOL,
    LPAREN,
    RPAREN,
    DOT,
    LBRACE,
    RBRACE,
    ERR,
    DONE,
} token_t;

typedef struct
{
    token_t kind;
    char *lexeme;
    int line;
} token;
