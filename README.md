# CompilerJs
## Estructura de Carpetas
```text
compilador-js-c/
├── src/                  # Código fuente principal
│   ├── lexer/            # Módulo de Análisis Léxico
│   ├── parser/           # Módulo de Análisis Sintáctico
│   ├── ast/              # Definiciones del Árbol de Sintaxis Abstracta
│   ├── runtime/          # Código de Soporte, Máquina Virtual y Ejecución
│   └── util/             # Funciones de utilidad (ej. gestión de memoria)
├── include/              # Archivos de cabecera (.h) públicos
├── tests/                # Archivos de prueba (código JS que compilarás)
├── bin/                  # Salida del ejecutable
├── build/                # Archivos temporales de compilación
├── Makefile              # Script para automatizar la compilación
└── main.c                # Punto de entrada del programa