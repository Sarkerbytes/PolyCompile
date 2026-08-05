/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "compiler/java/parser/parser_java.y"

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



/* Line 189 of yacc.c  */
#line 103 "compiler/java/parser/parser_java.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 34 "compiler/java/parser/parser_java.y"

    char* string_val;



/* Line 214 of yacc.c  */
#line 219 "compiler/java/parser/parser_java.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 231 "compiler/java/parser/parser_java.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   773

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  178
/* YYNRULES -- Number of states.  */
#define YYNSTATES  334

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   329

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    82,     2,     2,     2,    81,     2,     2,
       2,     2,    79,    77,     2,    78,     2,    80,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      75,     2,    76,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    16,    24,    32,    38,
      40,    43,    44,    46,    49,    50,    52,    54,    56,    58,
      60,    62,    64,    68,    72,    75,    77,    80,    84,    88,
      92,    96,   103,   109,   114,   121,   127,   134,   140,   150,
     157,   163,   165,   169,   172,   177,   179,   181,   183,   185,
     187,   189,   191,   193,   195,   197,   199,   201,   205,   211,
     213,   217,   219,   223,   227,   233,   237,   240,   242,   245,
     247,   249,   251,   253,   255,   257,   259,   261,   263,   265,
     267,   269,   271,   273,   275,   278,   280,   286,   294,   302,
     304,   307,   312,   316,   320,   323,   329,   337,   347,   349,
     351,   352,   357,   360,   362,   363,   365,   366,   375,   385,
     394,   398,   401,   404,   407,   411,   415,   421,   426,   428,
     431,   438,   440,   442,   446,   450,   454,   458,   462,   464,
     468,   470,   474,   476,   480,   484,   486,   490,   494,   498,
     502,   506,   508,   512,   516,   518,   522,   526,   530,   532,
     535,   538,   541,   544,   549,   555,   561,   566,   568,   571,
     574,   579,   583,   588,   592,   599,   605,   607,   609,   611,
     613,   615,   617,   619,   621,   623,   625,   629,   631
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      84,     0,    -1,    85,    -1,    86,    -1,    85,    86,    -1,
      87,    88,     4,    51,    91,    -1,    87,    88,     4,    51,
       6,    51,    91,    -1,    87,    88,     4,    51,     7,    90,
      91,    -1,    87,    88,     5,    51,    91,    -1,     3,    -1,
      87,     3,    -1,    -1,    89,    -1,    88,    89,    -1,    -1,
       8,    -1,     9,    -1,    10,    -1,    11,    -1,    12,    -1,
      13,    -1,    51,    -1,    90,    66,    51,    -1,    71,    92,
      72,    -1,    71,    72,    -1,    93,    -1,    92,    93,    -1,
      87,    88,    96,    -1,    87,    88,    94,    -1,    87,    88,
      95,    -1,    99,   101,    65,    -1,    99,    51,    73,    74,
     101,    65,    -1,    51,    69,    97,    70,   103,    -1,    51,
      69,    70,   103,    -1,    99,    51,    69,    97,    70,   103,
      -1,    99,    51,    69,    70,   103,    -1,    32,    51,    69,
      97,    70,   103,    -1,    32,    51,    69,    70,   103,    -1,
      32,    51,    69,    31,    73,    74,    51,    70,   103,    -1,
      99,    51,    69,    97,    70,    65,    -1,    99,    51,    69,
      70,    65,    -1,    98,    -1,    97,    66,    98,    -1,    99,
      51,    -1,    99,    51,    73,    74,    -1,    99,    -1,    23,
      -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,
      -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,    51,
      -1,    99,   101,    65,    -1,    99,    51,    73,    74,    65,
      -1,   102,    -1,   101,    66,   102,    -1,    51,    -1,    51,
      64,   127,    -1,    51,    73,    74,    -1,    51,    73,    74,
      64,   127,    -1,    71,   104,    72,    -1,    71,    72,    -1,
     105,    -1,   104,   105,    -1,   100,    -1,   106,    -1,   103,
      -1,   107,    -1,   108,    -1,   111,    -1,   112,    -1,   113,
      -1,   118,    -1,   119,    -1,   120,    -1,   121,    -1,   122,
      -1,   123,    -1,   124,    -1,   127,    65,    -1,    65,    -1,
      33,    69,   127,    70,   105,    -1,    33,    69,   127,    70,
     105,    34,   105,    -1,    38,    69,   127,    70,    71,   109,
      72,    -1,   110,    -1,   109,   110,    -1,    39,   127,    67,
     104,    -1,    39,   127,    67,    -1,    40,    67,   104,    -1,
      40,    67,    -1,    35,    69,   127,    70,   105,    -1,    36,
     105,    35,    69,   127,    70,    65,    -1,    37,    69,   114,
      65,   116,    65,   117,    70,   105,    -1,   115,    -1,   127,
      -1,    -1,    99,    51,    64,   127,    -1,    99,    51,    -1,
     127,    -1,    -1,   127,    -1,    -1,    37,    69,    99,    51,
      67,   127,    70,   105,    -1,    51,    68,    51,    68,    51,
      69,   138,    70,    65,    -1,    51,    68,    51,    68,    51,
      69,    70,    65,    -1,    43,   127,    65,    -1,    43,    65,
      -1,    41,    65,    -1,    42,    65,    -1,    19,   127,    65,
      -1,    20,   103,   125,    -1,    20,   103,   125,    22,   103,
      -1,    20,   103,    22,   103,    -1,   126,    -1,   125,   126,
      -1,    21,    69,    99,    51,    70,   103,    -1,   128,    -1,
     129,    -1,   135,    64,   128,    -1,   135,    60,   128,    -1,
     135,    61,   128,    -1,   135,    62,   128,    -1,   135,    63,
     128,    -1,   130,    -1,   129,    57,   130,    -1,   131,    -1,
     130,    56,   131,    -1,   132,    -1,   131,    52,   132,    -1,
     131,    53,   132,    -1,   133,    -1,   132,    75,   133,    -1,
     132,    76,   133,    -1,   132,    54,   133,    -1,   132,    55,
     133,    -1,   132,    17,    51,    -1,   134,    -1,   133,    77,
     134,    -1,   133,    78,   134,    -1,   135,    -1,   134,    79,
     135,    -1,   134,    80,   135,    -1,   134,    81,   135,    -1,
     136,    -1,    58,   135,    -1,    59,   135,    -1,    82,   135,
      -1,    78,   135,    -1,    14,    99,    69,    70,    -1,    14,
      99,    69,   138,    70,    -1,    14,    99,    73,   127,    74,
      -1,    69,    99,    70,   135,    -1,   137,    -1,   136,    58,
      -1,   136,    59,    -1,   136,    73,   127,    74,    -1,   136,
      68,    51,    -1,    51,    69,   138,    70,    -1,    51,    69,
      70,    -1,   136,    68,    51,    69,   138,    70,    -1,   136,
      68,    51,    69,    70,    -1,    51,    -1,    47,    -1,    48,
      -1,    49,    -1,    50,    -1,    44,    -1,    45,    -1,    46,
      -1,    15,    -1,    16,    -1,    69,   127,    70,    -1,   127,
      -1,   138,    66,   127,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   145,   145,   150,   151,   159,   161,   163,   165,   170,
     171,   172,   176,   177,   178,   182,   183,   184,   185,   186,
     187,   191,   192,   196,   197,   201,   202,   206,   207,   208,
     216,   218,   227,   229,   238,   240,   242,   244,   247,   249,
     251,   260,   261,   265,   267,   269,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   296,   298,   303,
     304,   308,   310,   312,   314,   323,   324,   328,   329,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   355,   356,   363,   365,   373,   378,
     379,   383,   384,   385,   386,   391,   396,   402,   407,   408,
     409,   413,   415,   420,   421,   425,   426,   433,   441,   443,
     449,   451,   455,   456,   459,   464,   465,   466,   470,   471,
     475,   484,   488,   489,   490,   491,   492,   493,   497,   498,
     502,   503,   507,   508,   509,   513,   514,   515,   516,   517,
     518,   523,   524,   525,   529,   530,   531,   532,   536,   537,
     538,   539,   540,   541,   543,   545,   547,   552,   553,   554,
     555,   557,   559,   561,   563,   565,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   584,   586
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ANNOTATION", "KEYWORD_CLASS",
  "KEYWORD_INTERFACE", "KEYWORD_EXTENDS", "KEYWORD_IMPLEMENTS",
  "KEYWORD_PUBLIC", "KEYWORD_PRIVATE", "KEYWORD_PROTECTED",
  "KEYWORD_STATIC", "KEYWORD_FINAL", "KEYWORD_ABSTRACT", "KEYWORD_NEW",
  "KEYWORD_THIS", "KEYWORD_SUPER", "KEYWORD_INSTANCEOF", "KEYWORD_THROWS",
  "KEYWORD_THROW", "KEYWORD_TRY", "KEYWORD_CATCH", "KEYWORD_FINALLY",
  "KEYWORD_INT", "KEYWORD_FLOAT", "KEYWORD_DOUBLE", "KEYWORD_CHAR",
  "KEYWORD_BOOLEAN", "KEYWORD_BYTE", "KEYWORD_SHORT", "KEYWORD_LONG",
  "KEYWORD_STRING", "KEYWORD_VOID", "KEYWORD_IF", "KEYWORD_ELSE",
  "KEYWORD_WHILE", "KEYWORD_DO", "KEYWORD_FOR", "KEYWORD_SWITCH",
  "KEYWORD_CASE", "KEYWORD_DEFAULT", "KEYWORD_BREAK", "KEYWORD_CONTINUE",
  "KEYWORD_RETURN", "CONST_BOOL_TRUE", "CONST_BOOL_FALSE", "CONST_NULL",
  "CONST_INT", "CONST_FLOAT", "STRING_LITERAL", "CHAR_LITERAL",
  "IDENTIFIER", "OP_EQ", "OP_NEQ", "OP_LEQ", "OP_GEQ", "OP_AND", "OP_OR",
  "OP_INC", "OP_DEC", "OP_PLUS_ASSIGN", "OP_MINUS_ASSIGN", "OP_MUL_ASSIGN",
  "OP_DIV_ASSIGN", "ASSIGN", "SEMICOLON", "COMMA", "COLON", "DOT",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "$accept", "program",
  "class_list", "class_declaration", "annotation_list", "modifiers",
  "modifier", "id_list", "class_body", "class_member_list", "class_member",
  "field_declaration", "constructor_definition", "method_definition",
  "param_list", "param", "type_specifier", "var_declaration",
  "var_init_list", "var_init", "compound_statement", "statement_list",
  "statement", "expression_statement", "if_statement", "switch_statement",
  "case_list", "case_clause", "while_statement", "do_while_statement",
  "for_statement", "for_init", "var_declaration_inline", "for_cond",
  "for_update", "for_each_statement", "sysout_statement",
  "return_statement", "break_statement", "continue_statement",
  "throw_statement", "try_statement", "catch_clause_list", "catch_clause",
  "expression", "assignment_expr", "logical_or_expr", "logical_and_expr",
  "equality_expr", "relational_expr", "additive_expr",
  "multiplicative_expr", "unary_expr", "postfix_expr", "primary_expr",
  "argument_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,    60,    62,    43,    45,    42,
      47,    37,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    85,    85,    86,    86,    86,    86,    87,
      87,    87,    88,    88,    88,    89,    89,    89,    89,    89,
      89,    90,    90,    91,    91,    92,    92,    93,    93,    93,
      94,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    97,    97,    98,    98,    98,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,   100,   100,   101,
     101,   102,   102,   102,   102,   103,   103,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   106,   107,   107,   108,   109,
     109,   110,   110,   110,   110,   111,   112,   113,   114,   114,
     114,   115,   115,   116,   116,   117,   117,   118,   119,   119,
     120,   120,   121,   122,   123,   124,   124,   124,   125,   125,
     126,   127,   128,   128,   128,   128,   128,   128,   129,   129,
     130,   130,   131,   131,   131,   132,   132,   132,   132,   132,
     132,   133,   133,   133,   134,   134,   134,   134,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   138,   138
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     5,     7,     7,     5,     1,
       2,     0,     1,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     2,     1,     2,     3,     3,     3,
       3,     6,     5,     4,     6,     5,     6,     5,     9,     6,
       5,     1,     3,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     5,     1,
       3,     1,     3,     3,     5,     3,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     5,     7,     7,     1,
       2,     4,     3,     3,     2,     5,     7,     9,     1,     1,
       0,     4,     2,     1,     0,     1,     0,     8,     9,     8,
       3,     2,     2,     2,     3,     3,     5,     4,     1,     2,
       6,     1,     1,     3,     3,     3,     3,     3,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     2,     4,     5,     5,     4,     1,     2,     2,
       4,     3,     4,     3,     6,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      11,     9,     0,    11,     3,    14,     1,     4,    10,    15,
      16,    17,    18,    19,    20,     0,    12,     0,     0,    13,
       0,     0,     0,     0,    11,     5,     8,     0,    21,     0,
      24,    14,    11,    25,     6,     0,     7,     0,    23,    26,
      22,    46,    47,    48,    49,    50,    51,    52,    53,    54,
       0,    56,    28,    29,    27,     0,     0,     0,    61,     0,
      59,     0,    55,    56,     0,     0,    41,    45,     0,     0,
       0,    30,     0,    54,     0,     0,     0,    33,     0,     0,
      43,     0,   174,   175,   171,   172,   173,   167,   168,   169,
     170,   166,     0,     0,     0,     0,     0,    62,   121,   122,
     128,   130,   132,   135,   141,   144,   148,   157,     0,     0,
      63,    61,    60,     0,    37,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   166,    85,    66,     0,
      69,    71,     0,    67,    70,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,    42,    32,
       0,     0,     0,   149,   150,   166,     0,     0,   152,   151,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
     159,     0,     0,    40,    35,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,   100,     0,   112,   113,
     111,     0,     0,    61,     0,    65,    68,    84,    44,     0,
       0,   163,   177,     0,     0,   176,   129,   144,   131,   133,
     134,   140,   138,   139,   136,   137,   142,   143,   145,   146,
     147,   124,   125,   126,   127,   123,   161,     0,    39,    34,
      64,    31,    63,     0,   114,     0,     0,   115,   118,     0,
       0,     0,     0,     0,    98,    99,     0,   110,     0,     0,
      57,   153,     0,     0,     0,   162,   156,     0,   160,     0,
       0,   117,     0,   119,     0,     0,     0,   102,   104,     0,
       0,    63,   154,   155,   178,   165,     0,    38,     0,   116,
      86,    95,     0,     0,     0,     0,   103,     0,     0,    58,
     164,     0,     0,     0,   101,     0,   106,     0,     0,     0,
      89,     0,     0,    87,    96,     0,     0,   105,     0,    94,
      88,    90,     0,     0,   120,   107,     0,    92,    93,   109,
       0,    97,    91,   108
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,    15,    16,    29,    25,    32,
      33,    52,    53,    54,    65,    66,   129,   130,    59,    60,
     131,   132,   133,   134,   135,   136,   309,   310,   137,   138,
     139,   253,   254,   295,   316,   140,   141,   142,   143,   144,
     145,   146,   247,   248,   147,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   213
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -245
static const yytype_int16 yypact[] =
{
      37,  -245,    66,   157,  -245,   136,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,   183,  -245,     1,    17,  -245,
       5,    60,    26,    72,     0,  -245,  -245,    60,  -245,    30,
    -245,   136,     2,  -245,  -245,    74,  -245,   712,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
      87,    81,  -245,  -245,  -245,    89,   103,    63,   -19,    97,
    -245,   649,  -245,  -245,   110,   -52,  -245,   133,   589,   659,
     127,  -245,   139,   144,   110,    14,   227,  -245,   722,   110,
     149,   722,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,   156,   589,   589,   407,   589,   589,  -245,  -245,   177,
     182,   151,     6,   129,   134,    92,   -11,  -245,   -40,    46,
     -43,    -9,  -245,   171,  -245,   110,   589,   110,   180,   192,
     347,   214,   215,   222,   223,   120,   -27,  -245,  -245,   238,
    -245,  -245,   287,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,  -245,  -245,   225,  -245,  -245,
     217,    44,   433,  -245,  -245,   -32,   224,   230,  -245,  -245,
     589,   589,   589,   589,   242,   589,   589,   589,   589,   589,
     589,   589,   589,   589,   589,   589,   589,   589,   589,  -245,
    -245,   244,   589,  -245,  -245,     8,   589,   158,   234,   246,
    -245,   239,   207,   589,   589,   286,   407,   589,  -245,  -245,
    -245,   261,   276,    -8,   165,  -245,  -245,  -245,  -245,   472,
     589,  -245,  -245,    52,   589,  -245,   182,  -245,   151,     6,
       6,  -245,   129,   129,   129,   129,   134,   134,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,  -245,   270,   266,  -245,  -245,
    -245,  -245,   277,   272,  -245,   274,   110,   211,  -245,   278,
     279,   275,   296,   285,  -245,  -245,   281,  -245,   289,   280,
    -245,  -245,    54,   290,   589,  -245,  -245,   511,  -245,   110,
     722,  -245,   110,  -245,   347,   347,   589,   116,   589,   282,
     304,   172,  -245,  -245,  -245,  -245,    62,  -245,   309,  -245,
     334,  -245,   311,   589,   589,   321,  -245,   240,   318,  -245,
    -245,   329,   347,   335,  -245,   331,   589,   589,   336,   -33,
    -245,   550,   110,  -245,  -245,   347,   332,  -245,   337,   347,
    -245,  -245,   342,    71,  -245,  -245,   347,   347,   347,  -245,
     343,  -245,   347,  -245
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -245,  -245,  -245,   406,    -4,   379,    -2,  -245,    42,  -245,
     381,  -245,  -245,  -245,     9,   333,   -35,  -245,   -93,   345,
     -64,  -244,  -116,  -245,  -245,  -245,  -245,   105,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,   168,   -67,    -1,  -245,   259,   263,   104,
      53,   112,   -63,  -245,  -245,  -200
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -57
static const yytype_int16 yytable[] =
{
      77,    97,    55,     1,   195,     1,   307,   308,   111,   262,
     114,    22,    23,    19,    78,   149,   206,   187,    79,   -56,
      31,   186,    67,   164,   -56,   183,    67,   157,    31,   153,
     154,    76,   158,   159,    67,    19,   204,   152,   -56,   320,
       1,   202,   152,    67,   184,    68,   151,   179,   180,   191,
      69,   190,    20,   192,    70,    68,    68,   181,   201,   156,
     165,   166,   182,    26,   188,   259,     6,   286,    21,    34,
      75,    36,    30,   238,    38,   328,    24,    27,   109,    76,
      78,   167,   168,   332,   115,   212,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    62,    35,   217,   217,   217,
     217,    24,   217,   217,   217,   217,   217,   217,   228,   229,
     230,   323,    78,   209,    63,   237,   185,   210,   264,   240,
     264,   239,   265,    28,   282,    40,   249,   250,   264,   255,
     256,    24,   300,    64,    81,    82,    83,   264,    56,     8,
      58,   330,   212,   263,     9,    10,    11,    12,    13,    14,
      57,   266,   174,   175,   176,   177,   178,    -2,   290,   291,
       1,   252,    71,    72,    84,    85,    86,    87,    88,    89,
      90,    91,    61,   231,   232,   233,   234,   235,    92,    93,
     293,    76,   271,   294,    80,   200,   313,    17,    18,    94,
     111,     9,    10,    11,    12,    13,    14,   284,    95,   325,
     212,   110,    96,   162,   163,   287,   169,   170,   289,   292,
     331,   296,   206,   171,   172,   173,   206,   113,   222,   223,
     224,   225,   150,   241,    72,   152,   304,   305,   245,   246,
     260,    72,   245,   272,   160,   288,   186,   299,   161,   317,
     318,    81,    82,    83,   212,   189,   116,   117,   324,   193,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    62,
     118,   194,   119,   120,   121,   122,   219,   220,   123,   124,
     125,    84,    85,    86,    87,    88,    89,    90,   126,   307,
     308,   226,   227,   196,   197,    92,    93,   198,   199,   203,
     207,   208,   127,   221,   214,   236,    94,   243,    76,   128,
     215,    81,    82,    83,   244,    95,   116,   117,   242,    96,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    62,
     118,   251,   119,   120,   121,   122,   257,   258,   123,   124,
     125,    84,    85,    86,    87,    88,    89,    90,   126,   267,
     268,   186,   269,   270,   276,    92,    93,   277,   274,   275,
     278,   279,   127,   297,   281,   298,    94,   280,    76,   205,
     301,    81,    82,    83,   283,    95,   116,   117,   302,    96,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    62,
     118,   303,   119,   120,   121,   122,   306,   311,   123,   124,
     125,    84,    85,    86,    87,    88,    89,    90,   126,   312,
     314,   315,   326,   319,   327,    92,    93,   329,   333,     7,
      37,   148,   127,    39,   321,   273,    94,   112,    76,   216,
       0,    81,    82,    83,   218,    95,     0,     0,     0,    96,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    62,
       0,     0,     0,     0,     0,     0,     0,    81,    82,    83,
       0,    84,    85,    86,    87,    88,    89,    90,   155,     0,
       0,     0,     0,     0,     0,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    94,    84,    85,    86,
      87,    88,    89,    90,    91,    95,    81,    82,    83,    96,
       0,    92,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,   211,     0,     0,     0,     0,     0,     0,
       0,    95,     0,     0,     0,    96,    84,    85,    86,    87,
      88,    89,    90,    91,     0,    81,    82,    83,     0,     0,
      92,    93,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,   261,     0,     0,     0,     0,     0,     0,     0,
      95,     0,     0,     0,    96,    84,    85,    86,    87,    88,
      89,    90,    91,     0,    81,    82,    83,     0,     0,    92,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,   285,     0,     0,     0,     0,     0,     0,     0,    95,
       0,     0,     0,    96,    84,    85,    86,    87,    88,    89,
      90,    91,     0,    81,    82,    83,     0,     0,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    94,
     322,     0,     0,     0,     0,     0,     0,     0,    95,     0,
       0,     0,    96,    84,    85,    86,    87,    88,    89,    90,
      91,     0,     0,     0,     0,     0,     0,    92,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,     0,
       0,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,    96,    41,    42,    43,    44,    45,    46,    47,    48,
      73,    62,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    62,     0,     0,     0,     0,     0,     0,     0,     0,
      63,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      63,     0,     0,     0,     0,     0,     0,     0,     0,    74,
       9,    10,    11,    12,    13,    14,     0,     0,     0,   108,
       0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    62,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63
};

static const yytype_int16 yycheck[] =
{
      64,    68,    37,     3,   120,     3,    39,    40,    51,   209,
      74,     6,     7,    15,    66,    79,   132,   110,    70,    51,
      24,    64,    57,    17,    51,    65,    61,    94,    32,    92,
      93,    71,    95,    96,    69,    37,   129,    69,    70,    72,
       3,    68,    69,    78,   108,    64,    81,    58,    59,   116,
      69,   115,    51,   117,    73,    64,    64,    68,   125,    94,
      54,    55,    73,    21,    73,    73,     0,   267,    51,    27,
      61,    29,    72,    65,    72,   319,    71,    51,    69,    71,
      66,    75,    76,   327,    70,   152,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    66,   160,   161,   162,
     163,    71,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   311,    66,    69,    51,   182,    70,    73,    66,   186,
      66,   185,    70,    51,    70,    51,   193,   194,    66,   196,
     197,    71,    70,    70,    14,    15,    16,    66,    51,     3,
      51,    70,   209,   210,     8,     9,    10,    11,    12,    13,
      69,   214,    60,    61,    62,    63,    64,     0,   274,   275,
       3,   196,    65,    66,    44,    45,    46,    47,    48,    49,
      50,    51,    69,   174,   175,   176,   177,   178,    58,    59,
      64,    71,   246,    67,    51,    65,   302,     4,     5,    69,
      51,     8,     9,    10,    11,    12,    13,   264,    78,   315,
     267,    74,    82,    52,    53,   269,    77,    78,   272,   276,
     326,   278,   328,    79,    80,    81,   332,    73,   165,   166,
     167,   168,    73,    65,    66,    69,   293,   294,    21,    22,
      65,    66,    21,    22,    57,   270,    64,    65,    56,   306,
     307,    14,    15,    16,   311,    74,    19,    20,   312,    69,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    69,    35,    36,    37,    38,   162,   163,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    39,
      40,   169,   170,    69,    69,    58,    59,    65,    65,    51,
      65,    74,    65,    51,    70,    51,    69,    51,    71,    72,
      70,    14,    15,    16,    65,    78,    19,    20,    74,    82,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    35,    35,    36,    37,    38,    65,    51,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    69,
      74,    64,    70,    69,    69,    58,    59,    51,    70,    70,
      65,    70,    65,    71,    74,    51,    69,    68,    71,    72,
      51,    14,    15,    16,    74,    78,    19,    20,    34,    82,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    70,    35,    36,    37,    38,    65,    69,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    70,
      65,    70,    70,    67,    67,    58,    59,    65,    65,     3,
      31,    78,    65,    32,   309,   247,    69,    72,    71,   160,
      -1,    14,    15,    16,   161,    78,    -1,    -1,    -1,    82,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    14,    15,    16,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    44,    45,    46,
      47,    48,    49,    50,    51,    78,    14,    15,    16,    82,
      -1,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    82,    44,    45,    46,    47,
      48,    49,    50,    51,    -1,    14,    15,    16,    -1,    -1,
      58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    82,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    14,    15,    16,    -1,    -1,    58,
      59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    82,    44,    45,    46,    47,    48,    49,
      50,    51,    -1,    14,    15,    16,    -1,    -1,    58,    59,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    82,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    82,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    84,    85,    86,    87,     0,    86,     3,     8,
       9,    10,    11,    12,    13,    88,    89,     4,     5,    89,
      51,    51,     6,     7,    71,    91,    91,    51,    51,    90,
      72,    87,    92,    93,    91,    66,    91,    88,    72,    93,
      51,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    51,    94,    95,    96,    99,    51,    69,    51,   101,
     102,    69,    32,    51,    70,    97,    98,    99,    64,    69,
      73,    65,    66,    31,    70,    97,    71,   103,    66,    70,
      51,    14,    15,    16,    44,    45,    46,    47,    48,    49,
      50,    51,    58,    59,    69,    78,    82,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,    70,    97,
      74,    51,   102,    73,   103,    70,    19,    20,    33,    35,
      36,    37,    38,    41,    42,    43,    51,    65,    72,    99,
     100,   103,   104,   105,   106,   107,   108,   111,   112,   113,
     118,   119,   120,   121,   122,   123,   124,   127,    98,   103,
      73,    99,    69,   135,   135,    51,    99,   127,   135,   135,
      57,    56,    52,    53,    17,    54,    55,    75,    76,    77,
      78,    79,    80,    81,    60,    61,    62,    63,    64,    58,
      59,    68,    73,    65,   103,    70,    64,   101,    73,    74,
     103,   127,   103,    69,    69,   105,    69,    69,    65,    65,
      65,   127,    68,    51,   101,    72,   105,    65,    74,    69,
      73,    70,   127,   138,    70,    70,   130,   135,   131,   132,
     132,    51,   133,   133,   133,   133,   134,   134,   135,   135,
     135,   128,   128,   128,   128,   128,    51,   127,    65,   103,
     127,    65,    74,    51,    65,    21,    22,   125,   126,   127,
     127,    35,    99,   114,   115,   127,   127,    65,    51,    73,
      65,    70,   138,   127,    66,    70,   135,    69,    74,    70,
      69,   103,    22,   126,    70,    70,    69,    51,    65,    70,
      68,    74,    70,    74,   127,    70,   138,   103,    99,   103,
     105,   105,   127,    64,    67,   116,   127,    71,    51,    65,
      70,    51,    34,    70,   127,   127,    65,    39,    40,   109,
     110,    69,    70,   105,    65,    70,   117,   127,   127,    67,
      72,   110,    70,   138,   103,   105,    70,    67,   104,    65,
      70,   105,   104,    65
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1464 of yacc.c  */
#line 146 "compiler/java/parser/parser_java.y"
    { printf("[Parse] Java program parsed successfully.\n"); ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 160 "compiler/java/parser/parser_java.y"
    { printf("[Class] class %s\n", (yyvsp[(4) - (5)].string_val)); free((yyvsp[(4) - (5)].string_val)); ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 162 "compiler/java/parser/parser_java.y"
    { printf("[Class] class %s extends %s\n", (yyvsp[(4) - (7)].string_val), (yyvsp[(6) - (7)].string_val)); free((yyvsp[(4) - (7)].string_val)); free((yyvsp[(6) - (7)].string_val)); ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 164 "compiler/java/parser/parser_java.y"
    { printf("[Class] class %s implements ...\n", (yyvsp[(4) - (7)].string_val)); free((yyvsp[(4) - (7)].string_val)); ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 166 "compiler/java/parser/parser_java.y"
    { printf("[Interface] interface %s\n", (yyvsp[(4) - (5)].string_val)); free((yyvsp[(4) - (5)].string_val)); ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 170 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 171 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 191 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 192 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 217 "compiler/java/parser/parser_java.y"
    { printf("[Field] type=%s\n", (yyvsp[(1) - (3)].string_val)); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 219 "compiler/java/parser/parser_java.y"
    { printf("[Field] array type=%s\n", (yyvsp[(1) - (6)].string_val)); ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 228 "compiler/java/parser/parser_java.y"
    { printf("[Constructor] %s(...)\n", (yyvsp[(1) - (5)].string_val)); free((yyvsp[(1) - (5)].string_val)); ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 230 "compiler/java/parser/parser_java.y"
    { printf("[Constructor] %s()\n", (yyvsp[(1) - (4)].string_val)); free((yyvsp[(1) - (4)].string_val)); ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 239 "compiler/java/parser/parser_java.y"
    { printf("[Method] %s %s(...)\n", (yyvsp[(1) - (6)].string_val), (yyvsp[(2) - (6)].string_val)); free((yyvsp[(1) - (6)].string_val)); free((yyvsp[(2) - (6)].string_val)); ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 241 "compiler/java/parser/parser_java.y"
    { printf("[Method] %s %s()\n", (yyvsp[(1) - (5)].string_val), (yyvsp[(2) - (5)].string_val)); free((yyvsp[(1) - (5)].string_val)); free((yyvsp[(2) - (5)].string_val)); ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 243 "compiler/java/parser/parser_java.y"
    { printf("[Method] void %s(...)\n", (yyvsp[(2) - (6)].string_val)); free((yyvsp[(2) - (6)].string_val)); ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 245 "compiler/java/parser/parser_java.y"
    { printf("[Method] void %s()\n", (yyvsp[(2) - (5)].string_val)); free((yyvsp[(2) - (5)].string_val)); ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 248 "compiler/java/parser/parser_java.y"
    { printf("[Method] void %s(String[] %s)\n", (yyvsp[(2) - (9)].string_val), (yyvsp[(7) - (9)].string_val)); free((yyvsp[(2) - (9)].string_val)); free((yyvsp[(7) - (9)].string_val)); ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 250 "compiler/java/parser/parser_java.y"
    { printf("[Method] abstract/interface: %s %s(...)\n", (yyvsp[(1) - (6)].string_val), (yyvsp[(2) - (6)].string_val)); free((yyvsp[(1) - (6)].string_val)); free((yyvsp[(2) - (6)].string_val)); ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 252 "compiler/java/parser/parser_java.y"
    { printf("[Method] abstract/interface: %s %s()\n", (yyvsp[(1) - (5)].string_val), (yyvsp[(2) - (5)].string_val)); free((yyvsp[(1) - (5)].string_val)); free((yyvsp[(2) - (5)].string_val)); ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 266 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (2)].string_val)); free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 268 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(2) - (4)].string_val)); ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 270 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 278 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 279 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 280 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 281 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 282 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 283 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 284 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 285 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 286 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 287 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "void"; ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 288 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 297 "compiler/java/parser/parser_java.y"
    { printf("[Decl] type=%s\n", (yyvsp[(1) - (3)].string_val)); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 299 "compiler/java/parser/parser_java.y"
    { printf("[Decl] array %s %s[]\n", (yyvsp[(1) - (5)].string_val), (yyvsp[(2) - (5)].string_val)); free((yyvsp[(1) - (5)].string_val)); free((yyvsp[(2) - (5)].string_val)); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 309 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 311 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 313 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (3)].string_val)); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 315 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (5)].string_val)); free((yyvsp[(5) - (5)].string_val)); ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 355 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (2)].string_val)); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 364 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] if (%s)\n", (yyvsp[(3) - (5)].string_val)); free((yyvsp[(3) - (5)].string_val)); ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 366 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] if-else (%s)\n", (yyvsp[(3) - (7)].string_val)); free((yyvsp[(3) - (7)].string_val)); ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 374 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] switch (%s)\n", (yyvsp[(3) - (7)].string_val)); free((yyvsp[(3) - (7)].string_val)); ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 383 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(2) - (4)].string_val)); ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 384 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(2) - (3)].string_val)); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 392 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] while (%s)\n", (yyvsp[(3) - (5)].string_val)); free((yyvsp[(3) - (5)].string_val)); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 397 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] do-while (%s)\n", (yyvsp[(5) - (7)].string_val)); free((yyvsp[(5) - (7)].string_val)); ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 403 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] for(...)\n"); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 408 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 414 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(2) - (4)].string_val)); free((yyvsp[(4) - (4)].string_val)); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 416 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (2)].string_val)); free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 420 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 425 "compiler/java/parser/parser_java.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 434 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] for-each: %s %s : ...\n", (yyvsp[(3) - (8)].string_val), (yyvsp[(4) - (8)].string_val)); free((yyvsp[(3) - (8)].string_val)); free((yyvsp[(4) - (8)].string_val)); free((yyvsp[(6) - (8)].string_val)); ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 442 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] System.out.println/print(...)\n"); free((yyvsp[(1) - (9)].string_val)); free((yyvsp[(3) - (9)].string_val)); free((yyvsp[(5) - (9)].string_val)); free((yyvsp[(7) - (9)].string_val)); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 444 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] System.out.println()\n"); free((yyvsp[(1) - (8)].string_val)); free((yyvsp[(3) - (8)].string_val)); free((yyvsp[(5) - (8)].string_val)); ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 450 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] return %s\n", (yyvsp[(2) - (3)].string_val)); free((yyvsp[(2) - (3)].string_val)); ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 452 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] return;\n"); ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 455 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] break;\n"); ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 456 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] continue;\n"); ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 460 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] throw ...\n"); free((yyvsp[(2) - (3)].string_val)); ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 476 "compiler/java/parser/parser_java.y"
    { printf("[Stmt] catch(%s %s)\n", (yyvsp[(3) - (6)].string_val), (yyvsp[(4) - (6)].string_val)); free((yyvsp[(3) - (6)].string_val)); free((yyvsp[(4) - (6)].string_val)); ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 484 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 488 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 489 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 490 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 491 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 492 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 493 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 497 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 498 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "||_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 502 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 503 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "&&_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 507 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 508 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "==_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 509 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "!=_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 513 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 514 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "<_expr";  free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 515 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = ">_expr";  free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 516 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "<=_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 517 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = ">=_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 519 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "instanceof_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 523 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 524 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "+_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 525 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "-_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 529 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 530 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "*_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 531 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "/_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 532 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "%_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 536 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 537 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "++x"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 538 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "--x"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 539 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "!expr"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 540 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "-expr"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 542 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "new_obj"; free((yyvsp[(2) - (4)].string_val)); ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 544 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "new_obj_args"; free((yyvsp[(2) - (5)].string_val)); free((yyvsp[(4) - (5)].string_val)); ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 546 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "new_arr"; free((yyvsp[(2) - (5)].string_val)); free((yyvsp[(4) - (5)].string_val)); ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 548 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "cast_expr"; free((yyvsp[(2) - (4)].string_val)); free((yyvsp[(4) - (4)].string_val)); ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 552 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 553 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "x++"; free((yyvsp[(1) - (2)].string_val)); ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 554 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "x--"; free((yyvsp[(1) - (2)].string_val)); ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 556 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "arr_access"; free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(3) - (4)].string_val)); ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 558 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 560 "compiler/java/parser/parser_java.y"
    { printf("[Expr] Call: %s(...)\n", (yyvsp[(1) - (4)].string_val)); (yyval.string_val) = (yyvsp[(1) - (4)].string_val); free((yyvsp[(3) - (4)].string_val)); ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 562 "compiler/java/parser/parser_java.y"
    { printf("[Expr] Call: %s()\n", (yyvsp[(1) - (3)].string_val)); (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 564 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (6)].string_val); free((yyvsp[(3) - (6)].string_val)); free((yyvsp[(5) - (6)].string_val)); ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 566 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (5)].string_val); free((yyvsp[(3) - (5)].string_val)); ;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 570 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 571 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 572 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 573 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 574 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 575 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 576 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 577 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 578 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "this"; ;}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 579 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = "super"; ;}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 580 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(2) - (3)].string_val); ;}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 585 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 587 "compiler/java/parser/parser_java.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); free((yyvsp[(3) - (3)].string_val)); ;}
    break;



/* Line 1464 of yacc.c  */
#line 2704 "compiler/java/parser/parser_java.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 590 "compiler/java/parser/parser_java.y"


/* ------------------------------------------------------------------ */
/*  Standalone test driver                                              */
/*  Compile:  bison -d -o parser_java.tab.c parser_java.y             */
/*            flex  -o lex.yy_java.c lexer_java.l                     */
/*            g++ -o test_java parser_java.tab.c lex.yy_java.c        */
/*  Run:      ./test_java ../../examples/Hello.java                    */
/* ------------------------------------------------------------------ */
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

