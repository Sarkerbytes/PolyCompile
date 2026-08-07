# Supporting Design Documents — PolyCompile

---

## 1. Design Decisions and Rationale

### 1.1 Unified AST Across All Languages

**Decision:** All three language frontends produce nodes from a single `ASTBase.hpp` hierarchy.

**Rationale:** This enables the backend pipeline (IR Generator, Optimizer, Code Generator, Executor) to be completely language-agnostic. New language frontends can be added without touching any backend code.

**Trade-off:** The unified node set is the intersection of all three languages' constructs. Language-specific AST subtleties (e.g., Java class hierarchies, C++ templates) cannot be represented without extending the base types.

---

### 1.2 Dual-Frontend Architecture

**Decision:** Bison parsers are provided as standalone deliverables (`test_*.exe`) separate from the main compiler pipeline's recursive-descent parsers.

**Rationale:** Lab deliverables require Flex/Bison parsers. The main compiler uses recursive-descent parsers because they are easier to modify for AST construction and produce better error messages.

**Trade-off:** Maintaining two parsing implementations for each language creates potential inconsistency if grammar rules diverge.

---

### 1.3 `shared_ptr<ASTNode>` for All Tree Nodes

**Decision:** `ASTNodePtr = std::shared_ptr<ASTNode>` is used everywhere.

**Rationale:** AST nodes are shared across phases (parser → semantic → IR → optimizer). Reference counting through `shared_ptr` ensures correct lifetime without manual memory management.

**Trade-off:** `shared_ptr` has higher memory overhead and slightly slower performance than raw pointers. For the educational scale of this compiler, this is acceptable.

---

### 1.4 Static Optimizer and CodeGenerator Methods

**Decision:** `Optimizer::optimize()` and `CodeGenerator::generateAssembly()` are static methods.

**Rationale:** These operations are purely functional transformations of instruction lists with no persistent state. Static methods make the data flow explicit: input list → output list.

---

### 1.5 DiagnosticEngine as a Static Singleton

**Decision:** All error logging goes through a single static `DiagnosticEngine`.

**Rationale:** Eliminates the need to thread error lists through every function call. Any component (lexer, parser, semantic analyzer) can report errors without coupling to a specific error-handling strategy.

**Trade-off:** Global state is harder to reason about in multi-threaded contexts (not a concern for this single-threaded compiler).

---

### 1.6 Five Optimizer Passes Applied Sequentially

**Decision:** Optimization passes are applied in a fixed order: Constant Folding → Constant Propagation → Copy Propagation → Algebraic Simplification → Dead Code Elimination.

**Rationale:** Each pass creates opportunities for subsequent passes. Constant Folding reduces operations to literals, enabling Constant Propagation to replace variables, enabling Dead Code Elimination to remove now-unreferenced temporaries.

---

### 1.7 Educational Assembly (Not Real x86)

**Decision:** The CodeGenerator emits educational assembly using simplified mnemonics (`LOAD`, `STORE`, `ADD`, `CMP`, `JMP`, `PRINT`, etc.) rather than real x86-64 or ARM assembly.

**Rationale:** The goal is educational demonstration of code generation concepts, not a production compiler. Real assembly would require register allocation, calling conventions, and ABI compliance — beyond the scope of this project.

---

## 2. Assumptions

1. **Single-file programs:** Each invocation processes exactly one source file. Multi-file compilation and linking are Not Implemented.

2. **`main()` as entry point:** All programs are assumed to start execution from a function named `main`.

3. **No recursive function calls:** The Virtual Executor does not implement a proper call stack. Recursive user-defined function calls will produce incorrect results.

4. **Integer arithmetic in optimizer:** The constant folding and algebraic simplification passes only handle integer constants. Floating-point constant folding is Not Implemented.

5. **Labels and temporaries are globally unique:** Temp names (`t0`, `t1`, ...) and label names (`L0`, `L1`, ...) are generated with a monotonically incrementing counter reset per compilation unit.

6. **Lexer and parser are sequential:** The C++ frontend lexer runs first and populates the token list, then the parser processes the token list. Incremental parsing is Not Implemented.

---

## 3. Limitations

### 3.1 Language Feature Limitations

| Feature | Status |
|---------|--------|
| Pointer types (`int*`, `char*`) | Not Implemented |
| Reference types (`int&`) | Not Implemented |
| `struct` / `union` | Not Implemented |
| Arrays (beyond basic declaration recognition) | Not Implemented |
| Multi-dimensional arrays | Not Implemented |
| Dynamic memory (`malloc`, `free`, `new`, `delete`) | Not Implemented |
| Exception handling (`try`/`catch`/`throw`) | Not Implemented |
| Class inheritance and polymorphism | Not Implemented |
| Virtual functions and vtable dispatch | Not Implemented |
| Access modifiers (`public`/`private`/`protected`) | Lexically tokenized; Not semantically enforced |
| Generics / templates | Not Implemented |
| Macro expansion (`#define`) | Directives skipped; macros not expanded |
| Forward declarations (beyond function forward decl) | Not Implemented |
| `printf` format string parsing | Format strings are treated as opaque string literals |

### 3.2 Semantic Analysis Limitations

| Check | Status |
|-------|--------|
| Type compatibility checking | Not Implemented |
| Return type matching | Not Implemented |
| Argument count / type at call sites | Not Implemented |
| `break` / `continue` outside loop | Not Implemented |
| Uninitialized variable detection | Not Implemented |
| Const correctness | Not Implemented |

### 3.3 Code Generation Limitations

| Issue | Notes |
|-------|-------|
| Register allocation | Only `R1` and `R2` are used; no true register allocation |
| Complex nested control flow TAC | Simplified; may not correctly emit TAC for deep nesting |
| Floating-point instructions | Not separately handled in CodeGenerator |
| String concatenation (Java/C++) | Not Implemented |

---

## 4. Future Enhancements

### 4.1 Compiler Pipeline Enhancements

1. **Complete Recursive Function Call Support:** Add a proper call stack in the Executor to support user-defined recursive functions.

2. **Floating-Point Constant Folding:** Extend the Optimizer to handle `float` and `double` constant evaluation.

3. **Type Checking Pass:** Implement a full type inference and compatibility checking pass that verifies assignment compatibility, operator type rules, and return type matching.

4. **Array Support:** Extend the AST, IR, and Executor to handle single-dimensional and multi-dimensional arrays with proper bounds tracking.

5. **`#define` Macro Expansion:** Add a preprocessor phase before lexing that expands `#define` macros.

### 4.2 Backend Enhancements

6. **Native x86-64 Code Generation:** Replace or augment the educational assembly generator with a real x86-64 or LLVM IR code emitter.

7. **Register Allocation Algorithm:** Implement graph-coloring or linear-scan register allocation in the code generator.

8. **Basic Block CFG Construction:** Restructure the TAC list into a Control Flow Graph (CFG) of basic blocks to enable more powerful dataflow-based optimizations (reaching definitions, live variable analysis).

### 4.3 IDE and Tooling Enhancements

9. **Inline Error Highlighting in Web IDE:** Integrate Monaco Editor's marker API to underline syntax and semantic errors with red squiggles at their source location.

10. **Automated Test Harness:** Create a CI test framework that runs all example programs and compares token, AST, TAC, and output against golden reference files.

11. **Incremental Compilation:** Cache previously compiled modules and only recompile changed portions.

---

## 5. Technology Stack Summary

| Component | Technology | Version |
|-----------|-----------|---------|
| Core compiler | C++ | C++11/C++14 |
| Lexer generator | Flex | ≥ 2.6 |
| Parser generator | Bison | ≥ 3.0 |
| Build system | GNU Make + g++ / MinGW | — |
| Web IDE backend | Node.js + Express.js | — |
| Web IDE frontend | HTML5, CSS3, Vanilla JS + Monaco Editor | — |
| Containerization | Docker | — |

---

## 6. Project Conventions

| Convention | Standard |
|-----------|---------|
| C++ standard | C++11 with some C++14 features |
| Header guards | `#ifndef / #define / #endif` |
| Smart pointers | `std::shared_ptr` for all AST nodes |
| Naming | `PascalCase` for classes, `camelCase` for methods, `snake_case` for local variables |
| Error output | All error messages go to `stderr` via `DiagnosticEngine` |
| Output artifacts | All compiler-generated files go to `output/` directory |
| Token naming | `KEYWORD_*`, `CONST_*`, `OP_*` prefixes distinguish token categories |
