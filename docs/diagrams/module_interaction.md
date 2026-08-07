# Module Interaction Diagram

```mermaid
graph TD
    main["main.cpp\nCLI Entry Point\n--debug, --tokens, --ast,\n--tac, --opt, --asm, --symbol-table"] --> LD["LanguageDetector\nExtension-based .c/.cpp/.java"]

    LD -->|.c| FC["Frontend_C\nOrchestrates C pipeline"]
    LD -->|.cpp| FCPP["Frontend_CPP\nOrchestrates C++ pipeline"]
    LD -->|.java| FJ["Frontend_Java\nOrchestrates Java pipeline"]

    FC --> LEXA["Lexer_C\nlexer_c.l (Flex)\nProduces Token stream"]
    FC --> PARS["Parser_C\nparser_c.y (Bison) + Recursive Descent\nProduces ASTNodePtr"]
    FC --> SEMA["Semantic_C\nSemantic_C.cpp\nAST traversal, scope checking"]

    FCPP --> LEXB["Lexer_CPP\nlexer_cpp.l (Flex)\nIncludes stream operators << >>"]
    FCPP --> PARB["Parser_CPP\nparser_cpp.y (Bison) + Recursive Descent\nHandles cout/cin grammar"]
    FCPP --> SEMB["Semantic_CPP\nSemantic_CPP.cpp"]

    FJ --> LEXC["Lexer_Java\nlexer_java.l (Flex)\nJava-specific keywords"]
    FJ --> PARC["Parser_Java\nparser_java.y (Bison) + Recursive Descent\nClass structure grammar"]
    FJ --> SEMC["Semantic_Java\nSemantic_Java.cpp"]

    SEMA -->|"declare/lookup"| SYMC["SymbolTable_C\nStack of std::map scopes"]
    SEMB -->|"declare/lookup"| SYMCPP["SymbolTable_CPP\nStack of std::map scopes"]
    SEMC -->|"declare/lookup"| SYMJ["SymbolTable_Java\nStack of std::map scopes"]

    SEMA -->|"logError()"| DIAG["DiagnosticEngine\nStatic error registry\nLexical/Syntax/Semantic errors"]
    SEMB -->|"logError()"| DIAG
    SEMC -->|"logError()"| DIAG

    PARS -->|"ASTNodePtr"| AST["ASTBase Nodes\nASTBase.hpp\nProgramNode, FunctionNode,\nBlockNode, IfNode, ForNode,\nBinaryExprNode, etc."]
    PARB -->|"ASTNodePtr"| AST
    PARC -->|"ASTNodePtr"| AST

    AST -->|"root"| IRG["IRGenerator\nIRGenerator.cpp\nAST → TACInstruction list\ntemps: t0,t1...; labels: L0,L1..."]

    IRG -->|"std::vector<TACInstruction>"| OPT["Optimizer\nOptimizer.cpp\n5 passes sequentially"]

    OPT -->|"Optimized TAC"| CG["CodeGenerator\nCodeGenerator.cpp\nTAC → Educational Assembly\nLOAD/STORE/ADD/SUB/CMP/JMP/PRINT"]

    OPT -->|"Optimized TAC"| EX["Executor\nExecutor.cpp\nVirtual Runtime Engine\nstd::map<string,string> memory"]

    EX -->|"stdout"| OUT["Program Output"]

    CG -->|"save"| ASMF["output/target_code.asm"]
    IRG -->|"save"| TACF["output/tac.txt"]
    OPT -->|"save"| OTACF["output/optimized_tac.txt"]
    SYMC -->|"save"| SYMF["output/symbol_table.txt"]
    DIAG -->|"save"| REPF["output/semantic_report.txt"]
    AST -->|"save via AST_C"| ASTF["output/ast.txt"]
    LEXA -->|"save"| TOKF["output/tokens.txt"]
```

## Key Interfaces

| Interface | Type | Connects |
|-----------|------|---------|
| `ASTNodePtr` | `shared_ptr<ASTNode>` | Parser → Semantic Analyzer, Parser → IR Generator |
| `std::vector<Token>` | Token list | Lexer → Parser |
| `std::vector<TACInstruction>` | TAC list | IR Generator → Optimizer → CodeGenerator / Executor |
| `std::vector<std::string>` | Assembly lines | CodeGenerator → output file |
| `SymbolTable_*::lookup()` | `SymbolX*` | Semantic → Symbol Table |
| `DiagnosticEngine::logSemanticError()` | `void` | Any phase → Error registry |
