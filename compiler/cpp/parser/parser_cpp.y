%{
/*
 * parser_cpp.y  –  Bison Parser for C++ Language
 * PolyCompile Project
 *
 * Usage:
 *   bison -d -o parser_cpp.tab.c parser_cpp.y
 *   (Generates parser_cpp.tab.c and parser_cpp.tab.h)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int  yylex(void);
extern int  cpp_line;
extern int  cpp_col;
extern char* yytext;
extern FILE* yyin;

int cpp_syntax_errors = 0;

void yyerror(const char* msg) {
    fprintf(stderr, "[Syntax Error] Line %d: %s (near '%s')\n",
            cpp_line, msg, yytext);
    cpp_syntax_errors++;
}

%}

/* ------------------------------------------------------------------ */
/*  Value types                                                         */
/* ------------------------------------------------------------------ */
%union {
    char* string_val;
}

/* ------------------------------------------------------------------ */
/*  Token declarations                                                  */
/* ------------------------------------------------------------------ */

/* Preprocessor */
%token <string_val> HEADER_DIRECTIVE

/* C++ specific keywords */
%token KEYWORD_USING
%token KEYWORD_NAMESPACE
%token KEYWORD_COUT
%token KEYWORD_CIN
%token KEYWORD_ENDL
%token KEYWORD_CLASS
%token KEYWORD_NEW
%token KEYWORD_DELETE
%token KEYWORD_THIS
%token KEYWORD_PUBLIC
%token KEYWORD_PRIVATE
%token KEYWORD_PROTECTED
%token <string_val> KEYWORD_STRING

/* Data-type keywords */
%token <string_val> KEYWORD_INT
%token <string_val> KEYWORD_FLOAT
%token <string_val> KEYWORD_CHAR
%token <string_val> KEYWORD_DOUBLE
%token <string_val> KEYWORD_BOOL
%token              KEYWORD_VOID

/* Control-flow */
%token KEYWORD_IF
%token KEYWORD_ELSE
%token KEYWORD_WHILE
%token KEYWORD_DO
%token KEYWORD_FOR
%token KEYWORD_SWITCH
%token KEYWORD_CASE
%token KEYWORD_DEFAULT
%token KEYWORD_BREAK
%token KEYWORD_CONTINUE
%token KEYWORD_RETURN

/* Boolean */
%token <string_val> CONST_BOOL_TRUE
%token <string_val> CONST_BOOL_FALSE

/* Literals */
%token <string_val> CONST_INT
%token <string_val> CONST_FLOAT
%token <string_val> STRING_LITERAL
%token <string_val> CHAR_LITERAL

/* Identifier */
%token <string_val> IDENTIFIER

/* Operators */
%token OP_EQ OP_NEQ OP_LEQ OP_GEQ
%token OP_AND OP_OR
%token OP_INC OP_DEC
%token OP_PLUS_ASSIGN OP_MINUS_ASSIGN OP_MUL_ASSIGN OP_DIV_ASSIGN
%token STREAM_OUT STREAM_IN
%token SCOPE_RES
%token ASSIGN

/* Delimiters */
%token SEMICOLON COMMA COLON DOT
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

/* ------------------------------------------------------------------ */
/*  Non-terminal types                                                  */
/* ------------------------------------------------------------------ */
%type <string_val> type_specifier
%type <string_val> expression assignment_expr logical_or_expr logical_and_expr
%type <string_val> equality_expr relational_expr additive_expr multiplicative_expr
%type <string_val> unary_expr postfix_expr primary_expr
%type <string_val> argument_list stream_output_chain

/* ------------------------------------------------------------------ */
/*  Operator precedence                                                 */
/* ------------------------------------------------------------------ */
%right ASSIGN OP_PLUS_ASSIGN OP_MINUS_ASSIGN OP_MUL_ASSIGN OP_DIV_ASSIGN
%left  OP_OR
%left  OP_AND
%left  OP_EQ OP_NEQ
%left  '<' '>' OP_LEQ OP_GEQ
%left  STREAM_OUT STREAM_IN
%left  '+' '-'
%left  '*' '/' '%'
%right '!' OP_INC OP_DEC
%left  LPAREN RPAREN LBRACKET RBRACKET DOT SCOPE_RES

%start program

%%

/* ================================================================== */
/*  TOP LEVEL                                                           */
/* ================================================================== */

program
    : declaration_list
        { printf("[Parse] C++ program parsed successfully.\n"); }
    ;

declaration_list
    : declaration
    | declaration_list declaration
    ;

declaration
    : header_directive
    | using_directive
    | class_definition
    | function_definition
    | var_declaration
    ;

/* ------------------------------------------------------------------ */
header_directive
    : HEADER_DIRECTIVE
        { printf("[Token] Include: %s\n", $1); free($1); }
    ;

/* ------------------------------------------------------------------ */
/*  using namespace std;                                                */
/* ------------------------------------------------------------------ */
using_directive
    : KEYWORD_USING KEYWORD_NAMESPACE IDENTIFIER SEMICOLON
        { printf("[Decl] using namespace %s;\n", $3); free($3); }
    ;

/* ================================================================== */
/*  CLASS DEFINITION                                                    */
/* ================================================================== */
class_definition
    : KEYWORD_CLASS IDENTIFIER LBRACE class_body RBRACE SEMICOLON
        { printf("[Class] class %s { ... };\n", $2); free($2); }
    | KEYWORD_CLASS IDENTIFIER LBRACE class_body RBRACE
        { printf("[Class] class %s { ... }\n", $2); free($2); }
    ;

class_body
    : class_member
    | class_body class_member
    | /* empty */
    ;

class_member
    : access_specifier COLON class_member_list
    | function_definition
    | var_declaration
    ;

access_specifier
    : KEYWORD_PUBLIC    { printf("[Access] public:\n"); }
    | KEYWORD_PRIVATE   { printf("[Access] private:\n"); }
    | KEYWORD_PROTECTED { printf("[Access] protected:\n"); }
    ;

class_member_list
    : class_member_item
    | class_member_list class_member_item
    ;

class_member_item
    : function_definition
    | var_declaration
    ;

/* ================================================================== */
/*  TYPE SPECIFIER                                                      */
/* ================================================================== */
type_specifier
    : KEYWORD_INT    { $$ = $1; }
    | KEYWORD_FLOAT  { $$ = $1; }
    | KEYWORD_CHAR   { $$ = $1; }
    | KEYWORD_DOUBLE { $$ = $1; }
    | KEYWORD_BOOL   { $$ = $1; }
    | KEYWORD_STRING { $$ = $1; }
    | KEYWORD_VOID   { $$ = "void"; }
    | IDENTIFIER     { $$ = $1; }   /* user-defined types / class names */
    ;

/* ================================================================== */
/*  VARIABLE DECLARATION                                                */
/* ================================================================== */
var_declaration
    : type_specifier var_init_list SEMICOLON
        { printf("[Decl] Variable: type=%s\n", $1); }
    ;

var_init_list
    : var_init
    | var_init_list COMMA var_init
    ;

var_init
    : IDENTIFIER
        { free($1); }
    | IDENTIFIER ASSIGN expression
        { free($1); free($3); }
    | IDENTIFIER LBRACKET CONST_INT RBRACKET
        { free($1); free($3); }
    | IDENTIFIER LBRACKET RBRACKET
        { free($1); }
    ;

/* ================================================================== */
/*  FUNCTION DEFINITION                                                 */
/* ================================================================== */
function_definition
    : type_specifier IDENTIFIER LPAREN param_list RPAREN compound_statement
        { printf("[Func] %s %s(...)\n", $1, $2); free($1); free($2); }
    | type_specifier IDENTIFIER LPAREN RPAREN compound_statement
        { printf("[Func] %s %s()\n", $1, $2); free($1); free($2); }
    | type_specifier IDENTIFIER LPAREN param_list RPAREN SEMICOLON
        { printf("[Func] Forward: %s %s(...)\n", $1, $2); free($1); free($2); }
    | type_specifier IDENTIFIER LPAREN RPAREN SEMICOLON
        { printf("[Func] Forward: %s %s()\n", $1, $2); free($1); free($2); }
    /* Constructor / destructor form: ClassName::method */
    | type_specifier IDENTIFIER SCOPE_RES IDENTIFIER LPAREN param_list RPAREN compound_statement
        { printf("[Func] %s::%s(...)\n", $2, $4); free($1); free($2); free($4); }
    | type_specifier IDENTIFIER SCOPE_RES IDENTIFIER LPAREN RPAREN compound_statement
        { printf("[Func] %s::%s()\n", $2, $4); free($1); free($2); free($4); }
    ;

param_list
    : param
    | param_list COMMA param
    ;

param
    : type_specifier IDENTIFIER
        { free($1); free($2); }
    | type_specifier IDENTIFIER ASSIGN expression
        { free($1); free($2); free($4); }     /* default parameter */
    | type_specifier IDENTIFIER LBRACKET RBRACKET
        { free($1); free($2); }
    | type_specifier
        { free($1); }
    ;

/* ================================================================== */
/*  COMPOUND STATEMENT                                                  */
/* ================================================================== */
compound_statement
    : LBRACE statement_list RBRACE
    | LBRACE RBRACE
    ;

statement_list
    : statement
    | statement_list statement
    ;

/* ================================================================== */
/*  STATEMENTS                                                          */
/* ================================================================== */
statement
    : var_declaration
    | expression_statement
    | compound_statement
    | if_statement
    | switch_statement
    | while_statement
    | do_while_statement
    | for_statement
    | cout_statement
    | cin_statement
    | return_statement
    | break_statement
    | continue_statement
    ;

expression_statement
    : expression SEMICOLON { free($1); }
    | SEMICOLON
    ;

/* ------------------------------------------------------------------ */
/*  IF / ELSE                                                           */
/* ------------------------------------------------------------------ */
if_statement
    : KEYWORD_IF LPAREN expression RPAREN statement
        { printf("[Stmt] if (%s)\n", $3); free($3); }
    | KEYWORD_IF LPAREN expression RPAREN statement KEYWORD_ELSE statement
        { printf("[Stmt] if-else (%s)\n", $3); free($3); }
    ;

/* ------------------------------------------------------------------ */
/*  SWITCH                                                              */
/* ------------------------------------------------------------------ */
switch_statement
    : KEYWORD_SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE
        { printf("[Stmt] switch (%s)\n", $3); free($3); }
    ;

case_list
    : case_clause
    | case_list case_clause
    ;

case_clause
    : KEYWORD_CASE expression COLON statement_list { free($2); }
    | KEYWORD_CASE expression COLON               { free($2); }
    | KEYWORD_DEFAULT COLON statement_list
    | KEYWORD_DEFAULT COLON
    ;

/* ------------------------------------------------------------------ */
while_statement
    : KEYWORD_WHILE LPAREN expression RPAREN statement
        { printf("[Stmt] while (%s)\n", $3); free($3); }
    ;

do_while_statement
    : KEYWORD_DO statement KEYWORD_WHILE LPAREN expression RPAREN SEMICOLON
        { printf("[Stmt] do-while (%s)\n", $5); free($5); }
    ;

/* ------------------------------------------------------------------ */
for_statement
    : KEYWORD_FOR LPAREN for_init SEMICOLON for_cond SEMICOLON for_update RPAREN statement
        { printf("[Stmt] for(...)\n"); }
    ;

for_init
    : var_declaration_inline
    | expression { free($1); }
    | /* empty */
    ;

var_declaration_inline
    : type_specifier IDENTIFIER ASSIGN expression
        { free($1); free($2); free($4); }
    | type_specifier IDENTIFIER
        { free($1); free($2); }
    ;

for_cond
    : expression { free($1); }
    | /* empty */
    ;

for_update
    : expression { free($1); }
    | /* empty */
    ;

/* ------------------------------------------------------------------ */
/*  cout << expr << endl;                                               */
/* ------------------------------------------------------------------ */
cout_statement
    : KEYWORD_COUT STREAM_OUT stream_output_chain SEMICOLON
        { printf("[Stmt] cout << ...\n"); free($3); }
    ;

stream_output_chain
    : expression
        { $$ = $1; }
    | KEYWORD_ENDL
        { $$ = "endl"; }
    | stream_output_chain STREAM_OUT expression
        { $$ = $1; free($3); }
    | stream_output_chain STREAM_OUT KEYWORD_ENDL
        { $$ = $1; }
    ;

/* ------------------------------------------------------------------ */
/*  cin >> var;                                                         */
/* ------------------------------------------------------------------ */
cin_statement
    : KEYWORD_CIN STREAM_IN cin_input_chain SEMICOLON
        { printf("[Stmt] cin >> ...\n"); }
    ;

cin_input_chain
    : IDENTIFIER { free($1); }
    | cin_input_chain STREAM_IN IDENTIFIER { free($3); }
    ;

/* ------------------------------------------------------------------ */
return_statement
    : KEYWORD_RETURN expression SEMICOLON
        { printf("[Stmt] return %s\n", $2); free($2); }
    | KEYWORD_RETURN SEMICOLON
        { printf("[Stmt] return;\n"); }
    ;

break_statement    : KEYWORD_BREAK SEMICOLON    { printf("[Stmt] break;\n"); } ;
continue_statement : KEYWORD_CONTINUE SEMICOLON { printf("[Stmt] continue;\n"); } ;

/* ================================================================== */
/*  EXPRESSIONS                                                         */
/* ================================================================== */

expression
    : assignment_expr { $$ = $1; }
    ;

assignment_expr
    : logical_or_expr { $$ = $1; }
    | unary_expr ASSIGN          assignment_expr { $$ = $1; }
    | unary_expr OP_PLUS_ASSIGN  assignment_expr { $$ = $1; }
    | unary_expr OP_MINUS_ASSIGN assignment_expr { $$ = $1; }
    | unary_expr OP_MUL_ASSIGN   assignment_expr { $$ = $1; }
    | unary_expr OP_DIV_ASSIGN   assignment_expr { $$ = $1; }
    ;

logical_or_expr
    : logical_and_expr { $$ = $1; }
    | logical_or_expr OP_OR logical_and_expr { $$ = "||_expr"; free($1); free($3); }
    ;

logical_and_expr
    : equality_expr { $$ = $1; }
    | logical_and_expr OP_AND equality_expr { $$ = "&&_expr"; free($1); free($3); }
    ;

equality_expr
    : relational_expr { $$ = $1; }
    | equality_expr OP_EQ  relational_expr { $$ = "==_expr"; free($1); free($3); }
    | equality_expr OP_NEQ relational_expr { $$ = "!=_expr"; free($1); free($3); }
    ;

relational_expr
    : additive_expr { $$ = $1; }
    | relational_expr '<'    additive_expr { $$ = "<_expr";  free($1); free($3); }
    | relational_expr '>'    additive_expr { $$ = ">_expr";  free($1); free($3); }
    | relational_expr OP_LEQ additive_expr { $$ = "<=_expr"; free($1); free($3); }
    | relational_expr OP_GEQ additive_expr { $$ = ">=_expr"; free($1); free($3); }
    ;

additive_expr
    : multiplicative_expr { $$ = $1; }
    | additive_expr '+' multiplicative_expr { $$ = "+_expr"; free($1); free($3); }
    | additive_expr '-' multiplicative_expr { $$ = "-_expr"; free($1); free($3); }
    ;

multiplicative_expr
    : unary_expr { $$ = $1; }
    | multiplicative_expr '*' unary_expr { $$ = "*_expr"; free($1); free($3); }
    | multiplicative_expr '/' unary_expr { $$ = "/_expr"; free($1); free($3); }
    | multiplicative_expr '%' unary_expr { $$ = "%_expr"; free($1); free($3); }
    ;

unary_expr
    : postfix_expr       { $$ = $1; }
    | OP_INC unary_expr  { $$ = "++x"; free($2); }
    | OP_DEC unary_expr  { $$ = "--x"; free($2); }
    | '!' unary_expr     { $$ = "!expr"; free($2); }
    | '-' unary_expr     { $$ = "-expr"; free($2); }
    | '&' unary_expr     { $$ = "&expr"; free($2); }
    | '*' unary_expr     { $$ = "*expr"; free($2); }    /* dereference */
    | KEYWORD_NEW type_specifier LPAREN RPAREN
        { $$ = "new_obj"; free($2); }
    | KEYWORD_NEW type_specifier LBRACKET expression RBRACKET
        { $$ = "new_arr"; free($2); free($4); }
    ;

postfix_expr
    : primary_expr { $$ = $1; }
    | postfix_expr OP_INC  { $$ = "x++"; free($1); }
    | postfix_expr OP_DEC  { $$ = "x--"; free($1); }
    | postfix_expr LBRACKET expression RBRACKET
        { $$ = "arr_access"; free($1); free($3); }
    | postfix_expr DOT IDENTIFIER
        { $$ = $1; free($3); }
    | IDENTIFIER SCOPE_RES IDENTIFIER
        { $$ = $1; free($3); }
    | IDENTIFIER LPAREN argument_list RPAREN
        { printf("[Expr] Call: %s(...)\n", $1); $$ = $1; free($3); }
    | IDENTIFIER LPAREN RPAREN
        { printf("[Expr] Call: %s()\n", $1); $$ = $1; }
    | postfix_expr DOT IDENTIFIER LPAREN argument_list RPAREN
        { $$ = $1; free($3); free($5); }
    | postfix_expr DOT IDENTIFIER LPAREN RPAREN
        { $$ = $1; free($3); }
    ;

primary_expr
    : IDENTIFIER       { $$ = $1; }
    | CONST_INT        { $$ = $1; }
    | CONST_FLOAT      { $$ = $1; }
    | STRING_LITERAL   { $$ = $1; }
    | CHAR_LITERAL     { $$ = $1; }
    | CONST_BOOL_TRUE  { $$ = $1; }
    | CONST_BOOL_FALSE { $$ = $1; }
    | KEYWORD_THIS     { $$ = "this"; }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

argument_list
    : expression
        { $$ = $1; }
    | argument_list COMMA expression
        { $$ = $1; free($3); }
    ;

%%

/* ------------------------------------------------------------------ */
/*  Standalone test driver                                              */
/*  Compile:  bison -d -o parser_cpp.tab.c parser_cpp.y               */
/*            flex  -o lex.yy_cpp.c lexer_cpp.l                       */
/*            g++ -o test_cpp parser_cpp.tab.c lex.yy_cpp.c           */
/*  Run:      ./test_cpp ../../examples/hello.cpp                      */
#ifdef STANDALONE_MAIN
int main(int argc, char* argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Error: cannot open file '%s'\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    printf("=== PolyCompile — C++ Flex/Bison Parser ===\n");
    yyparse();

    if (cpp_syntax_errors == 0)
        printf("\n[OK] Parsed successfully with 0 syntax errors.\n");
    else
        printf("\n[FAIL] %d syntax error(s) found.\n", cpp_syntax_errors);

    if (argc > 1) fclose(yyin);
    return (cpp_syntax_errors > 0) ? 1 : 0;
}
#endif
