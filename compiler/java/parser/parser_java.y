%{
/*
 * parser_java.y  –  Bison Parser for Java Language
 * PolyCompile Project
 *
 * Usage:
 *   bison -d -o parser_java.tab.c parser_java.y
 *   (Generates parser_java.tab.c and parser_java.tab.h)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int  yylex(void);
extern int  java_line;
extern int  java_col;
extern char* yytext;
extern FILE* yyin;

int java_syntax_errors = 0;

void yyerror(const char* msg) {
    fprintf(stderr, "[Syntax Error] Line %d: %s (near '%s')\n",
            java_line, msg, yytext);
    java_syntax_errors++;
}

%}


/*  Value types                                                         */

%union {
    char* string_val;
}


/*  Token declarations                                                  */


/* Annotation */
%token <string_val> ANNOTATION

/* Class / OOP keywords */
%token KEYWORD_CLASS
%token KEYWORD_INTERFACE
%token KEYWORD_EXTENDS
%token KEYWORD_IMPLEMENTS
%token KEYWORD_PUBLIC
%token KEYWORD_PRIVATE
%token KEYWORD_PROTECTED
%token KEYWORD_STATIC
%token KEYWORD_FINAL
%token KEYWORD_ABSTRACT
%token KEYWORD_NEW
%token KEYWORD_THIS
%token KEYWORD_SUPER
%token KEYWORD_INSTANCEOF
%token KEYWORD_THROWS
%token KEYWORD_THROW
%token KEYWORD_TRY
%token KEYWORD_CATCH
%token KEYWORD_FINALLY

/* Primitive types */
%token <string_val> KEYWORD_INT
%token <string_val> KEYWORD_FLOAT
%token <string_val> KEYWORD_DOUBLE
%token <string_val> KEYWORD_CHAR
%token <string_val> KEYWORD_BOOLEAN
%token <string_val> KEYWORD_BYTE
%token <string_val> KEYWORD_SHORT
%token <string_val> KEYWORD_LONG
%token <string_val> KEYWORD_STRING
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

/* Constants */
%token <string_val> CONST_BOOL_TRUE
%token <string_val> CONST_BOOL_FALSE
%token <string_val> CONST_NULL
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
%token ASSIGN

/* Delimiters */
%token SEMICOLON COMMA COLON DOT
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET


/*  Non-terminal types                                                  */

%type <string_val> type_specifier
%type <string_val> expression assignment_expr logical_or_expr logical_and_expr
%type <string_val> equality_expr relational_expr additive_expr multiplicative_expr
%type <string_val> unary_expr postfix_expr primary_expr
%type <string_val> argument_list


/*  Operator precedence                                                 */

%right ASSIGN OP_PLUS_ASSIGN OP_MINUS_ASSIGN OP_MUL_ASSIGN OP_DIV_ASSIGN
%left  OP_OR
%left  OP_AND
%left  OP_EQ OP_NEQ
%left  '<' '>' OP_LEQ OP_GEQ
%left  '+' '-'
%left  '*' '/' '%'
%right '!' OP_INC OP_DEC KEYWORD_NEW
%left  LPAREN RPAREN LBRACKET RBRACKET DOT

%start program

%%


/*  TOP LEVEL  – Java file = optional package + imports + class decls  */


program
    : class_list
        { printf("[Parse] Java program parsed successfully.\n"); }
    ;

class_list
    : class_declaration
    | class_list class_declaration
    ;

/*  CLASS DECLARATION                                                   */


class_declaration
    : annotation_list modifiers KEYWORD_CLASS IDENTIFIER class_body
        { printf("[Class] class %s\n", $4); free($4); }
    | annotation_list modifiers KEYWORD_CLASS IDENTIFIER KEYWORD_EXTENDS IDENTIFIER class_body
        { printf("[Class] class %s extends %s\n", $4, $6); free($4); free($6); }
    | annotation_list modifiers KEYWORD_CLASS IDENTIFIER KEYWORD_IMPLEMENTS id_list class_body
        { printf("[Class] class %s implements ...\n", $4); free($4); }
    | annotation_list modifiers KEYWORD_INTERFACE IDENTIFIER class_body
        { printf("[Interface] interface %s\n", $4); free($4); }
    ;

annotation_list
    : ANNOTATION { free($1); }
    | annotation_list ANNOTATION { free($2); }
    | /* empty */
    ;

modifiers
    : modifier
    | modifiers modifier
    | /* empty */
    ;

modifier
    : KEYWORD_PUBLIC
    | KEYWORD_PRIVATE
    | KEYWORD_PROTECTED
    | KEYWORD_STATIC
    | KEYWORD_FINAL
    | KEYWORD_ABSTRACT
    ;

id_list
    : IDENTIFIER { free($1); }
    | id_list COMMA IDENTIFIER { free($3); }
    ;

class_body
    : LBRACE class_member_list RBRACE
    | LBRACE RBRACE
    ;

class_member_list
    : class_member
    | class_member_list class_member
    ;

class_member
    : annotation_list modifiers method_definition
    | annotation_list modifiers field_declaration
    | annotation_list modifiers constructor_definition
    ;


/*  FIELD DECLARATION                                                   */


field_declaration
    : type_specifier var_init_list SEMICOLON
        { printf("[Field] type=%s\n", $1); }
    | type_specifier IDENTIFIER LBRACKET RBRACKET var_init_list SEMICOLON
        { printf("[Field] array type=%s\n", $1); }
    ;


/*  CONSTRUCTOR                                                         */


constructor_definition
    : IDENTIFIER LPAREN param_list RPAREN compound_statement
        { printf("[Constructor] %s(...)\n", $1); free($1); }
    | IDENTIFIER LPAREN RPAREN compound_statement
        { printf("[Constructor] %s()\n", $1); free($1); }
    ;


/*  METHOD DEFINITION                                                   */


method_definition
    : type_specifier IDENTIFIER LPAREN param_list RPAREN compound_statement
        { printf("[Method] %s %s(...)\n", $1, $2); free($1); free($2); }
    | type_specifier IDENTIFIER LPAREN RPAREN compound_statement
        { printf("[Method] %s %s()\n", $1, $2); free($1); free($2); }
    | KEYWORD_VOID IDENTIFIER LPAREN param_list RPAREN compound_statement
        { printf("[Method] void %s(...)\n", $2); free($2); }
    | KEYWORD_VOID IDENTIFIER LPAREN RPAREN compound_statement
        { printf("[Method] void %s()\n", $2); free($2); }
    /* main method */
    | KEYWORD_VOID IDENTIFIER LPAREN KEYWORD_STRING LBRACKET RBRACKET IDENTIFIER RPAREN compound_statement
        { printf("[Method] void %s(String[] %s)\n", $2, $7); free($2); free($7); }
    | type_specifier IDENTIFIER LPAREN param_list RPAREN SEMICOLON
        { printf("[Method] abstract/interface: %s %s(...)\n", $1, $2); free($1); free($2); }
    | type_specifier IDENTIFIER LPAREN RPAREN SEMICOLON
        { printf("[Method] abstract/interface: %s %s()\n", $1, $2); free($1); free($2); }
    ;


/*  PARAMETERS                                                          */


param_list
    : param
    | param_list COMMA param
    ;

param
    : type_specifier IDENTIFIER
        { free($1); free($2); }
    | type_specifier IDENTIFIER LBRACKET RBRACKET
        { free($1); free($2); }
    | type_specifier
        { free($1); }
    ;

/*  TYPE SPECIFIER                                                      */


type_specifier
    : KEYWORD_INT     { $$ = $1; }
    | KEYWORD_FLOAT   { $$ = $1; }
    | KEYWORD_DOUBLE  { $$ = $1; }
    | KEYWORD_CHAR    { $$ = $1; }
    | KEYWORD_BOOLEAN { $$ = $1; }
    | KEYWORD_BYTE    { $$ = $1; }
    | KEYWORD_SHORT   { $$ = $1; }
    | KEYWORD_LONG    { $$ = $1; }
    | KEYWORD_STRING  { $$ = $1; }
    | KEYWORD_VOID    { $$ = "void"; }
    | IDENTIFIER      { $$ = $1; }  /* user-defined class type */
    ;


/*  VARIABLE DECLARATION (inside methods)                               */


var_declaration
    : type_specifier var_init_list SEMICOLON
        { printf("[Decl] type=%s\n", $1); }
    | type_specifier IDENTIFIER LBRACKET RBRACKET SEMICOLON
        { printf("[Decl] array %s %s[]\n", $1, $2); free($1); free($2); }
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
    | IDENTIFIER LBRACKET RBRACKET
        { free($1); }
    | IDENTIFIER LBRACKET RBRACKET ASSIGN expression
        { free($1); free($5); }
    ;


/*  COMPOUND STATEMENT                                                  */


compound_statement
    : LBRACE statement_list RBRACE
    | LBRACE RBRACE
    ;

statement_list
    : statement
    | statement_list statement
    ;


/*  STATEMENTS                                                          */


statement
    : var_declaration
    | expression_statement
    | compound_statement
    | if_statement
    | switch_statement
    | while_statement
    | do_while_statement
    | for_statement
    | for_each_statement
    | sysout_statement
    | return_statement
    | break_statement
    | continue_statement
    | throw_statement
    | try_statement
    ;

expression_statement
    : expression SEMICOLON { free($1); }
    | SEMICOLON
    ;


/*  IF / ELSE                                                           */

if_statement
    : KEYWORD_IF LPAREN expression RPAREN statement
        { printf("[Stmt] if (%s)\n", $3); free($3); }
    | KEYWORD_IF LPAREN expression RPAREN statement KEYWORD_ELSE statement
        { printf("[Stmt] if-else (%s)\n", $3); free($3); }
    ;


/*  SWITCH                                                              */

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


while_statement
    : KEYWORD_WHILE LPAREN expression RPAREN statement
        { printf("[Stmt] while (%s)\n", $3); free($3); }
    ;

do_while_statement
    : KEYWORD_DO statement KEYWORD_WHILE LPAREN expression RPAREN SEMICOLON
        { printf("[Stmt] do-while (%s)\n", $5); free($5); }
    ;


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


/*  Enhanced for-each: for (Type var : collection)                     */

for_each_statement
    : KEYWORD_FOR LPAREN type_specifier IDENTIFIER COLON expression RPAREN statement
        { printf("[Stmt] for-each: %s %s : ...\n", $3, $4); free($3); free($4); free($6); }
    ;


/*  System.out.println / System.out.print                              */

sysout_statement
    : IDENTIFIER DOT IDENTIFIER DOT IDENTIFIER LPAREN argument_list RPAREN SEMICOLON
        { printf("[Stmt] System.out.println/print(...)\n"); free($1); free($3); free($5); free($7); }
    | IDENTIFIER DOT IDENTIFIER DOT IDENTIFIER LPAREN RPAREN SEMICOLON
        { printf("[Stmt] System.out.println()\n"); free($1); free($3); free($5); }
    ;


return_statement
    : KEYWORD_RETURN expression SEMICOLON
        { printf("[Stmt] return %s\n", $2); free($2); }
    | KEYWORD_RETURN SEMICOLON
        { printf("[Stmt] return;\n"); }
    ;

break_statement    : KEYWORD_BREAK SEMICOLON    { printf("[Stmt] break;\n"); } ;
continue_statement : KEYWORD_CONTINUE SEMICOLON { printf("[Stmt] continue;\n"); } ;

throw_statement
    : KEYWORD_THROW expression SEMICOLON
        { printf("[Stmt] throw ...\n"); free($2); }
    ;

try_statement
    : KEYWORD_TRY compound_statement catch_clause_list
    | KEYWORD_TRY compound_statement catch_clause_list KEYWORD_FINALLY compound_statement
    | KEYWORD_TRY compound_statement KEYWORD_FINALLY compound_statement
    ;

catch_clause_list
    : catch_clause
    | catch_clause_list catch_clause
    ;

catch_clause
    : KEYWORD_CATCH LPAREN type_specifier IDENTIFIER RPAREN compound_statement
        { printf("[Stmt] catch(%s %s)\n", $3, $4); free($3); free($4); }
    ;


/*  EXPRESSIONS                                                         */


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
    | relational_expr KEYWORD_INSTANCEOF IDENTIFIER
        { $$ = "instanceof_expr"; free($1); free($3); }
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
    | KEYWORD_NEW type_specifier LPAREN RPAREN
        { $$ = "new_obj"; free($2); }
    | KEYWORD_NEW type_specifier LPAREN argument_list RPAREN
        { $$ = "new_obj_args"; free($2); free($4); }
    | KEYWORD_NEW type_specifier LBRACKET expression RBRACKET
        { $$ = "new_arr"; free($2); free($4); }
    | LPAREN type_specifier RPAREN unary_expr
        { $$ = "cast_expr"; free($2); free($4); }   /* type cast */
    ;

postfix_expr
    : primary_expr { $$ = $1; }
    | postfix_expr OP_INC  { $$ = "x++"; free($1); }
    | postfix_expr OP_DEC  { $$ = "x--"; free($1); }
    | postfix_expr LBRACKET expression RBRACKET
        { $$ = "arr_access"; free($1); free($3); }
    | postfix_expr DOT IDENTIFIER
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
    : IDENTIFIER        { $$ = $1; }
    | CONST_INT         { $$ = $1; }
    | CONST_FLOAT       { $$ = $1; }
    | STRING_LITERAL    { $$ = $1; }
    | CHAR_LITERAL      { $$ = $1; }
    | CONST_BOOL_TRUE   { $$ = $1; }
    | CONST_BOOL_FALSE  { $$ = $1; }
    | CONST_NULL        { $$ = $1; }
    | KEYWORD_THIS      { $$ = "this"; }
    | KEYWORD_SUPER     { $$ = "super"; }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

argument_list
    : expression
        { $$ = $1; }
    | argument_list COMMA expression
        { $$ = $1; free($3); }
    ;

%%


/*  Standalone test driver                                              */
/*  Compile:  bison -d -o parser_java.tab.c parser_java.y             */
/*            flex  -o lex.yy_java.c lexer_java.l                     */
/*            g++ -o test_java parser_java.tab.c lex.yy_java.c        */
/*  Run:      ./test_java ../../examples/Hello.java                    */

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

    printf("=== PolyCompile — Java Flex/Bison Parser ===\n");
    yyparse();

    if (java_syntax_errors == 0)
        printf("\n[OK] Parsed successfully with 0 syntax errors.\n");
    else
        printf("\n[FAIL] %d syntax error(s) found.\n", java_syntax_errors);

    if (argc > 1) fclose(yyin);
    return (java_syntax_errors > 0) ? 1 : 0;
}
#endif
