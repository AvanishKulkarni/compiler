%{
#include "token.h"
%}
DIGIT [0-9]
LETTER [a-zA-Z]
%%
(" "|\t|\n) /* skip whitespace */
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
\+ { return PLUS; }
\- { return MINUS; }
\* { return MULT; }
\/ { return DIV; }
= { return ASSOP; }
== { return EQ; }
!= { return NEQ; }
\< { return LTHAN; }
> { return GTHAN; }
% { return REM; }
&& { return AND; }
\|\| { return OR; }
! { return NOT; }
\+= { return ADDASSOP; }
\-= { return SUBASSOP; }
\*= { return MULASSOP; }
\/= { return DIVASSOP; }
%= { return REMASSOP; }

%%
int yywrap() { return 1; }