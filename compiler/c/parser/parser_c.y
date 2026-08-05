%{
/*
 * parser_c.y  –  Bison Parser for C Language
 * PolyCompile Project
 *
 * Usage:
 *   bison -d -o parser_c.tab.c parser_c.y
 *   (Generates parser_c.tab.c and parser_c.tab.h)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/*  Connection to lexer                                                 */
/* ------------------------------------------------------------------ */
extern int  yylex(void);
extern int  c_line;
extern int  c_col;
extern char* yytext;
extern FILE* yyin;

int c_syntax_errors = 0;

void yyerror(const char* msg) {
    fprintf(stderr, "[Syntax Error] Line %d: %s (near '%s')\n",
            c_line, msg, yytext);
    c_syntax_errors++;
}

%}

/* ------------------------------------------------------------------ */
/*  Value types for semantic actions                                    */
/* ------------------------------------------------------------------ */
%union {
    char* string_val;   /* raw lexeme text  */
}

/* ------------------------------------------------------------------ */
/*  Token declarations  (must match lexer_c.l returns)                 */
/* ------------------------------------------------------------------ */

/* Preprocessor */
%token <string_val> HEADER_DIRECTIVE

/* Data-type keywords */
%token <string_val> KEYWORD_INT
%token <string_val> KEYWORD_FLOAT
%token <string_val> KEYWORD_CHAR
%token <string_val> KEYWORD_DOUBLE
%token <string_val> KEYWORD_BOOL
%token              KEYWORD_VOID

/* Control-flow keywords */
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

/* I/O keywords */
%token KEYWORD_PRINTF
%token KEYWORD_SCANF

/* Boolean constants */
%token <string_val> CONST_BOOL_TRUE
%token <string_val> CONST_BOOL_FALSE

/* Literals */
%token <string_val> CONST_INT
%token <string_val> CONST_FLOAT
%token <string_val> STRING_LITERAL
%token <string_val> CHAR_LITERAL

/* Identifier */
%token <string_val> IDENTIFIER

/* Multi-char operators */
%token OP_EQ OP_NEQ OP_LEQ OP_GEQ
%token OP_AND OP_OR
%token OP_INC OP_DEC
%token OP_PLUS_ASSIGN OP_MINUS_ASSIGN OP_MUL_ASSIGN OP_DIV_ASSIGN

/* Assignment */
%token ASSIGN

/* Delimiters */
%token SEMICOLON COMMA COLON
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

/* ------------------------------------------------------------------ */
/*  Non-terminal types                                                  */
/* ------------------------------------------------------------------ */
%type <string_val> type_specifier
%type <string_val> expression assignment_expr logical_or_expr logical_and_expr
%type <string_val> equality_expr relational_expr additive_expr multiplicative_expr
%type <string_val> unary_expr postfix_expr primary_expr
%type <string_val> argument_list

/* ------------------------------------------------------------------ */
/*  Operator precedence (lowest → highest)                             */
/* ------------------------------------------------------------------ */
%right ASSIGN OP_PLUS_ASSIGN OP_MINUS_ASSIGN OP_MUL_ASSIGN OP_DIV_ASSIGN
%left  OP_OR
%left  OP_AND
%left  OP_EQ OP_NEQ
%left  '<' '>' OP_LEQ OP_GEQ
%left  '+' '-'
%left  '*' '/' '%'
%right '!' OP_INC OP_DEC
%left  LPAREN RPAREN LBRACKET RBRACKET

/* ------------------------------------------------------------------ */
/*  Grammar entry point                                                 */
/* ------------------------------------------------------------------ */
%start program

%%

/* ================================================================== */
/*  TOP LEVEL                                                           */
/* ================================================================== */

program
    : declaration_list
        { printf("[Parse] C program parsed successfully.\n"); }
    ;

declaration_list
    : declaration
    | declaration_list declaration
    ;

declaration
    : header_directive
    | function_definition
    | var_declaration
    ;

/* ------------------------------------------------------------------ */
/*  Preprocessor directive                                              */
/* ------------------------------------------------------------------ */
header_directive
    : HEADER_DIRECTIVE
        { printf("[Token] Header directive: %s\n", $1); free($1); }
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
    | KEYWORD_VOID   { $$ = "void"; }
    ;

/* ================================================================== */
/*  VARIABLE DECLARATION                                                */
/* ================================================================== */
var_declaration
    : type_specifier var_init_list SEMICOLON
        { printf("[Decl] Variable declaration: type=%s\n", $1); }
    ;

var_init_list
    : var_init
    | var_init_list COMMA var_init
    ;

var_init
    : IDENTIFIER
        { printf("[Decl] Variable: %s\n", $1); free($1); }
    | IDENTIFIER ASSIGN expression
        { printf("[Decl] Variable: %s (with initializer)\n", $1); free($1); }
    | IDENTIFIER LBRACKET CONST_INT RBRACKET
        { printf("[Decl] Array: %s[%s]\n", $1, $3); free($1); free($3); }
    | IDENTIFIER LBRACKET RBRACKET
        { printf("[Decl] Array: %s[]\n", $1); free($1); }
    ;

/* ================================================================== */
/*  FUNCTION DEFINITION                                                 */
/* ================================================================== */
function_definition
    : type_specifier IDENTIFIER LPAREN param_list RPAREN compound_statement
        { printf("[Func] Function: %s %s(...)\n", $1, $2); free($1); free($2); }
    | type_specifier IDENTIFIER LPAREN RPAREN compound_statement
        { printf("[Func] Function: %s %s()\n", $1, $2); free($1); free($2); }
    /* Forward declarations */
    | type_specifier IDENTIFIER LPAREN param_list RPAREN SEMICOLON
        { printf("[Func] Forward decl: %s %s(...)\n", $1, $2); free($1); free($2); }
    | type_specifier IDENTIFIER LPAREN RPAREN SEMICOLON
        { printf("[Func] Forward decl: %s %s()\n", $1, $2); free($1); free($2); }
    ;

param_list
    : param
    | param_list COMMA param
    ;

param
    : type_specifier IDENTIFIER
        { printf("[Param] %s %s\n", $1, $2); free($1); free($2); }
    | type_specifier IDENTIFIER LBRACKET RBRACKET
        { printf("[Param] %s %s[]\n", $1, $2); free($1); free($2); }
    | type_specifier
        { printf("[Param] %s (unnamed)\n", $1); free($1); }
    ;

/* ================================================================== */
/*  COMPOUND STATEMENT  { ... }                                        */
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
    | printf_statement
    | scanf_statement
    | return_statement
    | break_statement
    | continue_statement
    ;

/* ------------------------------------------------------------------ */
expression_statement
    : expression SEMICOLON
        { printf("[Stmt] Expression statement: %s\n", $1); free($1); }
    | SEMICOLON   /* empty statement */
    ;

/* ------------------------------------------------------------------ */
/*  IF / ELSE                                                           */
/* ------------------------------------------------------------------ */
if_statement
    : KEYWORD_IF LPAREN expression RPAREN statement
        { printf("[Stmt] if (%s)\n", $3); free($3); }
    | KEYWORD_IF LPAREN expression RPAREN statement KEYWORD_ELSE statement
        { printf("[Stmt] if (%s) ... else ...\n", $3); free($3); }
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
    : KEYWORD_CASE expression COLON statement_list
        { printf("[Stmt] case %s:\n", $2); free($2); }
    | KEYWORD_CASE expression COLON
        { free($2); }
    | KEYWORD_DEFAULT COLON statement_list
        { printf("[Stmt] default:\n"); }
    | KEYWORD_DEFAULT COLON
    ;

/* ------------------------------------------------------------------ */
/*  WHILE                                                               */
/* ------------------------------------------------------------------ */
while_statement
    : KEYWORD_WHILE LPAREN expression RPAREN statement
        { printf("[Stmt] while (%s)\n", $3); free($3); }
    ;

/* ------------------------------------------------------------------ */
/*  DO-WHILE                                                            */
/* ------------------------------------------------------------------ */
do_while_statement
    : KEYWORD_DO statement KEYWORD_WHILE LPAREN expression RPAREN SEMICOLON
        { printf("[Stmt] do...while (%s)\n", $5); free($5); }
    ;

/* ------------------------------------------------------------------ */
/*  FOR                                                                 */
/* ------------------------------------------------------------------ */
for_statement
    : KEYWORD_FOR LPAREN for_init SEMICOLON for_cond SEMICOLON for_update RPAREN statement
        { printf("[Stmt] for(...)\n"); }
    ;

for_init
    : var_declaration_inline
    | expression
        { free($1); }
    | /* empty */
    ;

/* Inline var decl inside for-init (no trailing semicolon) */
var_declaration_inline
    : type_specifier IDENTIFIER ASSIGN expression
        { printf("[Decl] for-init: %s %s\n", $1, $2); free($1); free($2); free($4); }
    | type_specifier IDENTIFIER
        { printf("[Decl] for-init: %s %s\n", $1, $2); free($1); free($2); }
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
/*  PRINTF                                                              */
/* ------------------------------------------------------------------ */
printf_statement
    : KEYWORD_PRINTF LPAREN argument_list RPAREN SEMICOLON
        { printf("[Stmt] printf(...)\n"); free($3); }
    | KEYWORD_PRINTF LPAREN RPAREN SEMICOLON
        { printf("[Stmt] printf()\n"); }
    ;

/* ------------------------------------------------------------------ */
/*  SCANF                                                               */
/* ------------------------------------------------------------------ */
scanf_statement
    : KEYWORD_SCANF LPAREN argument_list RPAREN SEMICOLON
        { printf("[Stmt] scanf(...)\n"); free($3); }
    ;

/* ------------------------------------------------------------------ */
/*  RETURN                                                              */
/* ------------------------------------------------------------------ */
return_statement
    : KEYWORD_RETURN expression SEMICOLON
        { printf("[Stmt] return %s\n", $2); free($2); }
    | KEYWORD_RETURN SEMICOLON
        { printf("[Stmt] return;\n"); }
    ;

/* ------------------------------------------------------------------ */
break_statement
    : KEYWORD_BREAK SEMICOLON
        { printf("[Stmt] break;\n"); }
    ;

continue_statement
    : KEYWORD_CONTINUE SEMICOLON
        { printf("[Stmt] continue;\n"); }
    ;

/* ================================================================== */
/*  EXPRESSIONS (precedence already handled by %left/%right above)     */
/* ================================================================== */

expression
    : assignment_expr { $$ = $1; }
    ;

assignment_expr
    : logical_or_expr { $$ = $1; }
    | unary_expr ASSIGN      assignment_expr { $$ = $1; /* simplified */ }
    | unary_expr OP_PLUS_ASSIGN  assignment_expr { $$ = $1; }
    | unary_expr OP_MINUS_ASSIGN assignment_expr { $$ = $1; }
    | unary_expr OP_MUL_ASSIGN   assignment_expr { $$ = $1; }
    | unary_expr OP_DIV_ASSIGN   assignment_expr { $$ = $1; }
    ;

logical_or_expr
    : logical_and_expr { $$ = $1; }
    | logical_or_expr OP_OR logical_and_expr
        { $$ = "||_expr"; free($1); free($3); }
    ;

logical_and_expr
    : equality_expr { $$ = $1; }
    | logical_and_expr OP_AND equality_expr
        { $$ = "&&_expr"; free($1); free($3); }
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
    : postfix_expr        { $$ = $1; }
    | OP_INC unary_expr   { $$ = "++x"; free($2); }
    | OP_DEC unary_expr   { $$ = "--x"; free($2); }
    | '!' unary_expr      { $$ = "!expr"; free($2); }
    | '-' unary_expr      { $$ = "-expr"; free($2); }
    | '&' unary_expr      { $$ = "&expr"; free($2); }
    ;

postfix_expr
    : primary_expr { $$ = $1; }
    | postfix_expr OP_INC  { $$ = "x++"; free($1); }
    | postfix_expr OP_DEC  { $$ = "x--"; free($1); }
    | postfix_expr LBRACKET expression RBRACKET
        { $$ = "arr_access"; free($1); free($3); }
    | IDENTIFIER LPAREN argument_list RPAREN
        { printf("[Expr] Call: %s(...)\n", $1); $$ = $1; free($3); }
    | IDENTIFIER LPAREN RPAREN
        { printf("[Expr] Call: %s()\n", $1); $$ = $1; }
    ;

primary_expr
    : IDENTIFIER      { $$ = $1; }
    | CONST_INT       { $$ = $1; }
    | CONST_FLOAT     { $$ = $1; }
    | STRING_LITERAL  { $$ = $1; }
    | CHAR_LITERAL    { $$ = $1; }
    | CONST_BOOL_TRUE  { $$ = $1; }
    | CONST_BOOL_FALSE { $$ = $1; }
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
/*  main() – standalone test driver                                     */
/*  Compile:  bison -d -o parser_c.tab.c parser_c.y                   */
/*            flex  -o lex.yy_c.c  lexer_c.l                          */
/*            g++ -o test_c parser_c.tab.c lex.yy_c.c                 */
/*  Run:      ./test_c < ../../examples/hello.c                        */
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

    printf("=== PolyCompile — C Flex/Bison Parser ===\n");
    yyparse();

    if (c_syntax_errors == 0)
        printf("\n[OK] Parsed successfully with 0 syntax errors.\n");
    else
        printf("\n[FAIL] %d syntax error(s) found.\n", c_syntax_errors);

    if (argc > 1) fclose(yyin);
    return (c_syntax_errors > 0) ? 1 : 0;
}
#endif
