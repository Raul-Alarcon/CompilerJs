#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static char *indent(int level) {
    static char buf[256];
    int i;
    buf[0]=0;
    for(i=0;i<level && i<250;i++) buf[i]=' '; buf[i]=0;
    return buf;
}

ASTNode* newNum(int val) {
    ASTNode* n = calloc(1,sizeof(ASTNode));
    n->type = NODE_NUM;
    n->num = val;
    return n;
}
ASTNode* newId(char* name) {
    ASTNode* n = calloc(1,sizeof(ASTNode));
    n->type = NODE_ID;
    n->id = strdup(name);
    return n;
}
ASTNode* newBinOp(ASTNode* l, ASTNode* r, char* op) {
    ASTNode* n = calloc(1,sizeof(ASTNode));
    n->type = NODE_BINOP;
    n->left = l;
    n->right = r;
    n->op = strdup(op);
    return n;
}
ASTNode* newAssign(char* id, ASTNode* expr) {
    ASTNode* n = calloc(1,sizeof(ASTNode));
    n->type = NODE_ASSIGN;
    n->id = strdup(id);
    n->left = expr;
    return n;
}
ASTNode* newReturn(ASTNode* expr) {
    ASTNode* n = calloc(1,sizeof(ASTNode));
    n->type = NODE_RETURN;
    n->left = expr;
    return n;
}
ASTNode* newFunction(char* id, ASTNode* body) {
    ASTNode* n = calloc(1,sizeof(ASTNode));
    n->type = NODE_FUNCTION;
    n->id = strdup(id);
    n->left = body;
    return n;
}
ASTNode* newBlock(ASTNode* stmts) {
    ASTNode* n = calloc(1,sizeof(ASTNode));
    n->type = NODE_BLOCK;
    n->left = stmts;
    return n;
}
ASTNode* makeStmtList(ASTNode* stmt) {
    ASTNode* n = calloc(1,sizeof(ASTNode));
    n->type = NODE_STMTLIST;
    n->next = stmt;
    return n;
}
ASTNode* appendStmtList(ASTNode* list, ASTNode* stmt) {
    if (!list) return makeStmtList(stmt);
    ASTNode* cur = list;
    while(cur->next) cur = cur->next;
    cur->next = stmt;
    return list;
}

void printAST(ASTNode* node, int level) {
    if (!node) return;
    switch(node->type) {
        case NODE_NUM: printf("%sNUM(%d)\n", indent(level), node->num); break;
        case NODE_ID: printf("%sID(%s)\n", indent(level), node->id); break;
        case NODE_BINOP: printf("%sBINOP(%s)\n", indent(level), node->op); printAST(node->left, level+2); printAST(node->right, level+2); break;
        case NODE_ASSIGN: printf("%sASSIGN(%s)\n", indent(level), node->id); printAST(node->left, level+2); break;
        case NODE_RETURN: printf("%sRETURN\n", indent(level)); printAST(node->left, level+2); break;
        case NODE_FUNCTION: printf("%sFUNCTION %s\n", indent(level), node->id); printAST(node->left, level+2); break;
        case NODE_BLOCK: printf("%sBLOCK\n", indent(level)); printAST(node->left, level+2); break;
        case NODE_STMTLIST: printf("%sSTMTLIST\n", indent(level)); { ASTNode* cur = node->next; while(cur) { printAST(cur, level+2); cur = cur->next; } } break;
        default: printf("%sUNKNOWN\n", indent(level)); break;
    }
}
