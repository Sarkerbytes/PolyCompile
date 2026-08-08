 


PolyCompile
Team Information
Team Member
Student ID
Ahmed Fairuz Anika
231-115-161
Tushar Sarker
231-115-171
Shongeet Saha
231-115-189





Table of Contents
Chapter 1: Introduction........................................................................... 3
Project Context................................................................................................... 3
Motivation.......................................................................................................... 3
Chapter 2: Objectives.............................................................................. 4
Project Objectives.............................................................................................. 4
What the Compiler Demonstrates.................................................................... 4
Chapter 3: Language Specification........................................................... 5
Complete Language Description....................................................................... 5
Supported Keywords.......................................................................................... 5
Operators............................................................................................................ 5
Data Types.......................................................................................................... 5
Formal CFG Grammar........................................................................................ 5
Chapter 4: Compiler Architecture............................................................ 7
Overall Compiler Pipeline.................................................................................. 7
Module Interactions........................................................................................... 7
Chapter 5: Lexer Design.......................................................................... 9
Token Definitions............................................................................................... 9
Regular Expressions........................................................................................... 9
Design Decisions................................................................................................. 9
Chapter 6: Parser Design....................................................................... 10
Grammar........................................................................................................... 10
Operator Precedence & Associativity Rules.................................................. 10
Conflict Resolution........................................................................................... 10
Chapter 7: Abstract Syntax Tree............................................................ 11
Node Structure................................................................................................. 11
AST Construction.............................................................................................. 11
Example AST..................................................................................................... 11
Chapter 8: Semantic Analysis................................................................. 12
Semantic Rules................................................................................................. 12
Type Checking.................................................................................................. 12
Scope Checking................................................................................................ 12
Semantic Error Detection................................................................................ 12
Chapter 9: Symbol Table....................................................................... 13
Data Structure.................................................................................................. 13
Scope Handling Strategy.................................................................................. 13
Symbol Lookup................................................................................................. 13
Symbol Insertion.............................................................................................. 13
Chapter 10: Intermediate Code Generation........................................... 14
Three Address Code (TAC)............................................................................... 14
Intermediate Representation......................................................................... 14
Examples........................................................................................................... 14
Chapter 11: Challenges.......................................................................... 15
Problems Encountered.................................................................................... 15
How They Were Solved................................................................................... 15
Lessons Learned............................................................................................... 15
Chapter 12: Testing............................................................................... 16
Chapter 13: Conclusion.......................................................................... 18
Project Achievements...................................................................................... 18
Learning Outcomes.......................................................................................... 18
Future Work..................................................................................................... 18
 






Chapter 1: Introduction
Project Context
PolyCompile is an educational, multi-language compiler framework built to translate and execute subsets of three major programming languages: C, C++, and Java. Developed as part of a university Compiler Construction course, PolyCompile demonstrates a complete 6-phase compilation model that bridges diverse language frontends into a single unified Intermediate Representation (IR), performs multi-pass optimization, emits educational target assembly instructions, and executes the compiled output on an interactive virtual runtime engine.
The project features a dual-frontend architecture:
1. Unified Compiler CLI (polycompile / polycompile.exe): A C++ application using custom hand-crafted lexers, recursive-descent AST generators, semantic analyzers, TAC IR generator, 5-pass TAC optimizer, assembly code generator, and virtual machine executor.
2. Standalone Flex & Bison Deliverables (test_c.exe, test_cpp.exe, test_java.exe): Independent executables generated directly from formal Flex (.l) lexical specifications and Bison (.y) LALR(1) grammars for theoretical verification.
3. Web IDE (server/): A Node.js/Express web application integrated with Monaco Editor, enabling real-time code compilation, live execution output, and phase-by-phase visual inspection in web browsers.
 
Motivation
Modern computer science curricula often demonstrate compilation using a single toy language. However, real-world software engineering demands an understanding of how distinct syntactical idioms (procedural C, stream-oriented C++, and object/class-structured Java) can be lowered into unified machine representations.
PolyCompile was motivated by the desire to:
●        Deeply understand lexical analysis, shift-reduce/LALR parsing, Abstract Syntax Trees, symbol table scope dynamics, type consistency, code optimization, and stack-based execution.
●        Build a modular architecture where different frontends funnel into a shared, language-agnostic Intermediate Code Generator (TAC).
●        Provide visual debugging tools (--tokens, --ast, --symbol-table, --tac, --opt, --asm, --debug) that make intermediate compiler states explicit and readable.
Chapter 2: Objectives
Project Objectives
1. Multi-Language Frontend Parsing: Support C, C++, and Java syntax subsets via both Flex/Bison LALR(1) specs and hand-crafted lexers/parsers.
2. Abstract Syntax Tree Construction: Construct unified node structures (ASTNode, ExprAST, StmtAST, BlockAST) for expression evaluation, control flow, functions, and declarations.
3. Multi-Scope Semantic Analysis: Enforce static typing, block/function scoping, undeclared variable detection, type mismatch detection, and duplicate symbol validation.
4. Three-Address Code Generation: Translate ASTs into linear TAC instruction streams using temporaries (t0, t1, ...), labels (L0, L1, ...), conditional/unconditional jumps, and function calls.
5. Multi-Pass TAC Optimization: Implement 5 optimization passes: Constant Folding, Constant Propagation, Copy Propagation, Algebraic Simplification, and Dead Code Elimination.
6. Code Generation & Execution: Emit readable target assembly code and simulate virtual runtime execution to evaluate runtime stdout output.
 
What the Compiler Demonstrates
PolyCompile demonstrates:
●        How different language syntaxes share low-level computational semantics.
●        Practical application of formal language theory (Context-Free Grammars, Chomsky hierarchy, Flex regular expressions, Bison parse tables).
●        Intermediate code optimization techniques used in commercial compilers (like GCC or LLVM).
●        Building production-grade tooling including command-line interfaces, diagnostic engines, and web-based developer interfaces.
Chapter 3: Language Specification
Complete Language Description
PolyCompile supports core subsets of C (.c), C++ (.cpp), and Java (.java). Each subset shares identical control flow constructs and operator precedence while maintaining language-specific I/O conventions and entry-point structures.
Supported Keywords
Language
Keywords Supported
C
int, float, double, char, bool, void, if, else, while, do, for, switch, case, default, break, continue, return, printf, scanf
C++
int, float, double, char, bool, string, void, if, else, while, do, for, switch, case, default, break, continue, return, using, namespace, std, cout, cin
Java
int, float, double, char, boolean, String, void, if, else, while, do, for, switch, case, default, break, continue, return, public, class, static, import, System, out, println, print, Scanner

 
Operators
●        Arithmetic: +, -, *, /, %, ++, --
●        Relational: ==, !=, <, >, <=, >=
●        Logical: &&, ||, !
●        Assignment: =
●        Stream / Bitwise: <<, >> (used in C++ I/O streams and numeric operations)
Data Types
●        int (32-bit signed integer)
●        float / double (IEEE 754 floating point numbers)
●        char (8-bit character)
●        bool / boolean (Boolean true/false)
●        string / String (Character sequence strings)
●        void (Function return type indicating no value)
Formal CFG Grammar
Below is the formal Context-Free Grammar (BNF notation) implemented across PolyCompile frontends:
<program>        	::= <declaration_list>
<declaration_list>   ::= <declaration> | <declaration_list> <declaration>
<declaration>    	::= <header_directive> | <function_def> | <var_decl> | <class_def>
 
<type_specifier> 	::= "int" | "float" | "double" | "char" | "bool" | "boolean" | "string" | "String" | "void"
 
<var_decl>       	::= <type_specifier> <ident_list> ";"
<ident_list>     	::= <ident_init> | <ident_list> "," <ident_init>
<ident_init>     	::= IDENTIFIER | IDENTIFIER "=" <expression>
 
<function_def>   	::= <type_specifier> IDENTIFIER "(" <param_list> ")" <compound_stmt>
<param_list>     	::= <param> | <param_list> "," <param> | ε
<param>          	::= <type_specifier> IDENTIFIER
 
<compound_stmt>  	::= "{" <statement_list> "}"
<statement_list> 	::= <statement> <statement_list> | ε
 
<statement>      	::= <var_decl>
                   	| <expr_stmt>
                   	| <if_stmt>
                   	| <while_stmt>
                   	| <do_while_stmt>
                   	| <for_stmt>
                   	| <switch_stmt>
                   	| <return_stmt>
                   	| <io_stmt>
                   	| <compound_stmt>
 
<expr_stmt>      	::= <expression> ";" | ";"
<if_stmt>        	::= "if" "(" <expression> ")" <statement> [ "else" <statement> ]
<while_stmt>     	::= "while" "(" <expression> ")" <statement>
<do_while_stmt>  	::= "do" <statement> "while" "(" <expression> ")" ";"
<for_stmt>       	::= "for" "(" [ <var_decl> | <expression> ] ";" [ <expression> ] ";" [ <expression> ] ")" <statement>
<switch_stmt>    	::= "switch" "(" <expression> ")" "{" <case_list> "}"
<case_list>      	::= <case_clause> <case_list> | ε
<case_clause>    	::= "case" <expression> ":" <statement_list> | "default" ":" <statement_list>
<return_stmt>    	::= "return" [ <expression> ] ";"
 
<expression>     	::= IDENTIFIER "=" <expression>
                   	| <logical_or_expr>
 
<logical_or_expr>	::= <logical_and_expr> { "||" <logical_and_expr> }
<logical_and_expr>   ::= <equality_expr> { "&&" <equality_expr> }
<equality_expr>  	::= <relational_expr> { ( "==" | "!=" ) <relational_expr> }
<relational_expr>	::= <additive_expr> { ( "<" | ">" | "<=" | ">=" ) <additive_expr> }
<additive_expr>  	::= <multiplicative_expr> { ( "+" | "-" ) <multiplicative_expr> }
<multiplicative_expr>::= <unary_expr> { ( "*" | "/" | "%" ) <unary_expr> }
<unary_expr>     	::= ( "!" | "-" | "+" ) <unary_expr> | <primary_expr>
<primary_expr>   	::= IDENTIFIER | INT_LITERAL | FLOAT_LITERAL | STRING_LITERAL | BOOL_LITERAL | "(" <expression> ")"

Chapter 4: Compiler Architecture
Overall Compiler Pipeline
PolyCompile processes source files through a strict 6-phase linear pipeline:
Source File (.c / .cpp / .java)
    	|
    	v
  Language Detector
    	|
    	v
  Select Frontend  --->  C Frontend (Lexer & Parser)
        |     	--->  C++ Frontend (Lexer & Parser)
        |     	--->  Java Frontend (Lexer & Parser)
    	v
  Abstract Syntax Tree (AST)
    	|
    	v
  Semantic Analyzer & Symbol Table
    	|
    	v
  TAC IR Generator
    	|
    	v
  TAC Optimizer (5 Passes)
    	|
        +----------------------+
        v                  	v
  Target Assembly    	Virtual Machine
  Generator                Executor
                          	|
                          	v
                     Stdout / Console Execution

Module Interactions
1. Language Detector (LanguageDetector.hpp): Inspects file extensions (.c, .cpp, .java) and selects the appropriate frontend.
2. Frontend Module (Frontend_C, Frontend_CPP, Frontend_Java): Runs tokenization, constructs AST nodes, and initial symbol tables.
3. Diagnostic Engine (DiagnosticEngine.hpp): Aggregates lexical, syntax, and semantic errors/warnings across all phases.
4. IR Generator (IRGenerator.cpp): Traverses the AST recursively and emits unoptimized TAC instructions.
5. Optimizer (Optimizer.cpp): Operates on std::vector<TACInstruction>, running 5 sequential optimization passes until convergence.
6. Code Generator (CodeGenerator.cpp): Maps TAC registers/instructions to an educational target assembly instruction format.
7. Executor (Executor.cpp): Executes the assembly instructions on an in-memory virtual machine state, maintaining variable stores and producing runtime standard output.
Chapter 5: Lexer Design
Token Definitions
Tokens are defined in Token.hpp as a Token structure containing:
●        type: TokenType enumeration (KEYWORD, IDENTIFIER, INT_LITERAL, FLOAT_LITERAL, STRING_LITERAL, OPERATOR, DELIMITER, END_OF_FILE, UNKNOWN).
●        value: String literal representation.
●        line: 1-indexed line number.
●        column: 1-indexed column number.
Regular Expressions
The Flex specification files (lexer_c.l, lexer_cpp.l, lexer_java.l) specify token patterns using regular expressions:
DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
INT         {DIGIT}+
FLOAT       {DIGIT}+\.{DIGIT}+([eE][+-]?{DIGIT}+)?
STRING      \"([^\"\\\n]|\\.)*\"
WS      	[ \t\r]+
NEWLINE     \n

Design Decisions
●        Line & Column Tracking: Hand-crafted lexers maintain line and column indices for detailed error reporting.
●        Comment Stripping: Both single-line (//...) and block comments (/* ... */) are stripped at tokenization without emitting tokens.
●        Preprocessor Skipping: Include headers (e.g. #include <stdio.h>) and imports (import java.util.*) are matched lexically and recorded without disrupting syntax trees.
Chapter 6: Parser Design
Grammar
The parsers accept context-free LALR(1) grammars implemented in Bison (parser_c.y, parser_cpp.y, parser_java.y) as well as recursive descent AST builders in C++.
Operator Precedence & Associativity Rules
Operators are defined with explicit precedence levels to resolve shift/reduce ambiguities:
Precedence
Operators
Associativity
1 (Lowest)
=
Right-to-Left
2
||
Left-to-Right
3
&&
Left-to-Right
4
==, !=
Left-to-Right
5
<, >, <=, >=
Left-to-Right
6
+, -
Left-to-Right
7
*, /, %
Left-to-Right
8 (Highest)
!, unary -, unary +
Right-to-Left

 
Conflict Resolution
Shift/Reduce conflicts in dangling-else statements are resolved using Bison precedence rules (%nonassoc LOWER_THAN_ELSE and %nonassoc ELSE), ensuring else binds to the nearest open if.
Chapter 7: Abstract Syntax Tree
Node Structure
The AST hierarchy is defined in ASTBase.hpp:
●        ASTNode: Abstract base class with virtual print(), getType(), and accept() methods.
●        ProgramAST: Root node storing global declarations and main functions.
●        VarDeclAST: Variable declaration node storing identifier, type, and optional initializer expression.
●        FunctionDeclAST: Function signature, parameters, and body block.
●        BinaryExprAST: Binary operator node with left and right child expression nodes.
●        LiteralAST: Int, float, string, or boolean constant node.
●        VariableAST: Identifier reference node.
●        IfStmtAST, WhileStmtAST, ForStmtAST, ReturnStmtAST: Control flow statement nodes.
AST Construction
Parsers build the tree bottom-up (Bison) or top-down (Recursive Descent). Each node takes ownership of its children using standard C++ smart pointers (std::shared_ptr<ASTNode>).
Example AST
For source code int x = 5 + 3;
ProgramAST
|-- VarDeclAST (type: int, name: x)
	|-- BinaryExprAST (op: +)
    	|-- LiteralAST (int: 5)
    	|-- LiteralAST (int: 3)

Chapter 8: Semantic Analysis
Semantic Rules
1. Variable Declaration: Every variable must be declared before use.
2. Unique Identifiers: No variable may be redeclared within the same scope level.
3. Type Consistency: Operations between mismatched types trigger warnings/errors or explicit conversion.
4. Function Parameters: Function call argument counts and types must match function prototypes.
5. Return Types: Return statement expressions must match declared function return types.
 
Type Checking
The semantic analyzer evaluates expressions recursively and assigns inferred types (TYPE_INT, TYPE_FLOAT, TYPE_BOOL, TYPE_STRING). Mismatched assignments (e.g., assigning string to int) emit semantic diagnostic errors.
Scope Checking
Nested scopes ({ ... }) create child symbol tables. Variable lookups traverse upward from current scope to global scope.
Semantic Error Detection
PolyCompile logs errors via DiagnosticEngine:
●        Error: Redeclaration of variable 'x' in scope
●        Error: Use of undeclared variable 'y'
●        Error: Type mismatch in assignment to 'z'
Chapter 9: Symbol Table
Data Structure
The Symbol Table is structured using a scoped linked hierarchy:
●        Symbol: Stores name, type, scopeLevel, lineDeclared, isInitialized, and memory offset.
●        SymbolTable: Contains std::unordered_map<std::string, Symbol> for the current scope and a pointer parent to the enclosing scope.
Scope Handling Strategy
●        enterScope(): Creates a new SymbolTable with parent pointing to current scope.
●        exitScope(): Restores current scope pointer to parent.
Symbol Lookup
lookup(name) searches local scope map. If not found, it recursively queries parent->lookup(name) until found or root is reached.
Symbol Insertion
insert(symbol) checks if name exists in local scope. If present, returns false (redeclaration error). Otherwise, inserts into local map.
Chapter 10: Intermediate Code Generation
Three Address Code (TAC)
TAC instructions have at most three operands: result = arg1 op arg2.
PolyCompile TAC operations include:
●        ASSIGN: t0 = 5
●        ADD, SUB, MUL, DIV, MOD: t1 = a + b
●        LABEL: L0:
●        JUMP: goto L1
●        JUMP_IF_FALSE: ifFalse t0 goto L2
●        PARAM, CALL, RETURN: param x, call foo, 1, return t2
Intermediate Representation
TAC represents linearized execution independent of target machine architectures.
Examples
Source Code:
int a = 10;
int b = 20;
int c = a + b * 2;

Generated TAC:
t0 = 20
t1 = 2
t2 = t0 * t1
t3 = 10
t4 = t3 + t2
c = t4

Chapter 11: Challenges
Problems Encountered
1. Grammar Ambiguities across 3 Languages: Handling distinct header directives and I/O syntaxes (printf vs cout << vs System.out.println).
2. AST Linearization for Complex Control Flow: Generating correct conditional jump labels (L0, L1) for do-while and switch-case blocks.
3. Pass Convergence in Optimization: Ensuring dead code elimination does not remove required labels or variables used across jump boundaries.
 
How They Were Solved
1. Created dedicated language-specific AST builders feeding into a single unified ASTNode hierarchy.
2. Built a label generation utility inside IRGenerator tracking forward and backward jump targets.
3. Implemented convergence loops in Optimizer running passes iteratively until zero instruction modifications occur.
 
Lessons Learned
●        Modularity and clean interface abstractions (like common IR) drastically simplify compiler extensibility.
●        Comprehensive diagnostic logging and visual inspection tools (--ast, --tac) speed up debugging exponentially.
Chapter 12: Testing
Test Case 1: Valid Program
Input Program (examples/add.c):
#include <stdio.h>
int main() {
	int a = 5;
	int b = 10;
	int sum = a + b;
    printf("%d", sum);
	return 0;
}

Expected Output: 15
Actual Output: 15
Result: PASS
 
Test Case 2: Lexical Errors
Input Program:
int main() {
	int @bad_var = 10;
	return 0;
}

Expected Output: Lexical Error: Unexpected character '@'
Actual Output: Lexical Error: Unexpected character '@' at line 2, column 9
Result: PASS
 
Test Case 3: Syntax Errors
Input Program:
int main() {
	int x = ;
	return 0;
}

Expected Output: Syntax Error: Unexpected token ';', expected expression
Actual Output: Syntax Error: Unexpected ';' at line 2
Result: PASS
 
Test Case 4: Semantic Errors
Input Program:
int main() {
	int a = 10;
	int a = 20;
	return 0;
}

Expected Output: Semantic Error: Redeclaration of variable 'a'
Actual Output: Semantic Error: Redeclaration of variable 'a' in scope at line 3
Result: PASS
Chapter 13: Conclusion
Project Achievements
●        Successfully implemented a 3-frontend (C, C++, Java) compiler pipeline.
●        Built a functional 5-pass TAC optimizer reducing redundant computations.
●        Integrated a Web IDE visualizer with Monaco Editor and live execution backend.
●        Delivered full documentation and automated build tooling (Makefile, Dockerfile).
Learning Outcomes
●        Gained practical mastery over Lexer/Parser tools (Flex & Bison) and formal CFG design.
●        Learned AST construction, scoped symbol management, TAC IR transformation, and stack execution models.
Future Work
●        Add pointer arithmetic and dynamic array heap allocation.
●        Support Object-Oriented features (classes, inheritance, virtual tables).
●        Implement an LLVM IR emitter backend for native machine binary output.

