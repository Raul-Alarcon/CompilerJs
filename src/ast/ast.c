#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static char *indent(int level)
{
    static char buf[256];
    int i;
    buf[0] = 0;
    for (i = 0; i < level && i < 250; i++)
        buf[i] = ' ';
    buf[i] = 0;
    return buf;
}

ASTNode *newNum(int val)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_NUM;
    n->num = val;
    return n;
}
ASTNode *newId(char *name)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_ID;
    n->id = strdup(name);
    return n;
}
ASTNode *newBinOp(ASTNode *l, ASTNode *r, char *op)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_BINOP;
    n->left = l;
    n->right = r;
    n->op = strdup(op);
    return n;
}
ASTNode *newAssign(char *id, ASTNode *expr)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_ASSIGN;
    n->id = strdup(id);
    n->left = expr;
    return n;
}
ASTNode *newReturn(ASTNode *expr)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_RETURN;
    n->left = expr;
    return n;
}
ASTNode *newFunction(char *id, ASTNode *body)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_FUNCTION;
    n->id = strdup(id);
    n->left = body;
    return n;
}
ASTNode *newBlock(ASTNode *stmts)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_BLOCK;
    n->left = stmts;
    return n;
}
ASTNode *makeStmtList(ASTNode *stmt)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_STMTLIST;
    n->next = stmt;
    return n;
}
ASTNode *appendStmtList(ASTNode *list, ASTNode *stmt)
{
    if (!list)
        return makeStmtList(stmt);
    ASTNode *cur = list;
    while (cur->next)
        cur = cur->next;
    cur->next = stmt;
    return list;
}

ASTNode *newIf(ASTNode *cond, ASTNode *thenBranch, ASTNode *elseBranch)
{
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_IF;
    node->left = cond;
    node->right = thenBranch;
    node->next = elseBranch;
    node->id = NULL;
    node->op = NULL;
    node->num = 0;
    return node;
}

ASTNode *newWhile(ASTNode *cond, ASTNode *body)
{
    ASTNode *node = calloc(1, sizeof(ASTNode));
    node->type = NODE_WHILE;
    node->left = cond;
    node->right = body;
    return node;
}

ASTNode *newFor(ASTNode *init, ASTNode *cond, ASTNode *step, ASTNode *body)
{
    ASTNode *node = calloc(1, sizeof(ASTNode));
    node->type = NODE_FOR;

    node->init = init;
    node->cond = cond;
    node->step = step;
    node->body = body;

    return node;
}

ASTNode *newString(char *value)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_STRING;
    n->str = strdup(value);  
    return n;
}


ASTNode *newBool(int value)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_BOOL;
    n->num = value;
    return n;
}

ASTNode *newVarDecl(char *id, Type type, ASTNode *expr)
{
    ASTNode *n = calloc(1, sizeof(ASTNode));
    n->type = NODE_VARDECL;
    n->id = strdup(id);
    n->varType = type;
    n->left = expr;
    return n;
}

void printAST(ASTNode *node, int level)
{
    if (!node)
        return;
    switch (node->type)
    {
    case NODE_NUM:
        printf("%sNUM(%d)\n", indent(level), node->num);
        break;
    case NODE_ID:
        printf("%sID(%s)\n", indent(level), node->id);
        break;
    case NODE_BINOP:
        printf("%sBINOP(%s)\n", indent(level), node->op);
        printAST(node->left, level + 2);
        printAST(node->right, level + 2);
        break;
    case NODE_ASSIGN:
        printf("%sASSIGN(%s)\n", indent(level), node->id);
        printAST(node->left, level + 2);
        break;
    case NODE_RETURN:
        printf("%sRETURN\n", indent(level));
        printAST(node->left, level + 2);
        break;
    case NODE_FUNCTION:
        printf("%sFUNCTION %s\n", indent(level), node->id);
        printAST(node->left, level + 2);
        break;
    case NODE_BLOCK:
        printf("%sBLOCK\n", indent(level));
        printAST(node->left, level + 2);
        break;
    case NODE_STMTLIST:
        printf("%sSTMTLIST\n", indent(level));
        {
            ASTNode *cur = node->next;
            while (cur)
            {
                printAST(cur, level + 2);
                cur = cur->next;
            }
        }
        break;
    case NODE_IF:
        printf("%sIF\n", indent(level));
        printf("%sCondition:\n", indent(level + 2));
        printAST(node->left, level + 4);
        printf("%sThen:\n", indent(level + 2));
        printAST(node->right, level + 4);
        if (node->next)
        {
            printf("%sElse:\n", indent(level + 2));
            printAST(node->next, level + 4);
        }
        break;
    case NODE_WHILE:
        printf("%sWHILE\n", indent(level));
        printf("%sCondition:\n", indent(level + 2));
        printAST(node->left, level + 4);
        printf("%sBody:\n", indent(level + 2));
        printAST(node->right, level + 4);
        break;
    case NODE_FOR:
        printf("%sFOR\n", indent(level));

        printf("%sInit:\n", indent(level + 2));
        printAST(node->init, level + 4);

        printf("%sCondition:\n", indent(level + 2));
        printAST(node->cond, level + 4);

        printf("%sStep:\n", indent(level + 2));
        printAST(node->step, level + 4);

        printf("%sBody:\n", indent(level + 2));
        printAST(node->body, level + 4);
        break;
    case NODE_STRING:
        printf("%sSTRING(%s)\n", indent(level), node->id);
        break;
    case NODE_BOOL:
        printf("%sBOOL(%s)\n", indent(level), node->num ? "true" : "false");
        break;
    case NODE_VARDECL:
        printf("%sVARDECL %s : ", indent(level), node->id);
        if (node->varType == TYPE_NUMBER)
            printf("NUMBER\n");
        else if (node->varType == TYPE_STRING)
            printf("STRING\n");
        else if (node->varType == TYPE_BOOL)
            printf("BOOL\n");
        else
            printf("UNKNOWN\n");
        printAST(node->left, level + 2);
        break;

    default:
        printf("%sUNKNOWN\n", indent(level));
        break;
    }
}
