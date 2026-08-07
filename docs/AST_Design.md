# AST Design — PolyCompile

---

## 1. Overview

The Abstract Syntax Tree (AST) in PolyCompile is defined in a **single unified header** [`compiler/common/Utilities/ASTBase.hpp`](../compiler/common/Utilities/ASTBase.hpp). All three language frontends (C, C++, Java) produce nodes from this shared type hierarchy, enabling the backend pipeline (IR Generator, Optimizer, Code Generator, Executor) to be completely language-independent.

---

## 2. Base Node Structure

```cpp
enum class ASTNodeType {
    PROGRAM,
    FUNCTION,
    VAR_DECL,
    VAR_DECL_LIST,
    BLOCK,
    IF_STMT,
    SWITCH_STMT,
    WHILE_STMT,
    DO_WHILE_STMT,
    FOR_STMT,
    RETURN_STMT,
    BREAK_STMT,
    CONTINUE_STMT,
    ASSIGN_STMT,
    BINARY_EXPR,
    UNARY_EXPR,
    LITERAL_EXPR,
    VAR_EXPR,
    CALL_EXPR,
    INPUT_STMT,
    OUTPUT_STMT
};

class ASTNode {
public:
    virtual ~ASTNode() {}
    virtual ASTNodeType getType() const = 0;
    virtual std::string toString(int indent = 0) const = 0;
protected:
    std::string getIndentStr(int indent) const {
        return std::string(indent * 2, ' ');
    }
};

using ASTNodePtr = std::shared_ptr<ASTNode>;
```

`ASTNodePtr` (a `shared_ptr<ASTNode>`) is the universal pointer type used throughout the compiler. This ensures:
- **Type safety** via `dynamic_pointer_cast`
- **Automatic memory management** — no manual `delete` calls
- **Nullable pointers** for optional subtrees (e.g., `else` branch of an `if`)

---

## 3. Node Types Reference

### 3.1 ProgramNode

```cpp
class ProgramNode : public ASTNode {
public:
    std::vector<ASTNodePtr> declarations;  // top-level functions/variables
};
```

Root of every AST. Contains all top-level declarations of the source file.

---

### 3.2 FunctionNode

```cpp
struct Parameter {
    std::string type;
    std::string name;
};

class FunctionNode : public ASTNode {
public:
    std::string returnType;
    std::string name;
    std::vector<Parameter> parameters;
    ASTNodePtr body;              // Always a BlockNode
};
```

Represents a function definition. Parameters carry both type and name.

---

### 3.3 VarDeclNode

```cpp
class VarDeclNode : public ASTNode {
public:
    std::string varType;          // "int", "float", etc.
    std::string varName;
    ASTNodePtr initExpr;          // nullptr if no initializer
};
```

Represents a single variable declaration with an optional initializer expression.

---

### 3.4 VarDeclListNode

```cpp
class VarDeclListNode : public ASTNode {
public:
    std::vector<ASTNodePtr> decls;  // vector of VarDeclNode
};
```

Represents a comma-separated declaration list: `int a, b, c;`. Does **not** open a new scope.

---

### 3.5 BlockNode

```cpp
class BlockNode : public ASTNode {
public:
    std::vector<ASTNodePtr> statements;
};
```

Represents a `{ ... }` compound statement. Opens a new lexical scope during semantic analysis.

---

### 3.6 IfNode

```cpp
class IfNode : public ASTNode {
public:
    ASTNodePtr condition;
    ASTNodePtr thenBranch;
    ASTNodePtr elseBranch;   // nullptr if no else
};
```

---

### 3.7 SwitchNode

```cpp
struct SwitchCase {
    ASTNodePtr value;
    std::vector<ASTNodePtr> body;
};

class SwitchNode : public ASTNode {
public:
    ASTNodePtr expression;
    std::vector<SwitchCase> cases;
    std::vector<ASTNodePtr> defaultBody;  // empty if no default
};
```

---

### 3.8 WhileNode / DoWhileNode

```cpp
class WhileNode : public ASTNode {
public:
    ASTNodePtr condition;
    ASTNodePtr body;
};

class DoWhileNode : public ASTNode {
public:
    ASTNodePtr body;
    ASTNodePtr condition;
};
```

---

### 3.9 ForNode

```cpp
class ForNode : public ASTNode {
public:
    ASTNodePtr init;        // VarDeclNode or AssignNode (nullable)
    ASTNodePtr condition;   // BinaryExprNode (nullable)
    ASTNodePtr update;      // UnaryExprNode or AssignNode (nullable)
    ASTNodePtr body;        // BlockNode or single statement
};
```

---

### 3.10 ReturnNode / BreakNode / ContinueNode

```cpp
class ReturnNode : public ASTNode {
public:
    ASTNodePtr expr;       // nullptr for bare return;
};

class BreakNode    : public ASTNode {};   // No children
class ContinueNode : public ASTNode {};   // No children
```

---

### 3.11 AssignNode

```cpp
class AssignNode : public ASTNode {
public:
    std::string varName;
    std::string op;        // "=", "+=", "-=", "*=", "/="
    ASTNodePtr expr;
};
```

---

### 3.12 BinaryExprNode

```cpp
class BinaryExprNode : public ASTNode {
public:
    std::string op;        // "+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "&&", "||"
    ASTNodePtr left;
    ASTNodePtr right;
};
```

---

### 3.13 UnaryExprNode

```cpp
class UnaryExprNode : public ASTNode {
public:
    std::string op;        // "!", "-", "++", "--", "pre++", "pre--", "post++", "post--"
    ASTNodePtr operand;
};
```

---

### 3.14 LiteralNode

```cpp
class LiteralNode : public ASTNode {
public:
    std::string value;      // The literal text (e.g., "42", "3.14", "\"hello\"")
    std::string valueType;  // "int", "float", "string", "bool", "char"
};
```

---

### 3.15 VarExprNode

```cpp
class VarExprNode : public ASTNode {
public:
    std::string name;
};
```

Represents a variable reference in an expression context.

---

### 3.16 CallExprNode

```cpp
class CallExprNode : public ASTNode {
public:
    std::string funcName;
    std::vector<ASTNodePtr> args;
};
```

---

### 3.17 InputNode

```cpp
class InputNode : public ASTNode {
public:
    std::string targetVar;                  // Primary target variable
    std::vector<std::string> targetVars;    // All targets (multi-argument scanf/cin)
    std::string promptMsg;
};
```

Represents `scanf(...)` in C, `cin >> x` in C++, or `scanner.nextInt()` in Java.

---

### 3.18 OutputNode

```cpp
class OutputNode : public ASTNode {
public:
    std::vector<ASTNodePtr> args;
    bool hasNewline;
};
```

Represents `printf(...)` in C, `cout << ...` in C++, or `System.out.println(...)` in Java.

---

## 4. AST Construction

The AST is built inside each `Frontend_*.cpp` by a **recursive-descent parser** that:
1. Consumes the token stream produced by the lexer
2. Creates the appropriate `ASTNode` subclass
3. Wraps children in `shared_ptr` (`std::make_shared<XNode>()`)
4. Returns `ASTNodePtr` upward through the call stack

### Example Construction (VarDecl)

```cpp
// Parser code:
auto node = std::make_shared<VarDeclNode>();
node->varType = consume(KEYWORD_INT).lexeme;     // "int"
node->varName = consume(IDENTIFIER).lexeme;       // "x"
if (peek().type == ASSIGN) {
    consume(ASSIGN);
    node->initExpr = parseExpression();           // BinaryExprNode, LiteralNode, etc.
}
consume(SEMICOLON);
return node;
```

---

## 5. Example AST — `hello.c`

**Source:**
```c
#include <stdio.h>
int main() {
    printf("Hello World!\n");
}
```

**AST (toString output):**
```
ProgramNode:
  FunctionNode: int main()
    BlockNode:
      OutputNode (newline=false):
        LiteralNode (string): "Hello World!\n"
```

**Debug output from `--debug` flag:**
```
<Program>
    |
 <main>
    |
 <Block>
    |
 <printf>
    |
<"Hello World!\n">
```

---

## 6. Example AST — `ifelse.c`

**Source:**
```c
int main() {
    int number;
    if (number % 2 == 0) {
        printf("%d is even\n", number);
    } else {
        printf("%d is odd\n", number);
    }
    return 0;
}
```

**AST Structure:**
```
ProgramNode:
  FunctionNode: int main()
    BlockNode:
      VarDeclNode: int number
      IfNode:
        Condition:
          BinaryExprNode: (==)
            BinaryExprNode: (%)
              VarExprNode: number
              LiteralNode (int): 2
            LiteralNode (int): 0
        Then:
          BlockNode:
            OutputNode (newline=false):
              LiteralNode (string): "%d is even\n"
              VarExprNode: number
        Else:
          BlockNode:
            OutputNode (newline=false):
              LiteralNode (string): "%d is odd\n"
              VarExprNode: number
      ReturnNode:
        LiteralNode (int): 0
```

---

## 7. AST Traversal

All phases traverse the AST using `switch` on `node->getType()` + `std::dynamic_pointer_cast`:

```cpp
void checkNode(ASTNodePtr node) {
    switch (node->getType()) {
        case ASTNodeType::FUNCTION: {
            auto func = std::dynamic_pointer_cast<FunctionNode>(node);
            // ... access func->name, func->parameters, func->body
            break;
        }
        case ASTNodeType::IF_STMT: {
            auto ifNode = std::dynamic_pointer_cast<IfNode>(node);
            checkNode(ifNode->condition);
            checkNode(ifNode->thenBranch);
            if (ifNode->elseBranch) checkNode(ifNode->elseBranch);
            break;
        }
        // ...
    }
}
```

---

## 8. Design Decisions

| Decision | Rationale |
|----------|-----------|
| Single unified `ASTBase.hpp` | All three frontends map to the same node types, making the backend language-agnostic |
| `shared_ptr<ASTNode>` | Automatic reference-counted memory management; safe to pass AST roots across function boundaries |
| `dynamic_pointer_cast` | Type-safe downcasting without manual RTTI checks |
| `toString(int indent)` virtual method | Enables tree printing at any node with consistent indentation |
| Nullable child pointers | `else` branch, `initExpr`, `for` clauses are optional — `nullptr` indicates absence |
