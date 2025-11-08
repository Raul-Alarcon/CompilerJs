%{
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"   /* tokens from bison */
#include "ast.h"
extern int yylval;
%}

%%

"let"|"const"|"var"      { return VAR; }
"function"               { return FUNCTION; }
"if"                     { return IF; }
"else"                   { return ELSE; }
"return"                 { return RETURN; }
"true"                  { yylval.bool_val = 1; return BOOL; }
"false"                 { yylval.bool_val = 0; return BOOL; }

[a-zA-Z_$][a-zA-Z0-9_$]* {
    yylval.id = strdup(yytext);
    return ID;
}

[0-9]+ {
    yylval.num = atoi(yytext);
    return NUM;
}

\"[^\"]*\" {
    /* strip quotes */
    int len = yyleng - 2;
    char *s = malloc(len + 1);
    if(len > 0) strncpy(s, yytext+1, len);
    s[len] = '\0';
    yylval.str = s;
    return STRING;
}

/"=="| "!=" | "<=" | ">="     { return RELOP; }
"+"|"-"|"*"|"/"               { yylval.op = strdup(yytext); return ADDOP; }

"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/   { /* block comment */ }
"//".*                   { /* line comment */ }
[ \t\r\n]+               { /* ignore whitespace */ }
.                        { return yytext[0]; }

%%
