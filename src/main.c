#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern ASTNode* ast_root;
extern int yyparse();

int main(int argc, char** argv) {
    if (yyparse() == 0) {
        printf("=== AST ===\n");
        printAST(ast_root, 0);
        printf("\n=== IR ===\n");
        extern void generate_ir(ASTNode*);
        generate_ir(ast_root);
    } else {
        fprintf(stderr, "Parsing failed.\n");
        return 1;
    }
    return 0;
}
