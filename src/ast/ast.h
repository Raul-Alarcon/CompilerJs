#ifndef AST_H
#define AST_H

typedef enum { NODE_NUM, NODE_ID, NODE_BINOP, NODE_ASSIGN, NODE_RETURN, NODE_FUNCTION, NODE_BLOCK, NODE_STMTLIST } NodeType;

typedef struct ASTNode {
    NodeType type;
    char *id;
    int num;
    char *op;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next; /* for lists */
} ASTNode;

/* constructors */
ASTNode* newNum(int val);
ASTNode* newId(char* name);
ASTNode* newBinOp(ASTNode* l, ASTNode* r, char* op);
ASTNode* newAssign(char* id, ASTNode* expr);
ASTNode* newReturn(ASTNode* expr);
ASTNode* newFunction(char* id, ASTNode* body);
ASTNode* newBlock(ASTNode* stmts);
ASTNode* makeStmtList(ASTNode* stmt);
ASTNode* appendStmtList(ASTNode* list, ASTNode* stmt);

void printAST(ASTNode* node, int level);

#endif
