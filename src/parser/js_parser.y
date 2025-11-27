%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"
#include "../semantic/symbol_table.h"

extern int yylex();
void yyerror(const char *s);
ASTNode* ast_root;

typedef struct ASTNode ASTNode;
%}

%union {
    int num;
    char* id;
    char* str;
    int bool_val;
    ASTNode* ast;
    char* op;
}

%token <id> ID
%token <num> NUM
%token <str> STRING
%token <bool_val> BOOL
%token VAR FUNCTION IF ELSE RETURN
%token <op> ADDOP
%token <op> RELOP
%token WHILE
%token FOR
%token INT
%token STRING_TYPE
%token BOOL_TYPE


%type <ast> expr stmt stmt_list block program simple_stmt typed_var_decl

%%

program
    : stmt_list              { ast_root = $1; }
    ;

typed_var_decl
    : INT ID '=' expr        { $$ = newVarDecl($2, TYPE_NUMBER, $4); insert_symbol($2, TYPE_NUMBER); }
    | STRING_TYPE ID '=' expr { $$ = newVarDecl($2, TYPE_STRING, $4); insert_symbol($2, TYPE_STRING); }
    | BOOL_TYPE ID '=' expr  { $$ = newVarDecl($2, TYPE_BOOL, $4); insert_symbol($2, TYPE_BOOL); }
    ;

simple_stmt
    : ID '=' expr         { $$ = newAssign($1, $3); }
    | VAR ID '=' expr     { $$ = newAssign($2, $4); insert_symbol($2, TYPE_NUMBER); }
    | INT ID '=' expr                 { $$ = newVarDecl($2, TYPE_NUMBER, $4); insert_symbol($2, TYPE_NUMBER); }
    | STRING_TYPE ID '=' expr         { $$ = newVarDecl($2, TYPE_STRING, $4); insert_symbol($2, TYPE_STRING); }
    | BOOL_TYPE ID '=' expr           { $$ = newVarDecl($2, TYPE_BOOL, $4); insert_symbol($2, TYPE_BOOL); }
    ;

stmt_list
    : /* vacío */            { $$ = NULL; } 
    | stmt                   { $$ = makeStmtList($1); }
    | stmt_list stmt          { $$ = appendStmtList($1, $2); }
    ;

stmt
    : typed_var_decl ';'               { $$ = $1; }
    | VAR ID '=' expr ';'              { $$ = newAssign($2, $4); insert_symbol($2, TYPE_NUMBER); }
    | ID '=' expr ';'                  { $$ = newAssign($1, $3); }
    | FUNCTION ID '(' ')' block        { $$ = newFunction($2, $5); insert_symbol($2, TYPE_FUNCTION); }
    | IF '(' expr ')' block            { $$ = newIf($3, $5, NULL); }
    | IF '(' expr ')' block ELSE block { $$ = newIf($3, $5, $7); }
    | WHILE '(' expr ')' block         { $$ = newWhile($3, $5); }
    | FOR '(' simple_stmt ';' expr ';' simple_stmt ')' block  { $$ = newFor($3, $5, $7, $9); }
    | RETURN expr ';'                  { $$ = newReturn($2); }
    | block                              { $$ = $1; }
    ;

block
    : '{' stmt_list '}'                { $$ = newBlock($2); }
    ;

expr
    : NUM                              { $$ = newNum($1); }
    | STRING                           { $$ = newString($1); }
    | BOOL                             { $$ = newBool($1); }
    | ID                               { $$ = newId($1); }
    | expr ADDOP expr                  { $$ = newBinOp($1, $3, $2); }
    | expr RELOP expr                  { $$ = newBinOp($1, $3, $2); }
    | '(' expr ')'        { $$ = $2; }
    ;


%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
