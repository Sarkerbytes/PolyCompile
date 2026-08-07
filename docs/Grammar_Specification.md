# Grammar Specification — PolyCompile

> Formal Context-Free Grammars (CFG) for all three supported language subsets.
> All grammars are LALR(1) grammars implemented via Bison.

---

## 1. Notation

| Symbol | Meaning |
|--------|---------|
| `::=` | Produces |
| `\|` | Alternation |
| `{ }` | Zero or more repetitions (EBNF shorthand) |
| `[ ]` | Optional (EBNF shorthand) |
| `'token'` | Terminal token |
| `UPPERCASE` | Terminal token from lexer |
| `lowercase` | Non-terminal |

---

## 2. C Language Grammar

### 2.1 Top-Level Structure

```
program         ::= declaration_list
declaration_list ::= declaration
                   | declaration_list declaration
declaration     ::= header_directive
                  | function_definition
                  | var_declaration
```

### 2.2 Type Specifiers

```
type_specifier  ::= 'int' | 'float' | 'char' | 'double' | 'bool' | 'void'
```

### 2.3 Variable Declarations

```
var_declaration  ::= type_specifier var_init_list ';'
var_init_list    ::= var_init | var_init_list ',' var_init
var_init         ::= IDENTIFIER
                   | IDENTIFIER '=' expression
                   | IDENTIFIER '[' CONST_INT ']'
                   | IDENTIFIER '[' ']'
```

### 2.4 Function Definitions

```
function_definition ::= type_specifier IDENTIFIER '(' param_list ')' compound_statement
                      | type_specifier IDENTIFIER '(' ')' compound_statement
                      | type_specifier IDENTIFIER '(' param_list ')' ';'
                      | type_specifier IDENTIFIER '(' ')' ';'

param_list      ::= param | param_list ',' param
param           ::= type_specifier IDENTIFIER
                  | type_specifier IDENTIFIER '[' ']'
                  | type_specifier
```

### 2.5 Statements

```
statement ::= var_declaration
            | expression_statement
            | compound_statement
            | if_statement
            | switch_statement
            | while_statement
            | do_while_statement
            | for_statement
            | printf_statement
            | scanf_statement
            | return_statement
            | break_statement
            | continue_statement

compound_statement   ::= '{' statement_list '}' | '{' '}'
statement_list       ::= statement | statement_list statement
expression_statement ::= expression ';' | ';'
```

### 2.6 Control Flow

```
if_statement       ::= 'if' '(' expression ')' statement
                     | 'if' '(' expression ')' statement 'else' statement

switch_statement   ::= 'switch' '(' expression ')' '{' case_list '}'
case_list          ::= case_clause | case_list case_clause
case_clause        ::= 'case' expression ':' statement_list
                     | 'case' expression ':'
                     | 'default' ':' statement_list
                     | 'default' ':'

while_statement    ::= 'while' '(' expression ')' statement
do_while_statement ::= 'do' statement 'while' '(' expression ')' ';'
for_statement      ::= 'for' '(' for_init ';' for_cond ';' for_update ')' statement
for_init           ::= var_declaration_inline | expression | ε
for_cond           ::= expression | ε
for_update         ::= expression | ε
var_declaration_inline ::= type_specifier IDENTIFIER '=' expression
                          | type_specifier IDENTIFIER

return_statement  ::= 'return' expression ';' | 'return' ';'
break_statement   ::= 'break' ';'
continue_statement ::= 'continue' ';'
```

### 2.7 I/O Statements

```
printf_statement ::= 'printf' '(' argument_list ')' ';'
                   | 'printf' '(' ')' ';'
scanf_statement  ::= 'scanf' '(' argument_list ')' ';'
```

### 2.8 Expressions (Precedence from lowest to highest)

```
expression       ::= assignment_expr
assignment_expr  ::= logical_or_expr
                   | unary_expr '='  assignment_expr
                   | unary_expr '+=' assignment_expr
                   | unary_expr '-=' assignment_expr
                   | unary_expr '*=' assignment_expr
                   | unary_expr '/=' assignment_expr

logical_or_expr  ::= logical_and_expr | logical_or_expr '||' logical_and_expr
logical_and_expr ::= equality_expr    | logical_and_expr '&&' equality_expr
equality_expr    ::= relational_expr
                   | equality_expr '==' relational_expr
                   | equality_expr '!=' relational_expr
relational_expr  ::= additive_expr
                   | relational_expr '<'  additive_expr
                   | relational_expr '>'  additive_expr
                   | relational_expr '<=' additive_expr
                   | relational_expr '>=' additive_expr
additive_expr    ::= multiplicative_expr
                   | additive_expr '+' multiplicative_expr
                   | additive_expr '-' multiplicative_expr
multiplicative_expr ::= unary_expr
                      | multiplicative_expr '*' unary_expr
                      | multiplicative_expr '/' unary_expr
                      | multiplicative_expr '%' unary_expr
unary_expr       ::= postfix_expr
                   | '++' unary_expr | '--' unary_expr
                   | '!' unary_expr  | '-' unary_expr | '&' unary_expr
postfix_expr     ::= primary_expr
                   | postfix_expr '++'
                   | postfix_expr '--'
                   | postfix_expr '[' expression ']'
                   | IDENTIFIER '(' argument_list ')'
                   | IDENTIFIER '(' ')'
primary_expr     ::= IDENTIFIER | CONST_INT | CONST_FLOAT
                   | STRING_LITERAL | CHAR_LITERAL
                   | 'true' | 'false'
                   | '(' expression ')'
argument_list    ::= expression | argument_list ',' expression
```

---

## 3. C++ Language Grammar

> The C++ grammar extends the C grammar with the following additions:

### 3.1 Additional Types

```
type_specifier  ::= ... (all C types) | 'string'
```

### 3.2 Using Directive

```
using_directive ::= 'using' 'namespace' IDENTIFIER ';'
```

### 3.3 Stream I/O

```
cout_statement  ::= 'cout' cout_chain ';'
cout_chain      ::= '<<' cout_arg | cout_chain '<<' cout_arg
cout_arg        ::= expression | 'endl'

cin_statement   ::= 'cin' '>>' IDENTIFIER ';'
                  | 'cin' '>>' IDENTIFIER ('>>' IDENTIFIER)* ';'
```

### 3.4 Class Keyword (Lexically recognized, Not Implemented as full OOP)

```
'class', 'new', 'delete', 'this', 'public', 'private', 'protected'
```
> These keywords are lexically tokenized but **class bodies and OOP features are Not Implemented** in the parser/semantic stages.

---

## 4. Java Language Grammar

### 4.1 Top-Level Structure

```
program           ::= class_declaration
class_declaration ::= modifiers 'class' IDENTIFIER '{' class_body '}'
class_body        ::= class_member*
class_member      ::= method_definition | field_declaration
modifiers         ::= ('public' | 'private' | 'protected' | 'static' | 'final' | 'abstract')*
```

### 4.2 Method Definitions

```
method_definition ::= modifiers type_specifier IDENTIFIER '(' param_list ')' compound_statement
                    | modifiers type_specifier IDENTIFIER '(' ')' compound_statement
```

### 4.3 Java-Specific Types

```
type_specifier ::= 'int' | 'float' | 'double' | 'char' | 'boolean' | 'String' | 'void'
                 | 'byte' | 'short' | 'long'
```

### 4.4 Java I/O

```
println_statement ::= 'System' '.' 'out' '.' 'println' '(' argument_list ')' ';'
                    | 'System' '.' 'out' '.' 'print'   '(' argument_list ')' ';'
scanner_read      ::= IDENTIFIER '.' 'nextInt'    '(' ')'
                    | IDENTIFIER '.' 'nextDouble' '(' ')'
                    | IDENTIFIER '.' 'next'       '(' ')'
```

---

## 5. Operator Precedence Table (All Languages)

| Precedence | Operator(s) | Associativity |
|-----------|-------------|---------------|
| 1 (lowest) | `=`, `+=`, `-=`, `*=`, `/=` | Right |
| 2 | `\|\|` | Left |
| 3 | `&&` | Left |
| 4 | `==`, `!=` | Left |
| 5 | `<`, `>`, `<=`, `>=` | Left |
| 6 | `+`, `-` | Left |
| 7 | `*`, `/`, `%` | Left |
| 8 | `!`, `++`, `--` (prefix) | Right |
| 9 (highest) | `()`, `[]` (postfix) | Left |

---

## 6. Token Regular Expressions

| Token | Regular Expression | Description |
|-------|-------------------|-------------|
| `IDENTIFIER` | `[a-zA-Z_][a-zA-Z0-9_]*` | Variable and function names |
| `CONST_INT` | `[0-9]+` | Integer literals |
| `CONST_FLOAT` | `[0-9]+"."[0-9]* \| "."[0-9]+` | Floating-point literals |
| `STRING_LITERAL` | `"([^"\\]\\.)*"` | String literals |
| `CHAR_LITERAL` | `'([^'\\]\\.)' ` | Character literals |
| `HEADER_DIRECTIVE` | `#include<...> \| #include"..."` | Preprocessor includes |

---

## 7. Keywords

### C Keywords
`int`, `float`, `char`, `double`, `bool`, `void`, `if`, `else`, `while`, `do`, `for`, `switch`, `case`, `default`, `break`, `continue`, `return`, `printf`, `scanf`, `true`, `false`

### C++ Additional Keywords
`using`, `namespace`, `cout`, `cin`, `endl`, `class`, `new`, `delete`, `this`, `public`, `private`, `protected`, `string`

### Java Additional Keywords
`class`, `interface`, `extends`, `implements`, `public`, `private`, `protected`, `static`, `final`, `abstract`, `new`, `this`, `super`, `instanceof`, `throws`, `throw`, `try`, `catch`, `finally`, `boolean`, `byte`, `short`, `long`, `String`, `null`
