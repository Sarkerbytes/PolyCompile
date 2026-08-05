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
#line 1 "compiler/cpp/parser/parser_cpp.y"

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



/* Line 189 of yacc.c  */
#line 103 "compiler/cpp/parser/parser_cpp.tab.c"

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

/* Line 214 of yacc.c  */
#line 34 "compiler/cpp/parser/parser_cpp.y"

    char* string_val;



/* Line 214 of yacc.c  */
#line 211 "compiler/cpp/parser/parser_cpp.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 223 "compiler/cpp/parser/parser_cpp.tab.c"

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
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   638

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNRULES -- Number of states.  */
#define YYNSTATES  280

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,     2,     2,     2,    73,    75,     2,
       2,     2,    71,    69,     2,    70,     2,    72,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      67,     2,    68,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    18,
      20,    22,    27,    34,    40,    42,    45,    46,    50,    52,
      54,    56,    58,    60,    62,    65,    67,    69,    71,    73,
      75,    77,    79,    81,    83,    85,    89,    91,    95,    97,
     101,   106,   110,   117,   123,   130,   136,   145,   153,   155,
     159,   162,   167,   172,   174,   178,   181,   183,   186,   188,
     190,   192,   194,   196,   198,   200,   202,   204,   206,   208,
     210,   212,   215,   217,   223,   231,   239,   241,   244,   249,
     253,   257,   260,   266,   274,   284,   286,   288,   289,   294,
     297,   299,   300,   302,   303,   308,   310,   312,   316,   320,
     325,   327,   331,   335,   338,   341,   344,   346,   348,   352,
     356,   360,   364,   368,   370,   374,   376,   380,   382,   386,
     390,   392,   396,   400,   404,   408,   410,   414,   418,   420,
     424,   428,   432,   434,   437,   440,   443,   446,   449,   452,
     457,   463,   465,   468,   471,   476,   480,   484,   489,   493,
     500,   506,   508,   510,   512,   514,   516,   518,   520,   522,
     526,   528
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      77,     0,    -1,    78,    -1,    79,    -1,    78,    79,    -1,
      80,    -1,    81,    -1,    82,    -1,    92,    -1,    89,    -1,
       3,    -1,     4,     5,    40,    57,    -1,     9,    40,    63,
      83,    64,    57,    -1,     9,    40,    63,    83,    64,    -1,
      84,    -1,    83,    84,    -1,    -1,    85,    59,    86,    -1,
      92,    -1,    89,    -1,    13,    -1,    14,    -1,    15,    -1,
      87,    -1,    86,    87,    -1,    92,    -1,    89,    -1,    17,
      -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,    16,
      -1,    22,    -1,    40,    -1,    88,    90,    57,    -1,    91,
      -1,    90,    58,    91,    -1,    40,    -1,    40,    56,   117,
      -1,    40,    65,    36,    66,    -1,    40,    65,    66,    -1,
      88,    40,    61,    93,    62,    95,    -1,    88,    40,    61,
      62,    95,    -1,    88,    40,    61,    93,    62,    57,    -1,
      88,    40,    61,    62,    57,    -1,    88,    40,    55,    40,
      61,    93,    62,    95,    -1,    88,    40,    55,    40,    61,
      62,    95,    -1,    94,    -1,    93,    58,    94,    -1,    88,
      40,    -1,    88,    40,    56,   117,    -1,    88,    40,    65,
      66,    -1,    88,    -1,    63,    96,    64,    -1,    63,    64,
      -1,    97,    -1,    96,    97,    -1,    89,    -1,    98,    -1,
      95,    -1,    99,    -1,   100,    -1,   103,    -1,   104,    -1,
     105,    -1,   110,    -1,   112,    -1,   114,    -1,   115,    -1,
     116,    -1,   117,    57,    -1,    57,    -1,    23,    61,   117,
      62,    97,    -1,    23,    61,   117,    62,    97,    24,    97,
      -1,    28,    61,   117,    62,    63,   101,    64,    -1,   102,
      -1,   101,   102,    -1,    29,   117,    59,    96,    -1,    29,
     117,    59,    -1,    30,    59,    96,    -1,    30,    59,    -1,
      25,    61,   117,    62,    97,    -1,    26,    97,    25,    61,
     117,    62,    57,    -1,    27,    61,   106,    57,   108,    57,
     109,    62,    97,    -1,   107,    -1,   117,    -1,    -1,    88,
      40,    56,   117,    -1,    88,    40,    -1,   117,    -1,    -1,
     117,    -1,    -1,     6,    53,   111,    57,    -1,   117,    -1,
       8,    -1,   111,    53,   117,    -1,   111,    53,     8,    -1,
       7,    54,   113,    57,    -1,    40,    -1,   113,    54,    40,
      -1,    33,   117,    57,    -1,    33,    57,    -1,    31,    57,
      -1,    32,    57,    -1,   118,    -1,   119,    -1,   125,    56,
     118,    -1,   125,    49,   118,    -1,   125,    50,   118,    -1,
     125,    51,   118,    -1,   125,    52,   118,    -1,   120,    -1,
     119,    46,   120,    -1,   121,    -1,   120,    45,   121,    -1,
     122,    -1,   121,    41,   122,    -1,   121,    42,   122,    -1,
     123,    -1,   122,    67,   123,    -1,   122,    68,   123,    -1,
     122,    43,   123,    -1,   122,    44,   123,    -1,   124,    -1,
     123,    69,   124,    -1,   123,    70,   124,    -1,   125,    -1,
     124,    71,   125,    -1,   124,    72,   125,    -1,   124,    73,
     125,    -1,   126,    -1,    47,   125,    -1,    48,   125,    -1,
      74,   125,    -1,    70,   125,    -1,    75,   125,    -1,    71,
     125,    -1,    10,    88,    61,    62,    -1,    10,    88,    65,
     117,    66,    -1,   127,    -1,   126,    47,    -1,   126,    48,
      -1,   126,    65,   117,    66,    -1,   126,    60,    40,    -1,
      40,    55,    40,    -1,    40,    61,   128,    62,    -1,    40,
      61,    62,    -1,   126,    60,    40,    61,   128,    62,    -1,
     126,    60,    40,    61,    62,    -1,    40,    -1,    36,    -1,
      37,    -1,    38,    -1,    39,    -1,    34,    -1,    35,    -1,
      12,    -1,    61,   117,    62,    -1,   117,    -1,   128,    58,
     117,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   144,   145,   149,   150,   151,   152,   153,
     158,   166,   174,   176,   181,   182,   183,   187,   188,   189,
     193,   194,   195,   199,   200,   204,   205,   212,   213,   214,
     215,   216,   217,   218,   219,   226,   231,   232,   236,   238,
     240,   242,   250,   252,   254,   256,   259,   261,   266,   267,
     271,   273,   275,   277,   285,   286,   290,   291,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   314,   315,   322,   324,   332,   337,   338,   342,   343,
     344,   345,   350,   355,   361,   366,   367,   368,   372,   374,
     379,   380,   384,   385,   392,   397,   399,   401,   403,   411,
     416,   417,   422,   424,   428,   429,   436,   440,   441,   442,
     443,   444,   445,   449,   450,   454,   455,   459,   460,   461,
     465,   466,   467,   468,   469,   473,   474,   475,   479,   480,
     481,   482,   486,   487,   488,   489,   490,   491,   492,   493,
     495,   500,   501,   502,   503,   505,   507,   509,   511,   513,
     515,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     532,   534
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "HEADER_DIRECTIVE", "KEYWORD_USING",
  "KEYWORD_NAMESPACE", "KEYWORD_COUT", "KEYWORD_CIN", "KEYWORD_ENDL",
  "KEYWORD_CLASS", "KEYWORD_NEW", "KEYWORD_DELETE", "KEYWORD_THIS",
  "KEYWORD_PUBLIC", "KEYWORD_PRIVATE", "KEYWORD_PROTECTED",
  "KEYWORD_STRING", "KEYWORD_INT", "KEYWORD_FLOAT", "KEYWORD_CHAR",
  "KEYWORD_DOUBLE", "KEYWORD_BOOL", "KEYWORD_VOID", "KEYWORD_IF",
  "KEYWORD_ELSE", "KEYWORD_WHILE", "KEYWORD_DO", "KEYWORD_FOR",
  "KEYWORD_SWITCH", "KEYWORD_CASE", "KEYWORD_DEFAULT", "KEYWORD_BREAK",
  "KEYWORD_CONTINUE", "KEYWORD_RETURN", "CONST_BOOL_TRUE",
  "CONST_BOOL_FALSE", "CONST_INT", "CONST_FLOAT", "STRING_LITERAL",
  "CHAR_LITERAL", "IDENTIFIER", "OP_EQ", "OP_NEQ", "OP_LEQ", "OP_GEQ",
  "OP_AND", "OP_OR", "OP_INC", "OP_DEC", "OP_PLUS_ASSIGN",
  "OP_MINUS_ASSIGN", "OP_MUL_ASSIGN", "OP_DIV_ASSIGN", "STREAM_OUT",
  "STREAM_IN", "SCOPE_RES", "ASSIGN", "SEMICOLON", "COMMA", "COLON", "DOT",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'&'", "$accept",
  "program", "declaration_list", "declaration", "header_directive",
  "using_directive", "class_definition", "class_body", "class_member",
  "access_specifier", "class_member_list", "class_member_item",
  "type_specifier", "var_declaration", "var_init_list", "var_init",
  "function_definition", "param_list", "param", "compound_statement",
  "statement_list", "statement", "expression_statement", "if_statement",
  "switch_statement", "case_list", "case_clause", "while_statement",
  "do_while_statement", "for_statement", "for_init",
  "var_declaration_inline", "for_cond", "for_update", "cout_statement",
  "stream_output_chain", "cin_statement", "cin_input_chain",
  "return_statement", "break_statement", "continue_statement",
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
     315,   316,   317,   318,   319,   320,   321,    60,    62,    43,
      45,    42,    47,    37,    33,    38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    78,    78,    79,    79,    79,    79,    79,
      80,    81,    82,    82,    83,    83,    83,    84,    84,    84,
      85,    85,    85,    86,    86,    87,    87,    88,    88,    88,
      88,    88,    88,    88,    88,    89,    90,    90,    91,    91,
      91,    91,    92,    92,    92,    92,    92,    92,    93,    93,
      94,    94,    94,    94,    95,    95,    96,    96,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    98,    98,    99,    99,   100,   101,   101,   102,   102,
     102,   102,   103,   104,   105,   106,   106,   106,   107,   107,
     108,   108,   109,   109,   110,   111,   111,   111,   111,   112,
     113,   113,   114,   114,   115,   116,   117,   118,   118,   118,
     118,   118,   118,   119,   119,   120,   120,   121,   121,   121,
     122,   122,   122,   122,   122,   123,   123,   123,   124,   124,
     124,   124,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     128,   128
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     4,     6,     5,     1,     2,     0,     3,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     1,     3,
       4,     3,     6,     5,     6,     5,     8,     7,     1,     3,
       2,     4,     4,     1,     3,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     5,     7,     7,     1,     2,     4,     3,
       3,     2,     5,     7,     9,     1,     1,     0,     4,     2,
       1,     0,     1,     0,     4,     1,     1,     3,     3,     4,
       1,     3,     3,     2,     2,     2,     1,     1,     3,     3,
       3,     3,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     2,     2,     2,     2,     4,
       5,     1,     2,     2,     4,     3,     3,     4,     3,     6,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    10,     0,     0,    32,    27,    28,    29,    30,    31,
      33,    34,     0,     2,     3,     5,     6,     7,     0,     9,
       8,     0,     0,     1,     4,    38,     0,    36,     0,    16,
       0,     0,     0,     0,    35,     0,    11,    20,    21,    22,
       0,    14,     0,    19,    18,     0,     0,   158,   156,   157,
     152,   153,   154,   155,   151,     0,     0,     0,     0,     0,
       0,     0,    39,   106,   107,   113,   115,   117,   120,   125,
     128,   132,   141,     0,    53,     0,    48,     0,    41,    38,
      37,    13,    15,     0,     0,     0,     0,     0,   133,   134,
       0,   136,   138,   135,   137,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   142,   143,     0,     0,    45,     0,    43,
      50,     0,     0,    40,    12,    17,    23,    26,    25,     0,
       0,     0,     0,   146,   148,   160,     0,   159,   114,   128,
     116,   118,   119,   123,   124,   121,   122,   126,   127,   129,
     130,   131,   109,   110,   111,   112,   108,   145,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   151,
      72,    55,     0,    58,    60,     0,    56,    59,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,     0,     0,
       0,    49,    44,    42,    24,    47,     0,   139,     0,     0,
     147,     0,   144,     0,     0,     0,     0,     0,    87,     0,
     104,   105,   103,     0,    54,    57,    71,    51,    52,    46,
     140,   161,   150,     0,    96,     0,    95,   100,     0,     0,
       0,     0,     0,     0,    85,    86,     0,   102,   149,     0,
      94,     0,    99,     0,     0,     0,    89,    91,     0,    98,
      97,   101,    73,    82,     0,     0,     0,    90,     0,     0,
       0,    88,    93,     0,     0,     0,    76,    74,    83,     0,
      92,     0,    81,    75,    77,     0,    79,    80,    84,    78
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,    17,    40,    41,    42,
     125,   126,   172,   173,    26,    27,    20,    75,    76,   174,
     175,   176,   177,   178,   179,   265,   266,   180,   181,   182,
     233,   234,   256,   269,   183,   225,   184,   228,   185,   186,
     187,   188,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,   136
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -149
static const yytype_int16 yypact[] =
{
     581,  -149,    15,   -15,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,    38,   581,  -149,  -149,  -149,  -149,    19,  -149,
    -149,    22,    12,  -149,  -149,   -32,   126,  -149,    65,   598,
      66,   535,    -9,   -18,  -149,    95,  -149,  -149,  -149,  -149,
      51,  -149,    98,  -149,  -149,    99,   540,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,   -19,   535,   535,   535,   535,   535,
     535,   535,  -149,  -149,   116,   124,    58,   -22,   127,   121,
     115,    73,  -149,    -2,   133,    30,  -149,   110,  -149,   -28,
    -149,   138,  -149,   540,   388,    32,   166,   436,  -149,  -149,
     145,  -149,  -149,  -149,  -149,   535,   535,   535,   535,   535,
     535,   535,   535,   535,   535,   535,   535,   535,   535,   535,
     535,   535,   535,  -149,  -149,   169,   535,  -149,   223,  -149,
      18,   540,     0,  -149,  -149,   540,  -149,  -149,  -149,   147,
      36,   153,   535,  -149,  -149,  -149,    56,  -149,   124,  -149,
      58,   -22,   -22,   127,   127,   127,   127,   121,   121,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,   152,   154,   164,
     165,   157,   162,   355,   167,   173,   170,   179,   478,   -21,
    -149,  -149,    95,  -149,  -149,   289,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,   180,   535,
     172,  -149,  -149,  -149,  -149,  -149,   147,  -149,   181,   535,
    -149,   493,  -149,    42,   212,   535,   535,   228,   421,   535,
    -149,  -149,  -149,   207,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,    61,  -149,    77,  -149,  -149,   -10,   203,
     204,   206,   229,   211,  -149,  -149,   210,  -149,  -149,   151,
    -149,   233,  -149,   355,   355,   535,   218,   535,   213,  -149,
    -149,  -149,   251,  -149,   215,   535,   221,  -149,   171,   355,
     222,  -149,   535,   535,   224,   -25,  -149,  -149,  -149,   219,
    -149,   226,   355,  -149,  -149,   355,   355,   355,  -149,   355
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -149,  -149,  -149,   269,  -149,  -149,  -149,  -149,   248,  -149,
    -149,   175,     3,     1,  -149,   254,   -23,   208,   182,   -71,
    -140,  -148,  -149,  -149,  -149,  -149,    25,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,   -31,    31,  -149,   196,   217,   105,    80,   101,    49,
    -149,  -149,   103
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -35
static const yytype_int16 yytable[] =
{
      62,    19,   119,    18,   263,   264,    44,     4,     5,     6,
       7,     8,     9,    10,    19,   207,    18,    44,    77,   -34,
      21,    99,   100,    30,    31,    22,    90,   215,    31,    32,
      43,    11,    18,    33,    86,    74,    86,    33,    23,   273,
      87,    43,    87,    18,   241,   101,   102,   242,    78,    85,
     224,   193,    46,    73,    47,   117,   135,   192,   195,    25,
     128,   118,    28,   118,    37,    38,    39,     4,     5,     6,
       7,     8,     9,    10,   189,    29,    48,    49,    50,    51,
      52,    53,    54,   190,   127,   158,    18,    74,   121,    55,
      56,    11,   122,   131,   121,   252,   253,   132,   196,    97,
      98,   198,   128,    57,    88,    89,    45,    91,    92,    93,
      94,   267,    58,    59,   199,    81,    60,    61,   200,   199,
     113,   114,    36,   238,    74,   219,   127,   278,    18,   215,
     239,   215,   277,   115,   240,    79,   279,   213,   116,   152,
     153,   154,   155,   156,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   149,   150,   151,    83,   217,   249,
      84,    46,    95,    47,   108,   109,   110,   111,   221,    96,
     135,   112,   226,   120,   229,   230,   123,   235,   236,   143,
     144,   145,   146,    34,    35,    48,    49,    50,    51,    52,
      53,    54,   105,   106,   107,   124,   103,   104,    55,    56,
     263,   264,   141,   142,   147,   148,   133,   137,   250,   157,
     118,   232,    57,   201,   254,   197,   257,   203,   205,   204,
     202,    58,    59,   206,   261,    60,    61,   210,   208,   159,
     160,   270,   271,    46,   209,    47,   211,   216,   218,     4,
       5,     6,     7,     8,     9,    10,   161,   220,   162,   163,
     164,   165,   227,   231,   166,   167,   168,    48,    49,    50,
      51,    52,    53,   169,   237,   243,   244,   245,   247,   246,
      55,    56,   248,   251,   255,   259,   258,   260,   262,   268,
     170,   275,    24,   272,    57,   276,   118,   171,    82,    80,
     274,   138,   130,    58,    59,   159,   160,    60,    61,    46,
     194,    47,     0,   191,   223,     4,     5,     6,     7,     8,
       9,    10,   161,   140,   162,   163,   164,   165,     0,     0,
     166,   167,   168,    48,    49,    50,    51,    52,    53,   169,
       0,     0,     0,     0,     0,     0,    55,    56,     0,     0,
       0,     0,     0,     0,     0,     0,   170,     0,     0,     0,
      57,     0,   118,   214,     0,     0,     0,     0,     0,    58,
      59,   159,   160,    60,    61,    46,     0,    47,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,   161,     0,
     162,   163,   164,   165,     0,     0,   166,   167,   168,    48,
      49,    50,    51,    52,    53,   169,     0,     0,     0,     0,
       0,     0,    55,    56,     4,     5,     6,     7,     8,     9,
      10,     0,   170,     0,     0,     0,    57,     0,   118,     0,
       0,     0,     0,     0,     0,    58,    59,     0,    11,    60,
      61,    46,     0,    47,     0,     0,     0,     4,     5,     6,
       7,     8,     9,    10,     0,     0,    46,     0,    47,     0,
     129,     0,     0,     0,     0,    48,    49,    50,    51,    52,
      53,   169,     0,     0,     0,     0,     0,     0,    55,    56,
      48,    49,    50,    51,    52,    53,    54,     0,     0,     0,
       0,     0,    57,    55,    56,     0,     0,     0,    46,     0,
      47,    58,    59,     0,     0,    60,    61,    57,   134,     0,
       0,     0,     0,    46,     0,    47,    58,    59,     0,     0,
      60,    61,    48,    49,    50,    51,    52,    53,    54,     0,
       0,     0,     0,     0,     0,    55,    56,    48,    49,    50,
      51,    52,    53,    54,     0,   212,     0,     0,     0,    57,
      55,    56,     0,     0,     0,    46,     0,    47,    58,    59,
       0,     0,    60,    61,    57,   222,     4,     5,     6,     7,
       8,     9,    10,    58,    59,     0,     0,    60,    61,    48,
      49,    50,    51,    52,    53,    54,     0,     0,     0,     0,
      11,     0,    55,    56,     1,     2,     0,     0,     0,     0,
       3,     0,     0,     0,     0,     0,    57,     4,     5,     6,
       7,     8,     9,    10,     0,    58,    59,     0,     0,    60,
      61,    37,    38,    39,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    11
};

static const yytype_int16 yycheck[] =
{
      31,     0,    73,     0,    29,    30,    29,    16,    17,    18,
      19,    20,    21,    22,    13,   163,    13,    40,    36,    40,
       5,    43,    44,    55,    56,    40,    57,   175,    56,    61,
      29,    40,    29,    65,    55,    32,    55,    65,     0,    64,
      61,    40,    61,    40,    54,    67,    68,    57,    66,    46,
       8,   122,    10,    62,    12,    57,    87,    57,   129,    40,
      83,    63,    40,    63,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    56,    63,    34,    35,    36,    37,
      38,    39,    40,    65,    83,   116,    83,    84,    58,    47,
      48,    40,    62,    61,    58,   243,   244,    65,    62,    41,
      42,   132,   125,    61,    55,    56,    40,    58,    59,    60,
      61,   259,    70,    71,    58,    64,    74,    75,    62,    58,
      47,    48,    57,    62,   121,   196,   125,   275,   125,   277,
      53,   279,   272,    60,    57,    40,   276,   168,    65,   108,
     109,   110,   111,   112,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,    59,   189,     8,
      61,    10,    46,    12,    49,    50,    51,    52,   199,    45,
     201,    56,   203,    40,   205,   206,    66,   208,   209,    99,
     100,   101,   102,    57,    58,    34,    35,    36,    37,    38,
      39,    40,    71,    72,    73,    57,    69,    70,    47,    48,
      29,    30,    97,    98,   103,   104,    40,    62,   239,    40,
      63,   208,    61,    61,   245,    62,   247,    53,    61,    54,
      66,    70,    71,    61,   255,    74,    75,    57,    61,     6,
       7,   262,   263,    10,    61,    12,    57,    57,    66,    16,
      17,    18,    19,    20,    21,    22,    23,    66,    25,    26,
      27,    28,    40,    25,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    57,    62,    62,    61,    57,    40,
      47,    48,    62,    40,    56,    24,    63,    62,    57,    57,
      57,    62,    13,    59,    61,    59,    63,    64,    40,    35,
     265,    95,    84,    70,    71,     6,     7,    74,    75,    10,
     125,    12,    -1,   121,   201,    16,    17,    18,    19,    20,
      21,    22,    23,    96,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,
      61,    -1,    63,    64,    -1,    -1,    -1,    -1,    -1,    70,
      71,     6,     7,    74,    75,    10,    -1,    12,    -1,    -1,
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      25,    26,    27,    28,    -1,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    16,    17,    18,    19,    20,    21,
      22,    -1,    57,    -1,    -1,    -1,    61,    -1,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    -1,    40,    74,
      75,    10,    -1,    12,    -1,    -1,    -1,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    10,    -1,    12,    -1,
      62,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    61,    47,    48,    -1,    -1,    -1,    10,    -1,
      12,    70,    71,    -1,    -1,    74,    75,    61,    62,    -1,
      -1,    -1,    -1,    10,    -1,    12,    70,    71,    -1,    -1,
      74,    75,    34,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    34,    35,    36,
      37,    38,    39,    40,    -1,    57,    -1,    -1,    -1,    61,
      47,    48,    -1,    -1,    -1,    10,    -1,    12,    70,    71,
      -1,    -1,    74,    75,    61,    62,    16,    17,    18,    19,
      20,    21,    22,    70,    71,    -1,    -1,    74,    75,    34,
      35,    36,    37,    38,    39,    40,    -1,    -1,    -1,    -1,
      40,    -1,    47,    48,     3,     4,    -1,    -1,    -1,    -1,
       9,    -1,    -1,    -1,    -1,    -1,    61,    16,    17,    18,
      19,    20,    21,    22,    -1,    70,    71,    -1,    -1,    74,
      75,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     9,    16,    17,    18,    19,    20,    21,
      22,    40,    77,    78,    79,    80,    81,    82,    88,    89,
      92,     5,    40,     0,    79,    40,    90,    91,    40,    63,
      55,    56,    61,    65,    57,    58,    57,    13,    14,    15,
      83,    84,    85,    89,    92,    40,    10,    12,    34,    35,
      36,    37,    38,    39,    40,    47,    48,    61,    70,    71,
      74,    75,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    62,    88,    93,    94,    36,    66,    40,
      91,    64,    84,    59,    61,    88,    55,    61,   125,   125,
     117,   125,   125,   125,   125,    46,    45,    41,    42,    43,
      44,    67,    68,    69,    70,    71,    72,    73,    49,    50,
      51,    52,    56,    47,    48,    60,    65,    57,    63,    95,
      40,    58,    62,    66,    57,    86,    87,    89,    92,    62,
      93,    61,    65,    40,    62,   117,   128,    62,   120,   125,
     121,   122,   122,   123,   123,   123,   123,   124,   124,   125,
     125,   125,   118,   118,   118,   118,   118,    40,   117,     6,
       7,    23,    25,    26,    27,    28,    31,    32,    33,    40,
      57,    64,    88,    89,    95,    96,    97,    98,    99,   100,
     103,   104,   105,   110,   112,   114,   115,   116,   117,    56,
      65,    94,    57,    95,    87,    95,    62,    62,   117,    58,
      62,    61,    66,    53,    54,    61,    61,    97,    61,    61,
      57,    57,    57,   117,    64,    97,    57,   117,    66,    95,
      66,   117,    62,   128,     8,   111,   117,    40,   113,   117,
     117,    25,    88,   106,   107,   117,   117,    57,    62,    53,
      57,    54,    57,    62,    62,    61,    40,    57,    62,     8,
     117,    40,    97,    97,   117,    56,   108,   117,    63,    24,
      62,   117,    57,    29,    30,   101,   102,    97,    57,   109,
     117,   117,    59,    64,   102,    62,    59,    96,    97,    96
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
#line 140 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Parse] C++ program parsed successfully.\n"); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 159 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Token] Include: %s\n", (yyvsp[(1) - (1)].string_val)); free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 167 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Decl] using namespace %s;\n", (yyvsp[(3) - (4)].string_val)); free((yyvsp[(3) - (4)].string_val)); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 175 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Class] class %s { ... };\n", (yyvsp[(2) - (6)].string_val)); free((yyvsp[(2) - (6)].string_val)); ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 177 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Class] class %s { ... }\n", (yyvsp[(2) - (5)].string_val)); free((yyvsp[(2) - (5)].string_val)); ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 193 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Access] public:\n"); ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 194 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Access] private:\n"); ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 195 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Access] protected:\n"); ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 212 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 213 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 214 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 215 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 216 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 217 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 218 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "void"; ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 219 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 227 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Decl] Variable: type=%s\n", (yyvsp[(1) - (3)].string_val)); ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 237 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 239 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 241 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(3) - (4)].string_val)); ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 243 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (3)].string_val)); ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 251 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Func] %s %s(...)\n", (yyvsp[(1) - (6)].string_val), (yyvsp[(2) - (6)].string_val)); free((yyvsp[(1) - (6)].string_val)); free((yyvsp[(2) - (6)].string_val)); ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 253 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Func] %s %s()\n", (yyvsp[(1) - (5)].string_val), (yyvsp[(2) - (5)].string_val)); free((yyvsp[(1) - (5)].string_val)); free((yyvsp[(2) - (5)].string_val)); ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 255 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Func] Forward: %s %s(...)\n", (yyvsp[(1) - (6)].string_val), (yyvsp[(2) - (6)].string_val)); free((yyvsp[(1) - (6)].string_val)); free((yyvsp[(2) - (6)].string_val)); ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 257 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Func] Forward: %s %s()\n", (yyvsp[(1) - (5)].string_val), (yyvsp[(2) - (5)].string_val)); free((yyvsp[(1) - (5)].string_val)); free((yyvsp[(2) - (5)].string_val)); ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 260 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Func] %s::%s(...)\n", (yyvsp[(2) - (8)].string_val), (yyvsp[(4) - (8)].string_val)); free((yyvsp[(1) - (8)].string_val)); free((yyvsp[(2) - (8)].string_val)); free((yyvsp[(4) - (8)].string_val)); ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 262 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Func] %s::%s()\n", (yyvsp[(2) - (7)].string_val), (yyvsp[(4) - (7)].string_val)); free((yyvsp[(1) - (7)].string_val)); free((yyvsp[(2) - (7)].string_val)); free((yyvsp[(4) - (7)].string_val)); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 272 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (2)].string_val)); free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 274 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(2) - (4)].string_val)); free((yyvsp[(4) - (4)].string_val)); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 276 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(2) - (4)].string_val)); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 278 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 314 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (2)].string_val)); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 323 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] if (%s)\n", (yyvsp[(3) - (5)].string_val)); free((yyvsp[(3) - (5)].string_val)); ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 325 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] if-else (%s)\n", (yyvsp[(3) - (7)].string_val)); free((yyvsp[(3) - (7)].string_val)); ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 333 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] switch (%s)\n", (yyvsp[(3) - (7)].string_val)); free((yyvsp[(3) - (7)].string_val)); ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 342 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(2) - (4)].string_val)); ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 343 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(2) - (3)].string_val)); ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 351 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] while (%s)\n", (yyvsp[(3) - (5)].string_val)); free((yyvsp[(3) - (5)].string_val)); ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 356 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] do-while (%s)\n", (yyvsp[(5) - (7)].string_val)); free((yyvsp[(5) - (7)].string_val)); ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 362 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] for(...)\n"); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 367 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 373 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(2) - (4)].string_val)); free((yyvsp[(4) - (4)].string_val)); ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 375 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (2)].string_val)); free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 379 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 384 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 393 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] cout << ...\n"); free((yyvsp[(3) - (4)].string_val)); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 398 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 400 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "endl"; ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 402 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 404 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 412 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] cin >> ...\n"); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 416 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 417 "compiler/cpp/parser/parser_cpp.y"
    { free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 423 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] return %s\n", (yyvsp[(2) - (3)].string_val)); free((yyvsp[(2) - (3)].string_val)); ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 425 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] return;\n"); ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 428 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] break;\n"); ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 429 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Stmt] continue;\n"); ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 436 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 440 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 441 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 442 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 443 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 444 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 445 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 449 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 450 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "||_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 454 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 455 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "&&_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 459 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 460 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "==_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 461 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "!=_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 465 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 466 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "<_expr";  free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 467 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = ">_expr";  free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 468 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "<=_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 469 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = ">=_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 473 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 474 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "+_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 475 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "-_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 479 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 480 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "*_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 481 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "/_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 482 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "%_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 486 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 487 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "++x"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 488 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "--x"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 489 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "!expr"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 490 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "-expr"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 491 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "&expr"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 492 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "*expr"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 494 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "new_obj"; free((yyvsp[(2) - (4)].string_val)); ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 496 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "new_arr"; free((yyvsp[(2) - (5)].string_val)); free((yyvsp[(4) - (5)].string_val)); ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 500 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 501 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "x++"; free((yyvsp[(1) - (2)].string_val)); ;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 502 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "x--"; free((yyvsp[(1) - (2)].string_val)); ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 504 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "arr_access"; free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(3) - (4)].string_val)); ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 506 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 508 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 510 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Expr] Call: %s(...)\n", (yyvsp[(1) - (4)].string_val)); (yyval.string_val) = (yyvsp[(1) - (4)].string_val); free((yyvsp[(3) - (4)].string_val)); ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 512 "compiler/cpp/parser/parser_cpp.y"
    { printf("[Expr] Call: %s()\n", (yyvsp[(1) - (3)].string_val)); (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 514 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (6)].string_val); free((yyvsp[(3) - (6)].string_val)); free((yyvsp[(5) - (6)].string_val)); ;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 516 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (5)].string_val); free((yyvsp[(3) - (5)].string_val)); ;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 520 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 521 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 522 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 523 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 524 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 525 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 526 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 527 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = "this"; ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 528 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(2) - (3)].string_val); ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 533 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 535 "compiler/cpp/parser/parser_cpp.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); free((yyvsp[(3) - (3)].string_val)); ;}
    break;



/* Line 1464 of yacc.c  */
#line 2577 "compiler/cpp/parser/parser_cpp.tab.c"
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
#line 538 "compiler/cpp/parser/parser_cpp.y"


/* ------------------------------------------------------------------ */
/*  Standalone test driver                                              */
/*  Compile:  bison -d -o parser_cpp.tab.c parser_cpp.y               */
/*            flex  -o lex.yy_cpp.c lexer_cpp.l                       */
/*            g++ -o test_cpp parser_cpp.tab.c lex.yy_cpp.c           */
/*  Run:      ./test_cpp ../../examples/hello.cpp                      */
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

    printf("=== PolyCompile — C++ Flex/Bison Parser ===\n");
    yyparse();

    if (cpp_syntax_errors == 0)
        printf("\n[OK] Parsed successfully with 0 syntax errors.\n");
    else
        printf("\n[FAIL] %d syntax error(s) found.\n", cpp_syntax_errors);

    if (argc > 1) fclose(yyin);
    return (cpp_syntax_errors > 0) ? 1 : 0;
}

