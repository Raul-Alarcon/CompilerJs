#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"

static int temp = 0;
static int labelCount = 0;

char *newLabel()
{
    char *label = (char *)malloc(16);
    sprintf(label, "L%d", labelCount++);
    return label;
}
int newTemp() { return temp++; }

static void emit_string_literal(const char *s, int t)
{
    printf("t%d = \"%s\"\n", t, s);
}

int generate_expr(ASTNode *node)
{
    switch (node->type)
    {

    case NODE_NUM:
    {
        int t = newTemp();
        printf("t%d = %d\n", t, node->num);
        return t;
    }

    case NODE_STRING:
    {
        int t = newTemp();
        emit_string_literal(node->str ? node->str : "", t);
        return t;
    }
    case NODE_BOOL:
    {
        int t = newTemp();
        printf("t%d = %d\n", t, node->num ? 1 : 0); // true -> 1, false -> 0
        return t;
    }

    case NODE_BINOP:
    {
        int l = generate_expr(node->left);
        int r = generate_expr(node->right);
        int t = newTemp();

        // Heurística simple: si alguno de los operandos es string literal or node type STRING,
        // emitimos CONCAT si op == "+"
        int leftIsString = (node->left && node->left->type == NODE_STRING);
        int rightIsString = (node->right && node->right->type == NODE_STRING);

        if ((leftIsString || rightIsString) && node->op && strcmp(node->op, "+") == 0)
        {
            printf("t%d = concat t%d t%d\n", t, l, r);
        }
        else
        {
            printf("t%d = t%d %s t%d\n", t, l, node->op ? node->op : "?", r);
        }
        return t;
    }

    case NODE_ID:
    {
        int t = newTemp();
        printf("t%d = %s\n", t, node->id);
        return t;
    }

        // case NODE_BINOP:
        // {
        //     int l = generate_expr(node->left);
        //     int r = generate_expr(node->right);
        //     int t = newTemp();
        //     printf("t%d = t%d %s t%d\n", t, l, node->op, r);
        //     return t;
        // }

    default:
        printf("ERROR: expresión inválida\n");
        exit(1);
    }
}

void generate_stmt(ASTNode *node)
{

    switch (node->type)
    {

    case NODE_VARDECL:
    { 
        const char *name = node->id ? node->id : "<anon>";
        const char *typename = "UNKNOWN";
        if (node->varType == TYPE_NUMBER)
            typename = "NUMBER";
        else if (node->varType == TYPE_STRING)
            typename = "STRING";
        else if (node->varType == TYPE_BOOL)
            typename = "BOOL";

        printf("DECLARE %s : %s\n", name, typename);
        if (node->left)
        {
            int t = generate_expr(node->left);
            printf("STORE %s <- t%d\n", name, t);
        }
        break;
    }
    case NODE_ASSIGN:
    {
        int t = generate_expr(node->left);
        printf("STORE %s <- t%d\n", node->id, t);
        break;
    }

    case NODE_RETURN:
    {
        int t = generate_expr(node->left);
        printf("RETURN t%d\n", t);
        break;
    }

    case NODE_IF:
    {
        char *Ltrue = newLabel();
        char *Lend = newLabel();

        int cond = generate_expr(node->left);

        printf("IF t%d GOTO %s\n", cond, Ltrue);
        printf("GOTO %s\n", Lend);

        printf("%s:\n", Ltrue);
        generate_stmt(node->right);

        printf("%s:\n", Lend);
        break;
    }

    case NODE_FOR:
    {
        char *Lstart = newLabel();
        char *Lbody = newLabel();
        char *Lstep = newLabel();
        char *Lend = newLabel();

        if (node->init)
            generate_stmt(node->init);

        printf("%s:\n", Lstart);

        if (node->cond)
        {
            int cond = generate_expr(node->cond);
            printf("IF t%d GOTO %s\n", cond, Lbody);
            printf("GOTO %s\n", Lend);
        }
        else
        {
            printf("GOTO %s\n", Lbody);
        }

        printf("%s:\n", Lbody);
        generate_stmt(node->body);

        printf("%s:\n", Lstep);
        generate_stmt(node->step);

        printf("GOTO %s\n", Lstart);
        printf("%s:\n", Lend);

        break;
    }

    case NODE_BLOCK:
        generate_stmt(node->left);
        break;

    case NODE_STMTLIST:
    {
        ASTNode *cur = node->next;
        while (cur)
        {
            generate_stmt(cur);
            cur = cur->next;
        }
        break;
    }

    case NODE_WHILE:
    {
        char *Lstart = newLabel();
        char *Lbody = newLabel();
        char *Lend = newLabel();

        printf("%s:\n", Lstart);

        int cond = generate_expr(node->left);
        printf("IF t%d GOTO %s\n", cond, Lbody);
        printf("GOTO %s\n", Lend);

        printf("%s:\n", Lbody);
        generate_stmt(node->right);

        printf("GOTO %s\n", Lstart);
        printf("%s:\n", Lend);

        break;
    }

    default:
        printf("ERROR stmt\n");
        exit(1);
    }
}

void generate_ir(ASTNode *root)
{
    generate_stmt(root);
}