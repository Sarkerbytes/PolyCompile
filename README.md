# PolyCompiler

**A Professional Multi-Language Educational Compiler**  
Supports **C**, **C++**, and **Java** subsets with a complete 6-phase compilation pipeline.

---

## Architecture

```
PolyCompiler (CLI)
       │
Language Detector (.c / .cpp / .java)
       │
 ┌─────┴──────────────────────────────────┐
 ▼              ▼                          ▼
C Frontend    C++ Frontend          Java Frontend
 Lexer_C       Lexer_CPP             Lexer_Java
 Parser_C      Parser_CPP            Parser_Java
 Semantic_C    Semantic_CPP          Semantic_Java
 AST_C         AST_CPP               AST_Java
 SymbolTable_C SymbolTable_CPP       SymbolTable_Java
 └─────────────────────┬───────────────────┘
                       ▼
              Common Compiler Core
   ┌──────────────────────────────────────────┐
   │ IRGenerator  → Three Address Code (TAC)  │
   │ Optimizer    → 5 Optimization Passes     │
   │ CodeGenerator→ Educational Assembly      │
   │ Executor     → Virtual Program Runtime   │
   │ DiagnosticEngine, FileReader, Logger     │
   └──────────────────────────────────────────┘
```

---

## Features

### Multi-Language Frontends
| Feature | C | C++ | Java |
|---------|---|-----|------|
| Lexical Analysis | ✓ | ✓ | ✓ |
| Recursive Descent Parser | ✓ | ✓ | ✓ |
| Scoped Symbol Table | ✓ | ✓ | ✓ |
| Semantic Analysis | ✓ | ✓ | ✓ |
| AST Generation | ✓ | ✓ | ✓ |

### Supported Language Constructs
**C:**  `#include <stdio.h>`, `printf`, `scanf`, `int/float/char/double/bool/void`, `if/else`, `while`, `do-while`, `for`, `switch/case`, `break/continue`, `return`, functions

**C++:** `#include <iostream>`, `using namespace std`, `cout <<`, `cin >>`, `string`, `bool`, all control structures, functions

**Java:** `public class`, `public static void main`, `Scanner`, `System.out.println`, `System.out.print`, all control structures, methods

### 6-Phase Compilation Pipeline
1. **Lexical Analysis** — Tokenizes source into typed lexemes with line/col info
2. **Syntax Analysis** — Recursive-descent parser builds a full AST
3. **Semantic Analysis** — Type checking, symbol resolution, scope validation
4. **IR Generation** — Three Address Code (TAC) intermediate representation
5. **Optimization** — 5 optimization passes on TAC
6. **Code Generation** — Educational target assembly output

### 5 Optimization Passes
1. **Constant Folding** — `t1 = 5 + 3` → `t1 = 8`
2. **Constant Propagation** — `x = 10; y = x + 2` → `y = 12`
3. **Copy Propagation** — `x = y; z = x + 1` → `z = y + 1`
4. **Algebraic Simplification** — `x * 1` → `x`, `x + 0` → `x`, `x * 0` → `0`
5. **Dead Code Elimination** — Removes unused temporaries and dead instructions

### Target Educational Assembly Instructions
`MOV`, `LOAD`, `STORE`, `ADD`, `SUB`, `MUL`, `DIV`, `CMP`, `JMP`, `JMP_EQ`, `JMP_NE`, `PUSH`, `CALL`, `RET`, `READ`, `PRINT`

---

## Build Instructions

### Prerequisites
- g++ (GCC 6+) — available via MinGW on Windows
- GNU make

### Build

```bash
# Windows (MinGW)
mingw32-make

# Linux / macOS
make
```

This creates the `polycompile` (or `polycompile.exe` on Windows) binary.

---

## Usage

```
polycompile [flags] <source_file>
```

### Flags

| Flag | Description |
|------|-------------|
| *(none)* | Compile and execute the program |
| `--debug` | Verbose 6-phase report + program output |
| `--tokens` | Display token table |
| `--ast` | Display Abstract Syntax Tree dump |
| `--symbol-table` | Display Symbol Table |
| `--tac` | Display Three Address Code |
| `--opt` | Display Optimized TAC |
| `--asm` | Display target educational assembly |
| `--help` | Show usage help |

### Examples

```bash
# Normal execution
polycompile examples/hello.c
polycompile examples/hello.cpp
polycompile examples/Hello.java

# Debug mode (6-phase verbose output + execution)
polycompile --debug examples/hello.c
polycompile --debug examples/Hello.java

# Inspect tokens
polycompile --tokens examples/hello.cpp

# Inspect AST
polycompile --ast examples/Hello.java

# Inspect symbol table
polycompile --symbol-table examples/hello.c

# Inspect TAC
polycompile --tac examples/hello.cpp

# Inspect Optimized TAC
polycompile --opt examples/hello.c

# Inspect generated assembly
polycompile --asm examples/Hello.java

# Combine flags
polycompile --tokens --ast --tac examples/hello.c
polycompile --debug --tokens --asm examples/hello.cpp
```

---

## Output Files

All outputs are written to the `output/` directory:

| File | Contents |
|------|----------|
| `output/tokens.txt` | Full token table (type, lexeme, line, col) |
| `output/ast.txt` | Pretty-printed Abstract Syntax Tree |
| `output/symbol_table.txt` | Symbol table with scopes and types |
| `output/semantic_report.txt` | Semantic analysis events and errors |
| `output/tac.txt` | Three Address Code intermediate representation |
| `output/optimized_tac.txt` | TAC after all optimization passes |
| `output/target_code.asm` | Educational assembly code |

---

## Project Structure

```
PolyCompile/
├── main.cpp                         ← CLI entry point
├── Makefile                         ← Build system
├── README.md                        ← This file
├── LICENSE                          ← MIT License
│
├── compiler/
│   ├── common/
│   │   ├── Token/
│   │   │   └── Token.hpp            ← TokenType enum + Token struct
│   │   ├── Utilities/
│   │   │   ├── ASTBase.hpp          ← Shared AST node hierarchy
│   │   │   ├── DiagnosticEngine.hpp ← Centralized error reporting
│   │   │   └── FileReader.hpp       ← Source file reader
│   │   ├── LanguageDetector/
│   │   │   └── LanguageDetector.hpp ← Extension-based language detection
│   │   ├── IR/
│   │   │   ├── IRGenerator.hpp/.cpp ← TAC generation from AST
│   │   ├── Optimizer/
│   │   │   ├── Optimizer.hpp/.cpp   ← 5-pass TAC optimizer
│   │   ├── CodeGen/
│   │   │   ├── CodeGenerator.hpp/.cpp ← Assembly code generator
│   │   └── Executor/
│   │       ├── Executor.hpp/.cpp    ← Virtual runtime executor
│   │
│   ├── c/                           ← C Frontend
│   │   ├── lexer/lexer_c.l          ← Flex Lexer specification
│   │   ├── parser/parser_c.y        ← Bison Parser specification
│   │   ├── semantic/Semantic_C.hpp/.cpp
│   │   ├── symbol_table/SymbolTable_C.hpp
│   │   ├── ast/AST_C.hpp
│   │   └── frontend/Frontend_C.hpp/.cpp
│   │
│   ├── cpp/                         ← C++ Frontend
│   │   ├── lexer/lexer_cpp.l        ← Flex Lexer specification
│   │   ├── parser/parser_cpp.y      ← Bison Parser specification
│   │   ├── semantic/Semantic_CPP.hpp/.cpp
│   │   ├── symbol_table/SymbolTable_CPP.hpp
│   │   ├── ast/AST_CPP.hpp
│   │   └── frontend/Frontend_CPP.hpp/.cpp
│   │
│   └── java/                        ← Java Frontend
│       ├── lexer/lexer_java.l       ← Flex Lexer specification
│       ├── parser/parser_java.y     ← Bison Parser specification
│       ├── semantic/Semantic_Java.hpp/.cpp
│       ├── symbol_table/SymbolTable_Java.hpp
│       ├── ast/AST_Java.hpp
│       └── frontend/Frontend_Java.hpp/.cpp
│
├── examples/
│   ├── hello.c / for.c / while.c / switch.c / ifelse.c / add.c
│   ├── hello.cpp / for.cpp / while.cpp / switch.cpp / ifelse.cpp / arithmetic.cpp
│   └── Hello.java / ForLoop.java / WhileLoop.java / SwitchCase.java / IfElse.java / Arithmetic.java
│
└── output/            ← Generated at runtime
    ├── tokens.txt
    ├── ast.txt
    ├── symbol_table.txt
    ├── semantic_report.txt
    ├── tac.txt
    ├── optimized_tac.txt
    └── target_code.asm
```

---

## Run Commands Quick Reference

### 1. Build Commands
```powershell
# Build everything (main polycompile executable + all Flex/Bison test executables)
make all

# Build individual targets:
make win               # Build polycompile.exe
make fb-all            # Build all Flex/Bison test executables (test_c.exe, test_cpp.exe, test_java.exe)
make clean             # Clean object files and executables
```

### 2. Standalone Flex/Bison Parsers (Lab Deliverables)
```powershell
# C Flex/Bison Parser
.\test_c.exe examples/for.c
.\test_c.exe examples/switch.c

# C++ Flex/Bison Parser
.\test_cpp.exe examples/for.cpp
.\test_cpp.exe examples/switch.cpp
.\test_cpp.exe examples/arithmetic.cpp

# Java Flex/Bison Parser
.\test_java.exe examples/ForLoop.java
.\test_java.exe examples/SwitchCase.java
.\test_java.exe examples/Arithmetic.java
```

### 3. PolyCompiler — Normal Mode
```powershell
# C Examples
.\polycompile.exe examples/for.c
.\polycompile.exe examples/switch.c
.\polycompile.exe examples/while.c

# C++ Examples
.\polycompile.exe examples/for.cpp
.\polycompile.exe examples/switch.cpp
.\polycompile.exe examples/arithmetic.cpp

# Java Examples
.\polycompile.exe examples/ForLoop.java
.\polycompile.exe examples/SwitchCase.java
.\polycompile.exe examples/Arithmetic.java
```

### 4. PolyCompiler — Debug Mode (Tokens, AST, Symbol Table, TAC, ASM)
```powershell
# C (Debug)
.\polycompile.exe --debug examples/for.c
.\polycompile.exe --debug examples/switch.c

# C++ (Debug)
.\polycompile.exe --debug examples/for.cpp
.\polycompile.exe --debug examples/switch.cpp

# Java (Debug)
.\polycompile.exe --debug examples/ForLoop.java
.\polycompile.exe --debug examples/SwitchCase.java
```

---

## License

MIT License — see [LICENSE](LICENSE)
