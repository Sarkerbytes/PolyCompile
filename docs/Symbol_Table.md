# Symbol Table — PolyCompile

---

## 1. Overview

PolyCompile implements a separate symbol table for each language frontend:

| Class | Language | File |
|-------|----------|------|
| `SymbolTable_C` | C | `compiler/c/symbol_table/SymbolTable_C.hpp` |
| `SymbolTable_CPP` | C++ | `compiler/cpp/symbol_table/SymbolTable_CPP.hpp` |
| `SymbolTable_Java` | Java | `compiler/java/symbol_table/SymbolTable_Java.hpp` |

All three follow the same design pattern: a **stack of hash maps** representing nested lexical scopes.

---

## 2. Symbol Record Structure

```cpp
struct SymbolC {
    std::string name;                         // Identifier name
    std::string type;                         // "int", "float", "void", etc.
    int         scopeLevel;                   // 0 = global, 1 = function, 2+ = nested blocks
    bool        isFunction;                   // true if this is a function declaration
    std::vector<std::string> paramTypes;      // parameter types (functions only)
};
```

---

## 3. Data Structure

```cpp
class SymbolTable_C {
private:
    std::vector<std::map<std::string, SymbolC>> scopes;
    // scopes[0] = global scope
    // scopes[1] = function body scope
    // scopes[2] = nested block scope, etc.

    std::vector<SymbolC> allSymbols;  // permanent record of every declared symbol
};
```

The symbol table is implemented as:
- A **`std::vector`** of scope levels (acts as a stack)
- Each scope level is a **`std::map<string, SymbolC>`** (name → symbol record)
- A separate **`allSymbols`** flat list for complete reporting after scopes are exited

---

## 4. Scope Handling Strategy

### 4.1 Entering a Scope

```cpp
void enterScope() {
    scopes.push_back(std::map<std::string, SymbolC>());
}
```

Called at the start of:
- Constructor (pushes global scope level 0)
- Each `FunctionNode` (pushes function-body scope)
- Each `BlockNode` (pushes block scope)

### 4.2 Exiting a Scope

```cpp
void exitScope() {
    if (scopes.size() > 1) {
        scopes.pop_back();      // Destroys the innermost scope map
    }
    // Global scope (scopes[0]) is never popped
}
```

All symbols declared in the exited scope become inaccessible for future lookups. However, they remain in the `allSymbols` permanent list for reporting purposes.

### 4.3 Scope Level Assignment

Each declared symbol records its `scopeLevel = scopes.size() - 1` at declaration time:

| Scope | Level |
|-------|-------|
| Global (top of file) | 0 |
| Function body | 1 |
| `if` / `while` / `for` block | 2 |
| Nested block | 3+ |

---

## 5. Symbol Insertion

```cpp
bool declare(const std::string& name, const std::string& type,
             bool isFunc = false,
             const std::vector<std::string>& params = {}) {

    // Check for redeclaration in the CURRENT scope only
    if (scopes.back().count(name)) {
        return false;   // Duplicate declaration — caller logs a semantic error
    }

    SymbolC sym;
    sym.name       = name;
    sym.type       = type;
    sym.scopeLevel = scopes.size() - 1;
    sym.isFunction = isFunc;
    sym.paramTypes = params;

    scopes.back()[name] = sym;   // Insert into current scope
    allSymbols.push_back(sym);   // Also persist in permanent record

    return true;
}
```

**Key properties:**
- Duplicate detection is **scope-local** — the same name can be declared in nested scopes (shadowing is allowed)
- Returns `false` on duplicate within the same scope; the semantic analyzer then logs the error

---

## 6. Symbol Lookup

```cpp
SymbolC* lookup(const std::string& name) {
    // Traverse scopes from innermost to outermost (reverse order)
    for (int i = static_cast<int>(scopes.size()) - 1; i >= 0; --i) {
        auto it = scopes[i].find(name);
        if (it != scopes[i].end()) {
            return &(it->second);
        }
    }
    return nullptr;   // Symbol not found in any scope
}
```

**Lookup behavior:**
- Implements **lexical (static) scoping**: inner declarations shadow outer ones
- Returns a **pointer to the SymbolC record** for direct modification if needed
- Returns `nullptr` if no declaration exists in any scope — the semantic analyzer treats this as an "undeclared" error

---

## 7. Symbol Table Output

The `toString()` method produces a formatted table of all ever-declared symbols:

```cpp
std::string toString() const {
    // Header
    ss << "            C SYMBOL TABLE              \n";
    ss << "Scope Level | Name | Type | Kind | Params\n";
    ss << "----------------------------------------\n";

    for (const auto& sym : allSymbols) {
        ss << "  Level " << sym.scopeLevel
           << "   | " << sym.name
           << " | "   << sym.type
           << " | "   << (sym.isFunction ? "Function" : "Variable")
           << " | ";
        // Print parameter types for functions
        for (size_t p = 0; p < sym.paramTypes.size(); ++p) {
            ss << sym.paramTypes[p];
            if (p + 1 < sym.paramTypes.size()) ss << ", ";
        }
        ss << "\n";
    }
}
```

**Sample Output (`output/symbol_table.txt`):**
```
            C SYMBOL TABLE

Scope Level | Name   | Type  | Kind     | Params
----------------------------------------
  Level 0   | main   | int   | Function |
  Level 1   | x      | int   | Variable |
  Level 1   | y      | int   | Variable |
  Level 1   | result | int   | Variable |
========================================
```

---

## 8. Example: Scope Lifecycle

For the following C source:

```c
int main() {
    int x = 5;
    if (x > 0) {
        int y = 10;   // y declared in scope level 2
    }
    // y is not visible here
    return 0;
}
```

**Scope evolution:**

| Event | Scope Stack State |
|-------|------------------|
| Program start | `[scope_0: {main}]` |
| Enter `main()` body | `[scope_0: {main}, scope_1: {x}]` |
| Enter `if` block | `[scope_0: {main}, scope_1: {x}, scope_2: {y}]` |
| Exit `if` block | `[scope_0: {main}, scope_1: {x}]` |
| Exit `main()` body | `[scope_0: {main}]` |

At any point, `lookup("y")` after the `if` block exits returns `nullptr` — correctly flagging usage of `y` outside its scope as an error.

---

## 9. Limitations

| Limitation | Notes |
|------------|-------|
| No type compatibility checks | Types are stored but not compared for assignment compatibility |
| No overloading support | C++ function overloading is Not Implemented |
| No class member symbol tables | Java/C++ class fields are Not Implemented |
| Position information missing | `scopeLevel` records scope depth, not line/column of declaration |
