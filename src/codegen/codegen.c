#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

static int temp = 0;

void generate_ir(ASTNode* node) {
    if (!node) return;

    switch(node->type) {
        case NODE_STMTLIST: {
            ASTNode* cur = node->next;
            while(cur) { generate_ir(cur); cur = cur->next; }
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
        default:
            /* Other nodes */
            break;
    }
}
