#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"

static int temp = 0;
static int labelCount = 0;

char* newLabel() {
    char* label = (char*)malloc(16);
    sprintf(label, "L%d", labelCount++);
    return label;
}

void generate_ir(ASTNode* node) {
    if (!node) return;

    switch(node->type) {
        case NODE_STMTLIST: {
            ASTNode* cur = node->next;
            while(cur) { 
                generate_ir(cur); 
                cur = cur->next; 
            }
            break;
        }

        case NODE_ASSIGN: {
            generate_ir(node->left);
            printf("STORE %s <- t%d\n", node->id, temp-1);
            break;
        }

        case NODE_NUM: {
            printf("t%d = %d\n", temp++, node->num);
            break;
        }

        case NODE_BINOP: {
            generate_ir(node->left);
            generate_ir(node->right);
            int r = temp-1;
            int l = temp-2;
            printf("t%d = t%d %s t%d\n", temp++, l, node->op, r);
            break;
        }

        case NODE_RETURN: {
            generate_ir(node->left);
            printf("RETURN t%d\n", temp-1);
            break;
        }

        case NODE_FUNCTION: {
            printf("FUNC %s:\n", node->id);
            generate_ir(node->left);
            printf("ENDFUNC\n");
            break;
        }

        case NODE_BLOCK:
            generate_ir(node->left);
            break;

        case NODE_IF: {
            char* Ltrue = newLabel();
            char* Lend = newLabel();
 
            generate_ir(node->left);  
            printf("IF t%d GOTO %s\n", temp-1, Ltrue);
            printf("GOTO %s\n", Lend);
 
            printf("%s:\n", Ltrue);
            generate_ir(node->right);
 
            printf("%s:\n", Lend);
            break;
        }
        case NODE_FOR: { 
            char *Lstart = newLabel();
            char *Lbody = newLabel();
            char *Lend = newLabel();
 
            if (node->init) generate_ir(node->init);
 
            printf("%s:\n", Lstart);
 
            if (node->cond) {
                generate_ir(node->cond);                      
                printf("IF t%d GOTO %s\n", temp-1, Lbody);
                printf("GOTO %s\n", Lend);
            } else { 
                printf("GOTO %s\n", Lbody);
            }
 
            printf("%s:\n", Lbody);
            if (node->body) generate_ir(node->body);
 
            if (node->step) generate_ir(node->step);
 
            printf("GOTO %s\n", Lstart);
 
            printf("%s:\n", Lend);
            break;
        }
        default: 
            break;
    }
}
