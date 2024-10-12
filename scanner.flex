%{
#include "token.h"
%}
%%
(" "|\t|\n) { /* skip whitespace */ }
program { return PROGRAM; }
string { return STRING; }
else { return ELSE; }
if { return IF; }
int { return INT; }
float { return FLOAT; }
char { return CHAR; }
print { return PRINT; }
bool { return BOOL; }
true { return TRUE; }
false { return FALSE; }
<<EOF>> { return DONE; }
[a-zA-Z_][a-zA-Z0-9_]* { return IDENT; }
[+-]?[0-9]*\.[0-9]+ { return RCONST; }
[+-]?[0-9]+ { return ICONST; }
\"[^\"]*\" { return SCONST; }
"//".* { /* skip single line comment */ }
"/*".*"*/" { /* skip multi line comment */ }

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULT; }
"/" { return DIV; }
"%" { return REM; }
"=" { return ASSOP; }
"!" { return NOT; }
"+=" { return ADDASSOP; }
"-=" { return SUBASSOP; }
"*=" { return MULASSOP; }
"/=" { return DIVASSOP; }
"%=" { return REMASSOP; }
"==" { return EQ; }
"!=" { return NEQ; }

"&&" { return AND; }
"||" { return OR; }

"<" { return LTHAN; }
">" { return GTHAN; }
"," { return COMMA; }
";" { return SEMICOL; }
"(" { return LPAREN; }
")" { return RPAREN; }
"{" { return LBRACE; }
"}" { return RBRACE; }
"." { return DOT; }
. { return ERR; } { /* unrecognized token */ }
%%
int yywrap() { return 1; }