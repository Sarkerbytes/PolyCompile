# Parser Flow Diagram

## 1. Recursive Descent Parser Flow (Main Pipeline)

```mermaid
flowchart TD
    START["Token Stream\nfrom Lexer"] --> PARSE_PROGRAM["parseProgram()"]

    PARSE_PROGRAM --> CHECK_DECL{"Token type?"}
    CHECK_DECL -->|"KEYWORD_INT\nKEYWORD_VOID\nKEYWORD_FLOAT\netc."| PARSE_DECL["parseDeclaration()"]
    CHECK_DECL -->|"#include"| SKIP_HDR["Skip Header Directive"]
    CHECK_DECL -->|"EOF"| DONE["Return ProgramNode"]

    PARSE_DECL --> LOOK_AHEAD{"Look ahead:\nIDENTIFIER '(' ?"}
    LOOK_AHEAD -->|"Yes"| PARSE_FUNC["parseFunctionDef()\n→ FunctionNode"]
    LOOK_AHEAD -->|"No"| PARSE_VAR["parseVarDecl()\n→ VarDeclNode"]

    PARSE_FUNC --> PARSE_PARAMS["parseParamList()"]
    PARSE_FUNC --> PARSE_BODY["parseBlock()\n→ BlockNode"]

    PARSE_BODY --> PARSE_STMT_LIST["parseStatementList()"]
    PARSE_STMT_LIST --> PARSE_STMT{"Statement type?"}

    PARSE_STMT -->|if| PARSE_IF["parseIfStatement()\n→ IfNode"]
    PARSE_STMT -->|while| PARSE_WHILE["parseWhileStatement()\n→ WhileNode"]
    PARSE_STMT -->|for| PARSE_FOR["parseForStatement()\n→ ForNode"]
    PARSE_STMT -->|do| PARSE_DOWHILE["parseDoWhile()\n→ DoWhileNode"]
    PARSE_STMT -->|switch| PARSE_SWITCH["parseSwitchStatement()\n→ SwitchNode"]
    PARSE_STMT -->|return| PARSE_RET["parseReturn()\n→ ReturnNode"]
    PARSE_STMT -->|break| PARSE_BRK["→ BreakNode"]
    PARSE_STMT -->|continue| PARSE_CONT["→ ContinueNode"]
    PARSE_STMT -->|printf/cout| PARSE_OUT["parseOutput()\n→ OutputNode"]
    PARSE_STMT -->|scanf/cin| PARSE_IN["parseInput()\n→ InputNode"]
    PARSE_STMT -->|type keyword| PARSE_VDCL["parseVarDecl()\n→ VarDeclNode"]
    PARSE_STMT -->|identifier| PARSE_EXPR_STMT["parseExpressionStatement()\n→ AssignNode / CallExpr"]
    PARSE_STMT -->|"}"| BLOCK_END["End of block"]

    PARSE_IF --> PARSE_COND["parseExpression()\n→ condition"]
    PARSE_IF --> PARSE_THEN["parseBlock()\n→ thenBranch"]
    PARSE_IF -->|"else token"| PARSE_ELSE["parseBlock()\n→ elseBranch"]
```

---

## 2. Expression Parsing Hierarchy (Precedence Climbing)

```mermaid
flowchart LR
    parseExpression --> parseAssignment
    parseAssignment -->|"not assignment"| parseLogicalOr
    parseAssignment -->|"= += -= *= /="| parseAssignment_RHS["parseAssignment (right-recursive)"]

    parseLogicalOr --> parseLogicalAnd
    parseLogicalOr -->|"||"| parseLogicalOr_Loop["Loop: parse more ||"]

    parseLogicalAnd --> parseEquality
    parseLogicalAnd -->|"&&"| parseLogicalAnd_Loop["Loop: parse more &&"]

    parseEquality --> parseRelational
    parseEquality -->|"== !="| parseEquality_Loop["Loop: parse more == !="]

    parseRelational --> parseAdditive
    parseRelational -->|"< > <= >="| parseRelational_Loop["Loop: parse more comparisons"]

    parseAdditive --> parseMultiplicative
    parseAdditive -->|"+ -"| parseAdditive_Loop["Loop: parse more + -"]

    parseMultiplicative --> parseUnary
    parseMultiplicative -->|"* / %"| parseMultiplicative_Loop["Loop: parse more * / %"]

    parseUnary -->|"! - ++ --"| parseUnary_Recursive["parseUnary (recursive)"]
    parseUnary -->|"no prefix"| parsePostfix

    parsePostfix --> parsePrimary
    parsePostfix -->|"++ --"| parsePostfix_Inc["post-increment/decrement"]
    parsePostfix -->|"IDENTIFIER("| parseCall["parseCallExpr → CallExprNode"]
    parsePostfix -->|"["| parseArrayIndex["parseArrayAccess"]

    parsePrimary -->|"IDENTIFIER"| VarExprNode
    parsePrimary -->|"INT_CONST"| LiteralNode_Int["LiteralNode (int)"]
    parsePrimary -->|"FLOAT_CONST"| LiteralNode_Float["LiteralNode (float)"]
    parsePrimary -->|"STRING_LITERAL"| LiteralNode_String["LiteralNode (string)"]
    parsePrimary -->|"true/false"| LiteralNode_Bool["LiteralNode (bool)"]
    parsePrimary -->|"( expr )"| GroupedExpr["parseExpression (grouped)"]
```

---

## 3. Bison LALR(1) Parser Flow (Standalone Deliverable)

```mermaid
flowchart TD
    A["Token from Lexer (yylex)"] --> B["Push onto LALR Stack"]
    B --> C{"Can Reduce?"}
    C -->|"Rule matches stack top"| D["Apply Grammar Action\nprintf trace message"]
    D --> E["Pop RHS, Push LHS non-terminal"]
    E --> C
    C -->|"No reduction possible"| F{"Can Shift?"}
    F -->|"Lookahead fits grammar"| A
    F -->|"No shift possible"| G["yyerror() — Syntax Error\nIncrement error counter\nAttempt error recovery"]
    G --> H{"Recoverable?"}
    H -->|"Yes - discard tokens"| A
    H -->|"No"| I["Abort parsing"]
    C -->|"Accept"| J["Parse complete\nPrint success message"]
```

---

## 4. Error Recovery

The Bison parsers use Bison's built-in `error` recovery token. When a syntax error is encountered:

1. `yyerror()` is called — prints `[Syntax Error] Line N: message (near 'token')`
2. The error counter is incremented
3. Bison attempts to synchronize by discarding tokens until it finds a recovery point (typically `;` or `}`)
4. Parsing continues from the recovery point

At the end of parsing:
```
[OK] Parsed successfully with 0 syntax errors.
```
or:
```
[FAIL] 2 syntax error(s) found.
```
