#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

Symbol* symbol_table[TABLE_SIZE];
static int current_scope = 0;

static unsigned int hash(const char* s) {
    unsigned int h = 0;
    while(*s) h = (h<<5) + h + (unsigned char)(*s++);
    return h % TABLE_SIZE;
}

void insert_symbol(const char* name, Type type) {
    unsigned int h = hash(name);
    Symbol* s = calloc(1,sizeof(Symbol));
    s->name = strdup(name);
    s->type = type;
    s->scope = current_scope;
    s->next = symbol_table[h];
    symbol_table[h] = s;
}

Symbol* lookup_symbol(const char* name) {
    unsigned int h = hash(name);
    Symbol* s = symbol_table[h];
    while(s) {
        if (strcmp(s->name, name)==0) return s;
        s = s->next;
    }
    return NULL;
}

void enter_scope() { current_scope++; }
void exit_scope() { if(current_scope>0) current_scope--; }
