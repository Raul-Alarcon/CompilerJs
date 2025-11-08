# === Configuración ===
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Iinclude -I./src/ast -I./src/semantic -I./build -Wall -g
BUILD = build

# === Fuentes y objetos ===
OBJS = $(BUILD)/lex.yy.o $(BUILD)/y.tab.o $(BUILD)/main.o \
       $(BUILD)/ast.o $(BUILD)/symbol_table.o $(BUILD)/codegen.o

# === Regla principal ===
all: $(BUILD)/compiler

# === Crear carpeta build si no existe ===
$(BUILD):
	mkdir -p $(BUILD)

# === Generar lexer ===
$(BUILD)/lex.yy.c: src/lexer/js_lexer.l | $(BUILD)
	$(FLEX) -o $@ $<

# === Generar parser (Bison) ===
$(BUILD)/y.tab.c $(BUILD)/y.tab.h: src/parser/js_parser.y | $(BUILD)
	$(BISON) -d -o $(BUILD)/y.tab.c src/parser/js_parser.y --defines=$(BUILD)/y.tab.h


# === Compilaciones individuales ===
$(BUILD)/lex.yy.o: $(BUILD)/lex.yy.c $(BUILD)/y.tab.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/y.tab.o: $(BUILD)/y.tab.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/ast.o: src/ast/ast.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/symbol_table.o: src/semantic/symbol_table.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/codegen.o: src/codegen/codegen.c
	$(CC) $(CFLAGS) -c $< -o $@

# === Enlace final ===
$(BUILD)/compiler: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lfl

# === Limpiar ===
clean:
	rm -rf $(BUILD) *.o

.PHONY: all clean
