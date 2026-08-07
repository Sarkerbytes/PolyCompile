# Semantic Analysis — PolyCompile

---

## 1. Overview

PolyCompile performs semantic analysis after the AST is built. Each language frontend has a dedicated semantic analyzer:

| Analyzer | Language | Files |
|----------|----------|-------|
| `Semantic_C` | C | `compiler/c/semantic/Semantic_C.hpp` / `.cpp` |
| `Semantic_CPP` | C++ | `compiler/cpp/semantic/Semantic_CPP.hpp` / `.cpp` |
| `Semantic_Java` | Java | `compiler/java/semantic/Semantic_Java.hpp` / `.cpp` |

All three share the same structure: they perform **AST tree traversal** using `checkNode(ASTNodePtr)` and interact with a language-specific `SymbolTable_*` and the shared `DiagnosticEngine`.

---

## 2. Semantic Rules Implemented

### 2.1 Duplicate Variable Declaration

**Rule:** A variable cannot be declared twice within the same scope.

**Implementation:**
```cpp
case ASTNodeType::VAR_DECL: {
    auto vd = std::dynamic_pointer_cast<VarDeclNode>(node);
    if (!symbolTable.declare(vd->varName, vd->varType)) {
        DiagnosticEngine::logSemanticError(filename, 0, 0,
            "Duplicate variable declaration: " + vd->varName);
    }
    break;
}
```

**Error message:** `[Semantic Error] source.c:0:0 - Duplicate variable declaration: x`

---

### 2.2 Undeclared Variable Usage

**Rule:** A variable must be declared before it is used in any expression.

**Implementation:**
```cpp
case ASTNodeType::VAR_EXPR: {
    auto var = std::dynamic_pointer_cast<VarExprNode>(node);
    SymbolC* sym = symbolTable.lookup(var->name);
    if (!sym) {
        DiagnosticEngine::logSemanticError(filename, 0, 0,
            "Undeclared variable: " + var->name);
    }
    break;
}
```

**Error message:** `[Semantic Error] source.c:0:0 - Undeclared variable: y`

---

### 2.3 Undeclared Variable Assignment

**Rule:** Assigning to a variable that has not been declared is an error.

**Implementation:**
```cpp
case ASTNodeType::ASSIGN_STMT: {
    auto ass = std::dynamic_pointer_cast<AssignNode>(node);
    SymbolC* sym = symbolTable.lookup(ass->varName);
    if (!sym) {
        DiagnosticEngine::logSemanticError(filename, 0, 0,
            "Undeclared variable assignment: " + ass->varName);
    }
    if (ass->expr) checkNode(ass->expr);
    break;
}
```

---

### 2.4 Duplicate Function Declaration

**Rule:** A function cannot be declared twice (unless it is a forward declaration being redefined with the same signature).

**Implementation:**
```cpp
case ASTNodeType::FUNCTION: {
    auto func = std::dynamic_pointer_cast<FunctionNode>(node);
    SymbolC* existing = symbolTable.lookup(func->name);
    if (existing && existing->isFunction && existing->type == func->returnType) {
        // Forward declaration redefinition — OK
    } else if (!symbolTable.declare(func->name, func->returnType, true, paramTypes)) {
        DiagnosticEngine::logSemanticError(filename, 0, 0,
            "Duplicate function declaration: " + func->name);
    }
    break;
}
```

---

### 2.5 Undeclared Function Call

**Rule:** A function must be declared before it can be called.

**Implementation:**
```cpp
case ASTNodeType::CALL_EXPR: {
    auto call = std::dynamic_pointer_cast<CallExprNode>(node);
    SymbolC* sym = symbolTable.lookup(call->funcName);
    if (!sym || !sym->isFunction) {
        DiagnosticEngine::logSemanticError(filename, 0, 0,
            "Undeclared function call: " + call->funcName);
    }
    for (const auto& arg : call->args) checkNode(arg);
    break;
}
```

---

### 2.6 Duplicate Parameter Names

**Rule:** Two parameters in the same function cannot have the same name.

**Implementation:**
```cpp
for (const auto& p : func->parameters) {
    if (!symbolTable.declare(p.name, p.type)) {
        DiagnosticEngine::logSemanticError(filename, 0, 0,
            "Duplicate parameter name: " + p.name);
    }
}
```

---

## 3. Semantic Rules NOT Implemented

The following semantic checks are **Not Implemented**:

| Check | Status |
|-------|--------|
| Type-compatibility checking (e.g., assigning `string` to `int`) | Not Implemented |
| Return type matching (e.g., `int` function returning `float`) | Not Implemented |
| Argument count/type matching at call sites | Not Implemented |
| `break` / `continue` outside loop/switch detection | Not Implemented |
| Array bounds checking | Not Implemented |
| Java `null` dereference detection | Not Implemented |

---

## 4. Type Checking

**Implemented:** Variable and function types are **recorded** in the symbol table.

**Not Implemented:** Type compatibility is **not enforced** at expression or assignment level. There is no implicit or explicit type coercion checking.

---

## 5. Scope Checking

Scope is managed through a **stack-based symbol table** (see Symbol Table documentation). The semantic analyzer calls `enterScope()` / `exitScope()` at:

| Event | Action |
|-------|--------|
| Entering a `FunctionNode` | `enterScope()` for the function's local scope |
| Exiting a `FunctionNode` | `exitScope()` |
| Entering a `BlockNode` | `enterScope()` |
| Exiting a `BlockNode` | `exitScope()` |

Variable lookups (`symbolTable.lookup(name)`) traverse from the innermost scope outward to global, implementing **lexical (static) scoping**.

---

## 6. Semantic Error Detection — DiagnosticEngine

All semantic errors are logged through the centralized `DiagnosticEngine`:

```cpp
class DiagnosticEngine {
public:
    static void logSemanticError(const std::string& file, int line, int col,
                                  const std::string& msg);
    static bool hasErrors();
    static const std::vector<DiagnosticError>& getErrors();
    static void clear();
};
```

**DiagnosticError structure:**
```cpp
struct DiagnosticError {
    std::string phase;     // "Semantic Error"
    std::string filename;
    int line;
    int column;
    std::string message;
};
```

> **Note:** Line and column numbers for semantic errors are currently reported as `0` (position tracking from AST nodes is Not Implemented).

---

## 7. Semantic Analysis Output

The semantic analyzer produces two output files (saved to `output/`):

| File | Content |
|------|---------|
| `output/symbol_table.txt` | Complete symbol table dump |
| `output/semantic_report.txt` | List of semantic analysis events and errors |

**Sample `semantic_report.txt`:**
```
C SEMANTIC ANALYSIS REPORT:

Function declared: int main
Variable declared: int number
Semantic analysis completed with 0 errors.
```

**Sample `symbol_table.txt`:**
```
            C SYMBOL TABLE
Scope Level | Name   | Type | Kind     | Params
----------------------------------------
  Level 0   | main   | int  | Function |
  Level 1   | number | int  | Variable |
========================================
```

---

## 8. Semantic Analysis Traversal Order

The analyzer uses a **pre-order depth-first** traversal of the AST:

```
PROGRAM
├── FUNCTION (checkNode called → declare in global scope → enterScope)
│   ├── BLOCK
│   │   ├── VAR_DECL (declare in current scope)
│   │   ├── IF_STMT
│   │   │   ├── condition (checkNode)
│   │   │   ├── thenBranch (checkNode → BlockNode → enterScope)
│   │   │   └── elseBranch (checkNode → BlockNode → enterScope)
│   │   └── RETURN_STMT (checkNode on expr)
│   └── exitScope
└── (next declaration)
```

---

## 9. Design Decisions

| Decision | Rationale |
|----------|-----------|
| Separate `Semantic_X` per language | C++ and Java introduce additional constructs (class members, static methods) requiring language-specific semantic logic |
| AST-based (not token-stream-based) semantic analysis | AST makes scope structure explicit via `BlockNode`, eliminating the need to track `{` `}` manually |
| DiagnosticEngine as static singleton | Allows any component to report errors without threading the error list through function parameters |
| `allSymbols` permanent record in SymbolTable | Retains all declared symbols even after `exitScope()`, enabling complete symbol table reporting |
