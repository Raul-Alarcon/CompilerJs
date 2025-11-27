#ifndef AST_H
#define AST_H

typedef enum { NODE_NUM, NODE_ID, NODE_BINOP, NODE_ASSIGN, NODE_RETURN, NODE_FUNCTION, NODE_BLOCK, NODE_STMTLIST, NODE_IF, NODE_WHILE } NodeType;

typedef struct ASTNode {
    NodeType type;
    char *id;
    int num;
    char *op;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;  
} ASTNode;

/* constructors */
ASTNode* newNum(int val);
ASTNode* newId(char* name);
ASTNode* newBinOp(ASTNode* l, ASTNode* r, char* op);
ASTNode* newAssign(char* id, ASTNode* expr);
ASTNode* newWhile(ASTNode* cond, ASTNode* body);
ASTNode* newReturn(ASTNode* expr);
ASTNode* newFunction(char* id, ASTNode* body);
ASTNode* newBlock(ASTNode* stmts);
ASTNode* makeStmtList(ASTNode* stmt);
ASTNode* appendStmtList(ASTNode* list, ASTNode* stmt);

ASTNode* newIf(ASTNode* cond, ASTNode* thenBranch, ASTNode* elseBranch);

void printAST(ASTNode* node, int level);

#endif
