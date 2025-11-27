#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define TABLE_SIZE 100

typedef enum { TYPE_NUMBER, TYPE_STRING, TYPE_BOOL, TYPE_FUNCTION } Type;

typedef struct Symbol {
    char* name;
    Type type;
    int scope;
    struct Symbol* next;
} Symbol;

extern Symbol* symbol_table[TABLE_SIZE];

void insert_symbol(const char* name, Type type);
Symbol* lookup_symbol(const char* name); 
void enter_scope();
void exit_scope();

#endif
