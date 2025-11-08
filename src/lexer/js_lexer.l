%{
#include "parser.h"
#include "ast.h"
#include <string.h>
#include <stdlib.h>
%}

%%

"let"|"const"|"var"      { return VAR; }
"function"               { return FUNCTION; }
"if"                     { return IF; }
"else"                   { return ELSE; }
"return"                 { return RETURN; }
"true"|"false"           { yylval.bool_val = (strcmp(yytext,"true")==0); return BOOL; }

[a-zA-Z_$][a-zA-Z0-9_$]* { yylval.id = strdup(yytext); return ID; }
[0-9]+                   { yylval.num = atoi(yytext); return NUM; }
\"[^\"]*\"               { yylval.str = strdup(yytext); return STRING; }

"=="|"!="|"<="|">="      { return RELOP; }
"+"|"-"|"*"|"/"          { return ADDOP; }

"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/   { /* comentario bloque */ }
"//".*                   { /* comentario línea */ }

[ \t\n]+                 { /* ignorar */ }

.                        { return yytext[0]; }

%%

int yywrap(void) { return 1; }
