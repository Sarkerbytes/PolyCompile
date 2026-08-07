# Lexer Design — PolyCompile

---

## 1. Overview

PolyCompile provides **three dedicated lexers**, one per supported language:

| Lexer File | Language | Tool |
|------------|----------|------|
| `compiler/c/lexer/lexer_c.l` | C | Flex |
| `compiler/cpp/lexer/lexer_cpp.l` | C++ | Flex |
| `compiler/java/lexer/lexer_java.l` | Java | Flex |

All three lexers are **Flex specifications** (`.l` files) compiled using the `flex` tool.  
A shared `Token` data structure (`Token.hpp`) is used by the C++ frontend pipeline for token representation.

---

## 2. Token Structure

Defined in [`compiler/common/Token/Token.hpp`](../compiler/common/Token/Token.hpp):

```cpp
enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    INT_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,
    BOOL_LITERAL,
    OPERATOR,
    DELIMITER,
    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};
```

Each token stores:
- **type**: Broad category (KEYWORD, IDENTIFIER, etc.)
- **lexeme**: Exact matched text from source
- **line**: Source line number (1-indexed)
- **column**: Source column number (1-indexed)

---

## 3. Regular Expression Definitions

The following macro definitions are shared across all three Flex specifications:

```flex
DIGIT       [0-9]
LETTER      [a-zA-Z_]
ALNUM       [a-zA-Z0-9_]
INT_CONST   {DIGIT}+
FLOAT_CONST {DIGIT}+"." {DIGIT}* | "." {DIGIT}+
ID          {LETTER}{ALNUM}*
```

### Java-Specific Extensions

```flex
INT_CONST   {DIGIT}+[lL]?
FLOAT_CONST {DIGIT}+"." {DIGIT}*[fFdD]? | "." {DIGIT}+[fFdD]?
```
Java allows suffix letters (`l`, `L`, `f`, `F`, `d`, `D`) on numeric literals.

---

## 4. Token Definitions by Category

### 4.1 Whitespace & Comments

| Pattern | Action |
|---------|--------|
| `[ \t\r]+` | Skip (ignored) |
| `\n` | Increment line counter, reset column |
| `"//"[^\n]*` | Skip single-line comment |
| `"/*" ... "*/"` | Skip block comment (exclusive start condition `BLOCK_COMMENT`) |

### 4.2 Preprocessor Directives (C / C++)

| Pattern | Token Returned |
|---------|---------------|
| `#include <...>` | `HEADER_DIRECTIVE` |
| `#include "..."` | `HEADER_DIRECTIVE` |
| `#define ...` | Skipped (macro definitions not processed) |

### 4.3 Keywords — C Language

| Keyword | Token Name |
|---------|-----------|
| `int` | `KEYWORD_INT` |
| `float` | `KEYWORD_FLOAT` |
| `char` | `KEYWORD_CHAR` |
| `double` | `KEYWORD_DOUBLE` |
| `bool` | `KEYWORD_BOOL` |
| `void` | `KEYWORD_VOID` |
| `if` | `KEYWORD_IF` |
| `else` | `KEYWORD_ELSE` |
| `while` | `KEYWORD_WHILE` |
| `do` | `KEYWORD_DO` |
| `for` | `KEYWORD_FOR` |
| `switch` | `KEYWORD_SWITCH` |
| `case` | `KEYWORD_CASE` |
| `default` | `KEYWORD_DEFAULT` |
| `break` | `KEYWORD_BREAK` |
| `continue` | `KEYWORD_CONTINUE` |
| `return` | `KEYWORD_RETURN` |
| `printf` | `KEYWORD_PRINTF` |
| `scanf` | `KEYWORD_SCANF` |
| `true` | `CONST_BOOL_TRUE` |
| `false` | `CONST_BOOL_FALSE` |

### 4.4 Additional Keywords — C++

| Keyword | Token Name |
|---------|-----------|
| `using` | `KEYWORD_USING` |
| `namespace` | `KEYWORD_NAMESPACE` |
| `cout` | `KEYWORD_COUT` |
| `cin` | `KEYWORD_CIN` |
| `endl` | `KEYWORD_ENDL` |
| `class` | `KEYWORD_CLASS` |
| `new` | `KEYWORD_NEW` |
| `delete` | `KEYWORD_DELETE` |
| `this` | `KEYWORD_THIS` |
| `public` | `KEYWORD_PUBLIC` |
| `private` | `KEYWORD_PRIVATE` |
| `protected` | `KEYWORD_PROTECTED` |
| `string` | `KEYWORD_STRING` |

### 4.5 Additional Keywords — Java

| Keyword | Token Name |
|---------|-----------|
| `class` | `KEYWORD_CLASS` |
| `interface` | `KEYWORD_INTERFACE` |
| `extends` | `KEYWORD_EXTENDS` |
| `implements` | `KEYWORD_IMPLEMENTS` |
| `static` | `KEYWORD_STATIC` |
| `final` | `KEYWORD_FINAL` |
| `abstract` | `KEYWORD_ABSTRACT` |
| `super` | `KEYWORD_SUPER` |
| `instanceof` | `KEYWORD_INSTANCEOF` |
| `throws` / `throw` | `KEYWORD_THROWS` / `KEYWORD_THROW` |
| `try` / `catch` / `finally` | `KEYWORD_TRY` / `KEYWORD_CATCH` / `KEYWORD_FINALLY` |
| `boolean` | `KEYWORD_BOOLEAN` |
| `byte` / `short` / `long` | `KEYWORD_BYTE` / `KEYWORD_SHORT` / `KEYWORD_LONG` |
| `String` | `KEYWORD_STRING` |
| `null` | `CONST_NULL` |

### 4.6 Identifiers and Literals

| Pattern | Token |
|---------|-------|
| `{ID}` | `IDENTIFIER` |
| `{INT_CONST}` | `CONST_INT` |
| `{FLOAT_CONST}` | `CONST_FLOAT` |
| `"..."` | `STRING_LITERAL` |
| `'.'` | `CHAR_LITERAL` |

### 4.7 Operators

| Pattern | Token | Language |
|---------|-------|----------|
| `==` | `OP_EQ` | C, C++, Java |
| `!=` | `OP_NEQ` | C, C++, Java |
| `<=` | `OP_LEQ` | C, C++, Java |
| `>=` | `OP_GEQ` | C, C++, Java |
| `&&` | `OP_AND` | C, C++, Java |
| `\|\|` | `OP_OR` | C, C++, Java |
| `++` | `OP_INC` | C, C++, Java |
| `--` | `OP_DEC` | C, C++, Java |
| `+=` | `OP_PLUS_ASSIGN` | C, C++, Java |
| `-=` | `OP_MINUS_ASSIGN` | C, C++, Java |
| `*=` | `OP_MUL_ASSIGN` | C, C++ |
| `/=` | `OP_DIV_ASSIGN` | C, C++ |
| `=` | `ASSIGN` | C, C++, Java |
| `+`, `-`, `*`, `/`, `%` | Single char tokens | C, C++, Java |
| `<`, `>`, `!`, `&`, `\|` | Single char tokens | C, C++, Java |
| `<<` | `STREAM_OUT` | C++ only |
| `>>` | `STREAM_IN` | C++ only |
| `.` | `DOT` | Java only |

### 4.8 Delimiters

| Symbol | Token |
|--------|-------|
| `(` | `LPAREN` |
| `)` | `RPAREN` |
| `{` | `LBRACE` |
| `}` | `RBRACE` |
| `[` | `LBRACKET` |
| `]` | `RBRACKET` |
| `;` | `SEMICOLON` |
| `,` | `COMMA` |
| `:` | `COLON` |

### 4.9 Unknown Characters

```c
.   { fprintf(stderr, "[Lexical Error] Line %d, Col %d: Unknown character '%s'\n",
              c_line, c_col - 1, yytext); }
```

Any character not matching a defined pattern triggers a **Lexical Error** message with line/column information.

---

## 5. Flex Configuration Options

All lexers use these Flex options:

```flex
%option noyywrap    // No yywrap() required after EOF
%option yylineno    // Automatic line number tracking
%option batch       // Disable interactive mode (Windows-safe)
```

The `%x BLOCK_COMMENT` exclusive start condition is used in all three lexers to correctly handle multi-line `/* ... */` comments.

---

## 6. Line and Column Tracking

Each lexer maintains its own `line` and `col` counters:

```c
int c_line = 1;
int c_col  = 1;

#define YY_USER_ACTION  c_col += yyleng;  // Column advances by token length
```

Newlines explicitly reset the column to 1 and increment the line counter:
```c
\n  { c_line++; c_col = 1; }
```

---

## 7. Design Decisions

| Decision | Rationale |
|----------|-----------|
| Three separate Flex files | Prevents keyword conflicts between languages (e.g., `bool` vs `boolean`, `cout` vs `printf`) |
| Keywords matched before identifiers | Flex uses longest match + first-rule-wins; keywords are listed before the `{ID}` rule |
| `safe_strdup()` instead of `strdup()` | Portable implementation; `strdup` is not standard C89 |
| `BLOCK_COMMENT` exclusive start condition | Correctly handles nested `/* ... */` spanning multiple lines without false matches |
| `#define` directives skipped | Macro expansion is Not Implemented; directives are consumed to prevent parse errors |
| `%option batch` | Required for correct operation on Windows (MinGW) where stdin may be a terminal |
