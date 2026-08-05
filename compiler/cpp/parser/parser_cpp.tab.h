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
     KEYWORD_USING = 259,
     KEYWORD_NAMESPACE = 260,
     KEYWORD_COUT = 261,
     KEYWORD_CIN = 262,
     KEYWORD_ENDL = 263,
     KEYWORD_CLASS = 264,
     KEYWORD_NEW = 265,
     KEYWORD_DELETE = 266,
     KEYWORD_THIS = 267,
     KEYWORD_PUBLIC = 268,
     KEYWORD_PRIVATE = 269,
     KEYWORD_PROTECTED = 270,
     KEYWORD_STRING = 271,
     KEYWORD_INT = 272,
     KEYWORD_FLOAT = 273,
     KEYWORD_CHAR = 274,
     KEYWORD_DOUBLE = 275,
     KEYWORD_BOOL = 276,
     KEYWORD_VOID = 277,
     KEYWORD_IF = 278,
     KEYWORD_ELSE = 279,
     KEYWORD_WHILE = 280,
     KEYWORD_DO = 281,
     KEYWORD_FOR = 282,
     KEYWORD_SWITCH = 283,
     KEYWORD_CASE = 284,
     KEYWORD_DEFAULT = 285,
     KEYWORD_BREAK = 286,
     KEYWORD_CONTINUE = 287,
     KEYWORD_RETURN = 288,
     CONST_BOOL_TRUE = 289,
     CONST_BOOL_FALSE = 290,
     CONST_INT = 291,
     CONST_FLOAT = 292,
     STRING_LITERAL = 293,
     CHAR_LITERAL = 294,
     IDENTIFIER = 295,
     OP_EQ = 296,
     OP_NEQ = 297,
     OP_LEQ = 298,
     OP_GEQ = 299,
     OP_AND = 300,
     OP_OR = 301,
     OP_INC = 302,
     OP_DEC = 303,
     OP_PLUS_ASSIGN = 304,
     OP_MINUS_ASSIGN = 305,
     OP_MUL_ASSIGN = 306,
     OP_DIV_ASSIGN = 307,
     STREAM_OUT = 308,
     STREAM_IN = 309,
     SCOPE_RES = 310,
     ASSIGN = 311,
     SEMICOLON = 312,
     COMMA = 313,
     COLON = 314,
     DOT = 315,
     LPAREN = 316,
     RPAREN = 317,
     LBRACE = 318,
     RBRACE = 319,
     LBRACKET = 320,
     RBRACKET = 321
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 34 "compiler/cpp/parser/parser_cpp.y"

    char* string_val;



/* Line 1685 of yacc.c  */
#line 123 "compiler/cpp/parser/parser_cpp.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


