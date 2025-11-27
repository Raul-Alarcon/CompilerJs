#ifndef AST_H
#define AST_H

#include "../semantic/symbol_table.h"
typedef enum
{
    NODE_NUM,
    NODE_STRING,
    NODE_BOOL,
    NODE_ID,
    NODE_BINOP,
    NODE_ASSIGN,
    NODE_RETURN,
    NODE_FUNCTION,
    NODE_BLOCK,
    NODE_STMTLIST,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_VARDECL
} NodeType;

typedef struct ASTNode
{
    NodeType type;
    char *id;
    int num;
    char *op;

    char *str;
    int varType;

    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;

    struct ASTNode *init;
    struct ASTNode *cond;
    struct ASTNode *step;
    struct ASTNode *body;
} ASTNode;

/* constructors */
ASTNode *newNum(int val);
ASTNode *newId(char *name);
ASTNode *newBinOp(ASTNode *l, ASTNode *r, char *op);
ASTNode *newAssign(char *id, ASTNode *expr);
ASTNode *newWhile(ASTNode *cond, ASTNode *body);
ASTNode *newFor(ASTNode *init, ASTNode *cond, ASTNode *step, ASTNode *body);
ASTNode *newReturn(ASTNode *expr);
ASTNode *newFunction(char *id, ASTNode *body);
ASTNode *newBlock(ASTNode *stmts);
ASTNode *makeStmtList(ASTNode *stmt);
ASTNode *appendStmtList(ASTNode *list, ASTNode *stmt);

ASTNode *newString(char *value);
ASTNode *newBool(int value);
ASTNode* newVarDecl(char* id, Type type, ASTNode* expr);

ASTNode *newIf(ASTNode *cond, ASTNode *thenBranch, ASTNode *elseBranch);

void printAST(ASTNode *node, int level);

#endif
