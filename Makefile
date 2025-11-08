CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Iinclude -I./src/ast -I./src/semantic -Wall -g
BUILD = build

SRCDIRS = src/lexer src/parser src/ast src/semantic src/codegen

OBJS = $(BUILD)/lex.yy.o $(BUILD)/y.tab.o $(BUILD)/main.o $(BUILD)/ast.o $(BUILD)/symbol_table.o $(BUILD)/codegen.o

all: $(BUILD)/compiler

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/lex.yy.c: src/lexer/js_lexer.l | $(BUILD)
	$(FLEX) -o $@ src/lexer/js_lexer.l

$(BUILD)/y.tab.c $(BUILD)/y.tab.h: src/parser/js_parser.y | $(BUILD)
	$(BISON) -d -o $(BUILD)/y.tab.c src/parser/js_parser.y
	@mv y.tab.h $(BUILD)/y.tab.h || true

# compile flex/bison outputs and .c files
$(BUILD)/lex.yy.o: $(BUILD)/lex.yy.c $(BUILD)/y.tab.h
	$(CC) $(CFLAGS) -c $(BUILD)/lex.yy.c -o $@

$(BUILD)/y.tab.o: $(BUILD)/y.tab.c
	$(CC) $(CFLAGS) -c $(BUILD)/y.tab.c -o $@

$(BUILD)/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o $@

$(BUILD)/ast.o: src/ast/ast.c
	$(CC) $(CFLAGS) -c src/ast/ast.c -o $@

$(BUILD)/symbol_table.o: src/semantic/symbol_table.c
	$(CC) $(CFLAGS) -c src/semantic/symbol_table.c -o $@

$(BUILD)/codegen.o: src/codegen/codegen.c
	$(CC) $(CFLAGS) -c src/codegen/codegen.c -o $@

$(BUILD)/compiler: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lfl

clean:
	rm -rf $(BUILD) *.o

.PHONY: all clean
