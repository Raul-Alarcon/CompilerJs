%{ 
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"
#include "../semantic/symbol_table.h"
#include "../../build/y.tab.h"
%}

%%

"let"|"const"|"var"      { return VAR; }
"function"               { return FUNCTION; }
"int"                    { return INT; }
"string"                 { return STRING_TYPE; }
"bool"                   { return BOOL_TYPE; }
"if"                     { return IF; }
"else"                   { return ELSE; }
"while"                  { return WHILE; }
"for"                    { return FOR; }
"return"                 { return RETURN; }
"true"|"false"           { yylval.bool_val = (strcmp(yytext, "true") == 0); return BOOL; }

[a-zA-Z_$][a-zA-Z0-9_$]* { yylval.id = strdup(yytext); return ID; }
[0-9]+                   { yylval.num = atoi(yytext); return NUM; }
\"([^"]*)\"              { 
                            int len = yyleng - 2; 
                            yylval.str = (char*)malloc(len + 1);
                            strncpy(yylval.str, yytext + 1, len);
                            yylval.str[len] = '\0';
                            return STRING;
                         }

"=="|"!="|"<="|">="|">"|"<"  { yylval.op = strdup(yytext); return RELOP; }
"+"|"-"|"*"|"/"          { yylval.op = strdup(yytext); return ADDOP; }

"/*"([^*]|\n|(\*+([^*/]|\n)))*\*+"/"   { /* comentario bloque */ }
"//".*                   { /* comentario línea */ }

[ \t\r\n]+               { /* ignorar espacios */ }

.                        { return yytext[0]; }

%%

int yywrap(void) { return 1; }
