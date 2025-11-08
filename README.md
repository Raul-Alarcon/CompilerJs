# CompilerJs
## Estructura de Carpetas
```text
compilador-js-c/
├── src/                    # Código fuente principal
│   ├── lexer/              # Módulo de Análisis Léxico
│   ├── parser/             # Módulo de Análisis Sintáctico
│   ├── ast/                # Definiciones del Árbol de Sintaxis Abstracta
│   │   ├── ast.h           # Estructuras de nodos AST
│   │   └── ast.c           # Funciones: crear, imprimir, liberar
│   ├── codegen/            # Generación de código
│   ├── runtime/            # Código de Soporte, Máquina Virtual y Ejecución
│   ├── semantic/           # Análisis semántico
│   │   ├── symbol_table.c
│   │   └── symbol_table.h  # Tabla de símbolos (hash + ámbito)
│   └── util/               # Funciones de utilidad (ej. gestión de memoria)
├── include/                # Archivos de cabecera (.h) públicos 
├── examples/               # Programas de prueba en JS
├── scripts/                # Scripts útiles
├── Makefile                # Script para automatizar la compilación
└── main.c                  # Punto de entrada del programa


## Run Locally  
Clone the project  

```bash  
  git clone https://github.com/Raul-Alarcon/CompilerJs.git
```

Go to the project directory  

```bash  
  cd CompilerJs
```

Build  

```bash  
make
```

Start 

```bash  
./scripts/run.sh < examples/hello.js
```

Build Clean  

```bash  
make clean
```