thing = """- MINUS
* MULT 
/ DIV 
= ASSOP 
== EQ 
!= NEQ 
< LTHAN 
> GTHAN 
% REM 
&& AND 
|| OR 
! NOT 
+= ADDASSOP 
-= SUBASSOP 
*= MULASSOP 
/= DIVASSOP 
%= REMASSOP"""

escaped_characters = {
    '\\',  # Backslash
    '"',   # Double quote
    '[',   # Opening square bracket
    ']',   # Closing square bracket
    '^',   # Caret (negation in character classes)
    '-',   # Dash (range in character classes)
    '(',   # Opening parenthesis
    ')',   # Closing parenthesis
    '.',   # Period (matches any character except newline)
    '*',   # Asterisk (zero or more occurrences)
    '+',   # Plus (one or more occurrences)
    '?',   # Question mark (zero or one occurrence)
    '|',   # Vertical bar (alternation)
    '{',   # Opening curly brace
    '}',   # Closing curly brace
}

for op in thing.split('\n'):
    sym, token = op.split()
    if sym in escaped_characters:
        print(f"\\{sym} return {token};")
    else:
        print(f"{sym} {{ return {token}; }}")
