/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ANNOTATION = 258,
     KEYWORD_CLASS = 259,
     KEYWORD_INTERFACE = 260,
     KEYWORD_EXTENDS = 261,
     KEYWORD_IMPLEMENTS = 262,
     KEYWORD_PUBLIC = 263,
     KEYWORD_PRIVATE = 264,
     KEYWORD_PROTECTED = 265,
     KEYWORD_STATIC = 266,
     KEYWORD_FINAL = 267,
     KEYWORD_ABSTRACT = 268,
     KEYWORD_NEW = 269,
     KEYWORD_THIS = 270,
     KEYWORD_SUPER = 271,
     KEYWORD_INSTANCEOF = 272,
     KEYWORD_THROWS = 273,
     KEYWORD_THROW = 274,
     KEYWORD_TRY = 275,
     KEYWORD_CATCH = 276,
     KEYWORD_FINALLY = 277,
     KEYWORD_INT = 278,
     KEYWORD_FLOAT = 279,
     KEYWORD_DOUBLE = 280,
     KEYWORD_CHAR = 281,
     KEYWORD_BOOLEAN = 282,
     KEYWORD_BYTE = 283,
     KEYWORD_SHORT = 284,
     KEYWORD_LONG = 285,
     KEYWORD_STRING = 286,
     KEYWORD_VOID = 287,
     KEYWORD_IF = 288,
     KEYWORD_ELSE = 289,
     KEYWORD_WHILE = 290,
     KEYWORD_DO = 291,
     KEYWORD_FOR = 292,
     KEYWORD_SWITCH = 293,
     KEYWORD_CASE = 294,
     KEYWORD_DEFAULT = 295,
     KEYWORD_BREAK = 296,
     KEYWORD_CONTINUE = 297,
     KEYWORD_RETURN = 298,
     CONST_BOOL_TRUE = 299,
     CONST_BOOL_FALSE = 300,
     CONST_NULL = 301,
     CONST_INT = 302,
     CONST_FLOAT = 303,
     STRING_LITERAL = 304,
     CHAR_LITERAL = 305,
     IDENTIFIER = 306,
     OP_EQ = 307,
     OP_NEQ = 308,
     OP_LEQ = 309,
     OP_GEQ = 310,
     OP_AND = 311,
     OP_OR = 312,
     OP_INC = 313,
     OP_DEC = 314,
     OP_PLUS_ASSIGN = 315,
     OP_MINUS_ASSIGN = 316,
     OP_MUL_ASSIGN = 317,
     OP_DIV_ASSIGN = 318,
     ASSIGN = 319,
     SEMICOLON = 320,
     COMMA = 321,
     COLON = 322,
     DOT = 323,
     LPAREN = 324,
     RPAREN = 325,
     LBRACE = 326,
     RBRACE = 327,
     LBRACKET = 328,
     RBRACKET = 329
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 34 "compiler/java/parser/parser_java.y"

    char* string_val;



/* Line 1685 of yacc.c  */
#line 131 "compiler/java/parser/parser_java.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


