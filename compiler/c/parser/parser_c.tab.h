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
     HEADER_DIRECTIVE = 258,
     KEYWORD_INT = 259,
     KEYWORD_FLOAT = 260,
     KEYWORD_CHAR = 261,
     KEYWORD_DOUBLE = 262,
     KEYWORD_BOOL = 263,
     KEYWORD_VOID = 264,
     KEYWORD_IF = 265,
     KEYWORD_ELSE = 266,
     KEYWORD_WHILE = 267,
     KEYWORD_DO = 268,
     KEYWORD_FOR = 269,
     KEYWORD_SWITCH = 270,
     KEYWORD_CASE = 271,
     KEYWORD_DEFAULT = 272,
     KEYWORD_BREAK = 273,
     KEYWORD_CONTINUE = 274,
     KEYWORD_RETURN = 275,
     KEYWORD_PRINTF = 276,
     KEYWORD_SCANF = 277,
     CONST_BOOL_TRUE = 278,
     CONST_BOOL_FALSE = 279,
     CONST_INT = 280,
     CONST_FLOAT = 281,
     STRING_LITERAL = 282,
     CHAR_LITERAL = 283,
     IDENTIFIER = 284,
     OP_EQ = 285,
     OP_NEQ = 286,
     OP_LEQ = 287,
     OP_GEQ = 288,
     OP_AND = 289,
     OP_OR = 290,
     OP_INC = 291,
     OP_DEC = 292,
     OP_PLUS_ASSIGN = 293,
     OP_MINUS_ASSIGN = 294,
     OP_MUL_ASSIGN = 295,
     OP_DIV_ASSIGN = 296,
     ASSIGN = 297,
     SEMICOLON = 298,
     COMMA = 299,
     COLON = 300,
     LPAREN = 301,
     RPAREN = 302,
     LBRACE = 303,
     RBRACE = 304,
     LBRACKET = 305,
     RBRACKET = 306
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 37 "compiler/c/parser/parser_c.y"

    char* string_val;   /* raw lexeme text  */



/* Line 1685 of yacc.c  */
#line 108 "compiler/c/parser/parser_c.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


