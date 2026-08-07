# Compiler Pipeline Diagram

```mermaid
flowchart TD
    A["Source File (.c / .cpp / .java)"] --> B[Language Detector]
    B --> C{Select Frontend}

    C -->|".c"| D1[C Frontend]
    C -->|".cpp"| D2["C++ Frontend"]
    C -->|".java"| D3[Java Frontend]

    D1 --> E1[C Lexer - Flex]
    D2 --> E2["C++ Lexer - Flex"]
    D3 --> E3[Java Lexer - Flex]

    E1 --> F1["C Parser - Bison/Recursive Descent"]
    E2 --> F2["C++ Parser - Bison/Recursive Descent"]
    E3 --> F3["Java Parser - Bison/Recursive Descent"]

    F1 --> G["Unified AST (ASTBase.hpp)"]
    F2 --> G
    F3 --> G

    G --> H[Semantic Analyzer]
    H --> I[Symbol Table]
    H --> J[DiagnosticEngine - Error Log]

    G --> K["IR Generator - Three-Address Code"]
    K --> L1["Pass 1: Constant Folding"]
    L1 --> L2[Pass 2: Constant Propagation]
    L2 --> L3[Pass 3: Copy Propagation]
    L3 --> L4[Pass 4: Algebraic Simplification]
    L4 --> L5[Pass 5: Dead Code Elimination]

    L5 --> M["Code Generator - Educational Assembly"]
    L5 --> N["Executor - Virtual Runtime Engine"]
    N --> O[Program Output to stdout]

    M --> P["output/target_code.asm"]
    K --> Q["output/tac.txt"]
    L5 --> R["output/optimized_tac.txt"]
    H --> S["output/symbol_table.txt"]
    H --> T["output/semantic_report.txt"]
    F1 --> U["output/ast.txt"]
    E1 --> V["output/tokens.txt"]
```

## Pipeline Phase Summary

| Phase | Input | Output | Key Component |
|-------|-------|--------|--------------|
| 1. Lexical Analysis | Source characters | Token stream | `lexer_*.l` (Flex) |
| 2. Syntax Analysis | Tokens | AST | `parser_*.y` (Bison) / Recursive Descent |
| 3. Semantic Analysis | AST | Symbol Table + Error List | `Semantic_*.cpp` |
| 4. IR Generation | AST | TAC instructions | `IRGenerator.cpp` |
| 5. Optimization | TAC | Optimized TAC | `Optimizer.cpp` |
| 6a. Code Generation | Optimized TAC | Educational Assembly | `CodeGenerator.cpp` |
| 6b. Execution | Optimized TAC | Program Output | `Executor.cpp` |
