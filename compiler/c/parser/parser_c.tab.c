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
#line 1 "compiler/c/parser/parser_c.y"

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



/* Line 189 of yacc.c  */
#line 106 "compiler/c/parser/parser_c.tab.c"

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

/* Line 214 of yacc.c  */
#line 37 "compiler/c/parser/parser_c.y"

    char* string_val;   /* raw lexeme text  */



/* Line 214 of yacc.c  */
#line 199 "compiler/c/parser/parser_c.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 211 "compiler/c/parser/parser_c.tab.c"

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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   403

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNRULES -- Number of states.  */
#define YYNSTATES  219

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    59,     2,     2,     2,    58,    60,     2,
       2,     2,    56,    54,     2,    55,     2,    57,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,     2,    53,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    34,    36,    40,    42,
      46,    51,    55,    62,    68,    75,    81,    83,    87,    90,
      95,    97,   101,   104,   106,   109,   111,   113,   115,   117,
     119,   121,   123,   125,   127,   129,   131,   133,   135,   138,
     140,   146,   154,   162,   164,   167,   172,   176,   180,   183,
     189,   197,   207,   209,   211,   212,   217,   220,   222,   223,
     225,   226,   232,   237,   243,   247,   250,   253,   256,   258,
     260,   264,   268,   272,   276,   280,   282,   286,   288,   292,
     294,   298,   302,   304,   308,   312,   316,   320,   322,   326,
     330,   332,   336,   340,   344,   346,   349,   352,   355,   358,
     361,   363,   366,   369,   374,   379,   383,   385,   387,   389,
     391,   393,   395,   397,   401,   403
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      62,     0,    -1,    63,    -1,    64,    -1,    63,    64,    -1,
      65,    -1,    70,    -1,    67,    -1,     3,    -1,     4,    -1,
       5,    -1,     6,    -1,     7,    -1,     8,    -1,     9,    -1,
      66,    68,    43,    -1,    69,    -1,    68,    44,    69,    -1,
      29,    -1,    29,    42,    93,    -1,    29,    50,    25,    51,
      -1,    29,    50,    51,    -1,    66,    29,    46,    71,    47,
      73,    -1,    66,    29,    46,    47,    73,    -1,    66,    29,
      46,    71,    47,    43,    -1,    66,    29,    46,    47,    43,
      -1,    72,    -1,    71,    44,    72,    -1,    66,    29,    -1,
      66,    29,    50,    51,    -1,    66,    -1,    48,    74,    49,
      -1,    48,    49,    -1,    75,    -1,    74,    75,    -1,    67,
      -1,    76,    -1,    73,    -1,    77,    -1,    78,    -1,    81,
      -1,    82,    -1,    83,    -1,    88,    -1,    89,    -1,    90,
      -1,    91,    -1,    92,    -1,    93,    43,    -1,    43,    -1,
      10,    46,    93,    47,    75,    -1,    10,    46,    93,    47,
      75,    11,    75,    -1,    15,    46,    93,    47,    48,    79,
      49,    -1,    80,    -1,    79,    80,    -1,    16,    93,    45,
      74,    -1,    16,    93,    45,    -1,    17,    45,    74,    -1,
      17,    45,    -1,    12,    46,    93,    47,    75,    -1,    13,
      75,    12,    46,    93,    47,    43,    -1,    14,    46,    84,
      43,    86,    43,    87,    47,    75,    -1,    85,    -1,    93,
      -1,    -1,    66,    29,    42,    93,    -1,    66,    29,    -1,
      93,    -1,    -1,    93,    -1,    -1,    21,    46,   104,    47,
      43,    -1,    21,    46,    47,    43,    -1,    22,    46,   104,
      47,    43,    -1,    20,    93,    43,    -1,    20,    43,    -1,
      18,    43,    -1,    19,    43,    -1,    94,    -1,    95,    -1,
     101,    42,    94,    -1,   101,    38,    94,    -1,   101,    39,
      94,    -1,   101,    40,    94,    -1,   101,    41,    94,    -1,
      96,    -1,    95,    35,    96,    -1,    97,    -1,    96,    34,
      97,    -1,    98,    -1,    97,    30,    98,    -1,    97,    31,
      98,    -1,    99,    -1,    98,    52,    99,    -1,    98,    53,
      99,    -1,    98,    32,    99,    -1,    98,    33,    99,    -1,
     100,    -1,    99,    54,   100,    -1,    99,    55,   100,    -1,
     101,    -1,   100,    56,   101,    -1,   100,    57,   101,    -1,
     100,    58,   101,    -1,   102,    -1,    36,   101,    -1,    37,
     101,    -1,    59,   101,    -1,    55,   101,    -1,    60,   101,
      -1,   103,    -1,   102,    36,    -1,   102,    37,    -1,   102,
      50,    93,    51,    -1,    29,    46,   104,    47,    -1,    29,
      46,    47,    -1,    29,    -1,    25,    -1,    26,    -1,    27,
      -1,    28,    -1,    23,    -1,    24,    -1,    46,    93,    47,
      -1,    93,    -1,   104,    44,    93,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   133,   133,   138,   139,   143,   144,   145,   152,   160,
     161,   162,   163,   164,   165,   172,   177,   178,   182,   184,
     186,   188,   196,   198,   201,   203,   208,   209,   213,   215,
     217,   225,   226,   230,   231,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   255,   257,
     264,   266,   274,   279,   280,   284,   286,   288,   290,   297,
     305,   313,   318,   319,   321,   326,   328,   333,   334,   338,
     339,   346,   348,   356,   364,   366,   372,   377,   386,   390,
     391,   392,   393,   394,   395,   399,   400,   405,   406,   411,
     412,   413,   417,   418,   419,   420,   421,   425,   426,   427,
     431,   432,   433,   434,   438,   439,   440,   441,   442,   443,
     447,   448,   449,   450,   452,   454,   459,   460,   461,   462,
     463,   464,   465,   466,   470,   472
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "HEADER_DIRECTIVE", "KEYWORD_INT",
  "KEYWORD_FLOAT", "KEYWORD_CHAR", "KEYWORD_DOUBLE", "KEYWORD_BOOL",
  "KEYWORD_VOID", "KEYWORD_IF", "KEYWORD_ELSE", "KEYWORD_WHILE",
  "KEYWORD_DO", "KEYWORD_FOR", "KEYWORD_SWITCH", "KEYWORD_CASE",
  "KEYWORD_DEFAULT", "KEYWORD_BREAK", "KEYWORD_CONTINUE", "KEYWORD_RETURN",
  "KEYWORD_PRINTF", "KEYWORD_SCANF", "CONST_BOOL_TRUE", "CONST_BOOL_FALSE",
  "CONST_INT", "CONST_FLOAT", "STRING_LITERAL", "CHAR_LITERAL",
  "IDENTIFIER", "OP_EQ", "OP_NEQ", "OP_LEQ", "OP_GEQ", "OP_AND", "OP_OR",
  "OP_INC", "OP_DEC", "OP_PLUS_ASSIGN", "OP_MINUS_ASSIGN", "OP_MUL_ASSIGN",
  "OP_DIV_ASSIGN", "ASSIGN", "SEMICOLON", "COMMA", "COLON", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'&'", "$accept", "program",
  "declaration_list", "declaration", "header_directive", "type_specifier",
  "var_declaration", "var_init_list", "var_init", "function_definition",
  "param_list", "param", "compound_statement", "statement_list",
  "statement", "expression_statement", "if_statement", "switch_statement",
  "case_list", "case_clause", "while_statement", "do_while_statement",
  "for_statement", "for_init", "var_declaration_inline", "for_cond",
  "for_update", "printf_statement", "scanf_statement", "return_statement",
  "break_statement", "continue_statement", "expression", "assignment_expr",
  "logical_or_expr", "logical_and_expr", "equality_expr",
  "relational_expr", "additive_expr", "multiplicative_expr", "unary_expr",
  "postfix_expr", "primary_expr", "argument_list", 0
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
     305,   306,    60,    62,    43,    45,    42,    47,    37,    33,
      38
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    63,    64,    64,    64,    65,    66,
      66,    66,    66,    66,    66,    67,    68,    68,    69,    69,
      69,    69,    70,    70,    70,    70,    71,    71,    72,    72,
      72,    73,    73,    74,    74,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    76,    76,
      77,    77,    78,    79,    79,    80,    80,    80,    80,    81,
      82,    83,    84,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    90,    90,    91,    92,    93,    94,
      94,    94,    94,    94,    94,    95,    95,    96,    96,    97,
      97,    97,    98,    98,    98,    98,    98,    99,    99,    99,
     100,   100,   100,   100,   101,   101,   101,   101,   101,   101,
     102,   102,   102,   102,   102,   102,   103,   103,   103,   103,
     103,   103,   103,   103,   104,   104
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     1,     3,
       4,     3,     6,     5,     6,     5,     1,     3,     2,     4,
       1,     3,     2,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       5,     7,     7,     1,     2,     4,     3,     3,     2,     5,
       7,     9,     1,     1,     0,     4,     2,     1,     0,     1,
       0,     5,     4,     5,     3,     2,     2,     2,     1,     1,
       3,     3,     3,     3,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     2,     2,     2,     2,     2,
       1,     2,     2,     4,     4,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     8,     9,    10,    11,    12,    13,    14,     0,     2,
       3,     5,     0,     7,     6,     1,     4,    18,     0,    16,
       0,     0,     0,    15,     0,   121,   122,   117,   118,   119,
     120,   116,     0,     0,     0,     0,     0,     0,    19,    78,
      79,    85,    87,    89,    92,    97,   100,   104,   110,     0,
      30,     0,    26,     0,    21,    18,    17,     0,   105,   106,
       0,   108,   107,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   111,   112,     0,    25,     0,    23,    28,     0,
       0,    20,   115,   124,     0,   123,    86,   100,    88,    90,
      91,    95,    96,    93,    94,    98,    99,   101,   102,   103,
      81,    82,    83,    84,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    32,     0,    35,
      37,     0,    33,    36,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,     0,     0,    27,    24,    22,     0,
     114,   113,     0,     0,     0,    64,     0,    76,    77,    75,
       0,     0,     0,    31,    34,    48,    29,   125,     0,     0,
       0,     0,     0,    62,    63,     0,    74,     0,     0,     0,
       0,     0,     0,    66,    68,     0,    72,     0,     0,    50,
      59,     0,     0,     0,    67,     0,    71,    73,     0,     0,
      65,    70,     0,     0,     0,    53,    51,    60,     0,    69,
       0,    58,    52,    54,     0,    56,    57,    61,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    11,   128,   129,    18,    19,    14,
      51,    52,   130,   131,   132,   133,   134,   135,   204,   205,
     136,   137,   138,   172,   173,   193,   208,   139,   140,   141,
     142,   143,   144,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -189
static const yytype_int16 yypact[] =
{
     146,  -189,  -189,  -189,  -189,  -189,  -189,  -189,    13,   146,
    -189,  -189,   -13,  -189,  -189,  -189,  -189,   -31,    87,  -189,
     343,    52,   -22,  -189,    -5,  -189,  -189,  -189,  -189,  -189,
    -189,   -18,   343,   343,   343,   343,   343,   343,  -189,  -189,
       7,    53,   107,   -27,    85,    70,   119,   -29,  -189,    22,
      42,    35,  -189,    27,  -189,   -30,  -189,   288,  -189,  -189,
      63,  -189,  -189,  -189,   343,   343,   343,   343,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   343,   343,   343,
     343,   343,  -189,  -189,   343,  -189,    26,  -189,    39,   114,
      25,  -189,  -189,  -189,    36,  -189,    53,  -189,   107,   -27,
     -27,    85,    85,    85,    85,    70,    70,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,    95,   117,   125,   236,   127,
     134,   122,   147,   303,   149,   150,  -189,  -189,    -5,  -189,
    -189,   179,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,   166,   159,  -189,  -189,  -189,   343,
    -189,  -189,   343,   343,   199,    88,   343,  -189,  -189,  -189,
     169,   328,   343,  -189,  -189,  -189,  -189,  -189,   167,   170,
     172,   184,   176,  -189,  -189,   173,  -189,   178,    44,    54,
     236,   236,   343,   181,   343,   182,  -189,   183,   186,   213,
    -189,   185,   343,   188,  -189,   128,  -189,  -189,   236,   190,
    -189,   343,   343,   191,    60,  -189,  -189,  -189,   200,  -189,
     192,   236,  -189,  -189,   236,   236,   236,  -189,   236
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -189,  -189,  -189,   226,  -189,     1,     9,  -189,   228,  -189,
    -189,   164,   -47,  -188,  -114,  -189,  -189,  -189,  -189,    64,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,   -20,    89,  -189,   210,   211,   108,    37,   104,
     234,  -189,  -189,    17
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      38,    12,    87,    53,   154,    68,    69,    82,    83,    13,
      12,    20,    20,    15,    60,    21,    17,   164,    13,    22,
      22,    84,    50,   216,    55,    70,    71,   218,    57,    54,
       2,     3,     4,     5,     6,     7,   116,    93,   117,   118,
     119,   120,    64,   148,   121,   122,   123,   124,   125,    25,
      26,    27,    28,    29,    30,    31,     2,     3,     4,     5,
       6,     7,    32,    33,   115,    85,   189,   190,   147,   126,
      86,    88,    34,    86,    86,   127,   202,   203,    91,    89,
     149,    35,    90,   150,   206,    36,    37,    65,   149,   145,
      50,   187,     2,     3,     4,     5,     6,     7,   149,    49,
     217,   188,   164,   160,   164,   101,   102,   103,   104,   212,
      95,    25,    26,    27,    28,    29,    30,    31,     2,     3,
       4,     5,     6,     7,    32,    33,    74,    75,    76,   167,
      23,    24,   168,   169,    34,   174,   175,    66,    67,    72,
      73,    93,    93,    35,   202,   203,   151,    36,    37,     1,
       2,     3,     4,     5,     6,     7,   171,    77,    78,    79,
      80,    81,   191,   152,   194,   157,   110,   111,   112,   113,
     114,   153,   200,   155,    99,   100,   105,   106,   178,   179,
     156,   209,   210,     2,     3,     4,     5,     6,     7,   116,
     158,   117,   118,   119,   120,   161,   162,   121,   122,   123,
     124,   125,    25,    26,    27,    28,    29,    30,    31,   165,
     166,   170,   176,   183,   180,    32,    33,   181,   182,   184,
     185,   186,   126,   192,   198,    34,   196,    86,   163,   197,
     195,   201,   199,   207,    35,    16,   211,   215,    36,    37,
       2,     3,     4,     5,     6,     7,   116,   214,   117,   118,
     119,   120,    56,   146,   121,   122,   123,   124,   125,    25,
      26,    27,    28,    29,    30,    31,    58,    59,   213,    61,
      62,    63,    32,    33,    96,     0,    98,     0,     0,   126,
       0,     0,    34,     0,    86,     0,     0,     0,     0,     0,
       0,    35,     0,     0,     0,    36,    37,     0,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,   107,   108,
     109,    25,    26,    27,    28,    29,    30,    31,     0,     0,
       0,     0,     0,     0,    32,    33,    25,    26,    27,    28,
      29,    30,    31,     0,    34,    92,     0,     0,     0,    32,
      33,     0,     0,    35,     0,     0,   159,    36,    37,    34,
       0,    25,    26,    27,    28,    29,    30,    31,    35,     0,
       0,     0,    36,    37,    32,    33,    25,    26,    27,    28,
      29,    30,    31,     0,    34,   177,     0,     0,     0,    32,
      33,     0,     0,    35,     0,     0,     0,    36,    37,    34,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
       0,     0,    36,    37
};

static const yytype_int16 yycheck[] =
{
      20,     0,    49,    25,   118,    32,    33,    36,    37,     0,
       9,    42,    42,     0,    34,    46,    29,   131,     9,    50,
      50,    50,    21,   211,    29,    52,    53,   215,    46,    51,
       4,     5,     6,     7,     8,     9,    10,    57,    12,    13,
      14,    15,    35,    90,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     4,     5,     6,     7,
       8,     9,    36,    37,    84,    43,   180,   181,    43,    43,
      48,    29,    46,    48,    48,    49,    16,    17,    51,    44,
      44,    55,    47,    47,   198,    59,    60,    34,    44,    50,
      89,    47,     4,     5,     6,     7,     8,     9,    44,    47,
     214,    47,   216,   123,   218,    68,    69,    70,    71,    49,
      47,    23,    24,    25,    26,    27,    28,    29,     4,     5,
       6,     7,     8,     9,    36,    37,    56,    57,    58,   149,
      43,    44,   152,   153,    46,   155,   156,    30,    31,    54,
      55,   161,   162,    55,    16,    17,    51,    59,    60,     3,
       4,     5,     6,     7,     8,     9,   155,    38,    39,    40,
      41,    42,   182,    46,   184,    43,    77,    78,    79,    80,
      81,    46,   192,    46,    66,    67,    72,    73,   161,   162,
      46,   201,   202,     4,     5,     6,     7,     8,     9,    10,
      43,    12,    13,    14,    15,    46,    46,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    43,
      51,    12,    43,    29,    47,    36,    37,    47,    46,    43,
      47,    43,    43,    42,    11,    46,    43,    48,    49,    43,
      48,    43,    47,    43,    55,     9,    45,    45,    59,    60,
       4,     5,     6,     7,     8,     9,    10,    47,    12,    13,
      14,    15,    24,    89,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    32,    33,   204,    35,
      36,    37,    36,    37,    64,    -1,    65,    -1,    -1,    43,
      -1,    -1,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    59,    60,    -1,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    23,    24,    25,    26,
      27,    28,    29,    -1,    46,    47,    -1,    -1,    -1,    36,
      37,    -1,    -1,    55,    -1,    -1,    43,    59,    60,    46,
      -1,    23,    24,    25,    26,    27,    28,    29,    55,    -1,
      -1,    -1,    59,    60,    36,    37,    23,    24,    25,    26,
      27,    28,    29,    -1,    46,    47,    -1,    -1,    -1,    36,
      37,    -1,    -1,    55,    -1,    -1,    -1,    59,    60,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    59,    60
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    62,    63,
      64,    65,    66,    67,    70,     0,    64,    29,    68,    69,
      42,    46,    50,    43,    44,    23,    24,    25,    26,    27,
      28,    29,    36,    37,    46,    55,    59,    60,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    47,
      66,    71,    72,    25,    51,    29,    69,    46,   101,   101,
      93,   101,   101,   101,    35,    34,    30,    31,    32,    33,
      52,    53,    54,    55,    56,    57,    58,    38,    39,    40,
      41,    42,    36,    37,    50,    43,    48,    73,    29,    44,
      47,    51,    47,    93,   104,    47,    96,   101,    97,    98,
      98,    99,    99,    99,    99,   100,   100,   101,   101,   101,
      94,    94,    94,    94,    94,    93,    10,    12,    13,    14,
      15,    18,    19,    20,    21,    22,    43,    49,    66,    67,
      73,    74,    75,    76,    77,    78,    81,    82,    83,    88,
      89,    90,    91,    92,    93,    50,    72,    43,    73,    44,
      47,    51,    46,    46,    75,    46,    46,    43,    43,    43,
      93,    46,    46,    49,    75,    43,    51,    93,    93,    93,
      12,    66,    84,    85,    93,    93,    43,    47,   104,   104,
      47,    47,    46,    29,    43,    47,    43,    47,    47,    75,
      75,    93,    42,    86,    93,    48,    43,    43,    11,    47,
      93,    43,    16,    17,    79,    80,    75,    43,    87,    93,
      93,    45,    49,    80,    47,    45,    74,    75,    74
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
#line 134 "compiler/c/parser/parser_c.y"
    { printf("[Parse] C program parsed successfully.\n"); ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 153 "compiler/c/parser/parser_c.y"
    { printf("[Token] Header directive: %s\n", (yyvsp[(1) - (1)].string_val)); free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 160 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 161 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 162 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 163 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 164 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 165 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "void"; ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 173 "compiler/c/parser/parser_c.y"
    { printf("[Decl] Variable declaration: type=%s\n", (yyvsp[(1) - (3)].string_val)); ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 183 "compiler/c/parser/parser_c.y"
    { printf("[Decl] Variable: %s\n", (yyvsp[(1) - (1)].string_val)); free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 185 "compiler/c/parser/parser_c.y"
    { printf("[Decl] Variable: %s (with initializer)\n", (yyvsp[(1) - (3)].string_val)); free((yyvsp[(1) - (3)].string_val)); ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 187 "compiler/c/parser/parser_c.y"
    { printf("[Decl] Array: %s[%s]\n", (yyvsp[(1) - (4)].string_val), (yyvsp[(3) - (4)].string_val)); free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(3) - (4)].string_val)); ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 189 "compiler/c/parser/parser_c.y"
    { printf("[Decl] Array: %s[]\n", (yyvsp[(1) - (3)].string_val)); free((yyvsp[(1) - (3)].string_val)); ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 197 "compiler/c/parser/parser_c.y"
    { printf("[Func] Function: %s %s(...)\n", (yyvsp[(1) - (6)].string_val), (yyvsp[(2) - (6)].string_val)); free((yyvsp[(1) - (6)].string_val)); free((yyvsp[(2) - (6)].string_val)); ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 199 "compiler/c/parser/parser_c.y"
    { printf("[Func] Function: %s %s()\n", (yyvsp[(1) - (5)].string_val), (yyvsp[(2) - (5)].string_val)); free((yyvsp[(1) - (5)].string_val)); free((yyvsp[(2) - (5)].string_val)); ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 202 "compiler/c/parser/parser_c.y"
    { printf("[Func] Forward decl: %s %s(...)\n", (yyvsp[(1) - (6)].string_val), (yyvsp[(2) - (6)].string_val)); free((yyvsp[(1) - (6)].string_val)); free((yyvsp[(2) - (6)].string_val)); ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 204 "compiler/c/parser/parser_c.y"
    { printf("[Func] Forward decl: %s %s()\n", (yyvsp[(1) - (5)].string_val), (yyvsp[(2) - (5)].string_val)); free((yyvsp[(1) - (5)].string_val)); free((yyvsp[(2) - (5)].string_val)); ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 214 "compiler/c/parser/parser_c.y"
    { printf("[Param] %s %s\n", (yyvsp[(1) - (2)].string_val), (yyvsp[(2) - (2)].string_val)); free((yyvsp[(1) - (2)].string_val)); free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 216 "compiler/c/parser/parser_c.y"
    { printf("[Param] %s %s[]\n", (yyvsp[(1) - (4)].string_val), (yyvsp[(2) - (4)].string_val)); free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(2) - (4)].string_val)); ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 218 "compiler/c/parser/parser_c.y"
    { printf("[Param] %s (unnamed)\n", (yyvsp[(1) - (1)].string_val)); free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 256 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] Expression statement: %s\n", (yyvsp[(1) - (2)].string_val)); free((yyvsp[(1) - (2)].string_val)); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 265 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] if (%s)\n", (yyvsp[(3) - (5)].string_val)); free((yyvsp[(3) - (5)].string_val)); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 267 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] if (%s) ... else ...\n", (yyvsp[(3) - (7)].string_val)); free((yyvsp[(3) - (7)].string_val)); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 275 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] switch (%s)\n", (yyvsp[(3) - (7)].string_val)); free((yyvsp[(3) - (7)].string_val)); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 285 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] case %s:\n", (yyvsp[(2) - (4)].string_val)); free((yyvsp[(2) - (4)].string_val)); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 287 "compiler/c/parser/parser_c.y"
    { free((yyvsp[(2) - (3)].string_val)); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 289 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] default:\n"); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 298 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] while (%s)\n", (yyvsp[(3) - (5)].string_val)); free((yyvsp[(3) - (5)].string_val)); ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 306 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] do...while (%s)\n", (yyvsp[(5) - (7)].string_val)); free((yyvsp[(5) - (7)].string_val)); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 314 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] for(...)\n"); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 320 "compiler/c/parser/parser_c.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 327 "compiler/c/parser/parser_c.y"
    { printf("[Decl] for-init: %s %s\n", (yyvsp[(1) - (4)].string_val), (yyvsp[(2) - (4)].string_val)); free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(2) - (4)].string_val)); free((yyvsp[(4) - (4)].string_val)); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 329 "compiler/c/parser/parser_c.y"
    { printf("[Decl] for-init: %s %s\n", (yyvsp[(1) - (2)].string_val), (yyvsp[(2) - (2)].string_val)); free((yyvsp[(1) - (2)].string_val)); free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 333 "compiler/c/parser/parser_c.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 338 "compiler/c/parser/parser_c.y"
    { free((yyvsp[(1) - (1)].string_val)); ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 347 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] printf(...)\n"); free((yyvsp[(3) - (5)].string_val)); ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 349 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] printf()\n"); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 357 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] scanf(...)\n"); free((yyvsp[(3) - (5)].string_val)); ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 365 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] return %s\n", (yyvsp[(2) - (3)].string_val)); free((yyvsp[(2) - (3)].string_val)); ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 367 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] return;\n"); ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 373 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] break;\n"); ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 378 "compiler/c/parser/parser_c.y"
    { printf("[Stmt] continue;\n"); ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 386 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 390 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 391 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); /* simplified */ ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 392 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 393 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 394 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 395 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 399 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 401 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "||_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 405 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 407 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "&&_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 411 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 412 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "==_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 413 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "!=_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 417 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 418 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "<_expr";  free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 419 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = ">_expr";  free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 420 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "<=_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 421 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = ">=_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 425 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 426 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "+_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 427 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "-_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 431 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 432 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "*_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 433 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "/_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 434 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "%_expr"; free((yyvsp[(1) - (3)].string_val)); free((yyvsp[(3) - (3)].string_val)); ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 438 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 439 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "++x"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 440 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "--x"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 441 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "!expr"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 442 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "-expr"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 443 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "&expr"; free((yyvsp[(2) - (2)].string_val)); ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 447 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 448 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "x++"; free((yyvsp[(1) - (2)].string_val)); ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 449 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "x--"; free((yyvsp[(1) - (2)].string_val)); ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 451 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = "arr_access"; free((yyvsp[(1) - (4)].string_val)); free((yyvsp[(3) - (4)].string_val)); ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 453 "compiler/c/parser/parser_c.y"
    { printf("[Expr] Call: %s(...)\n", (yyvsp[(1) - (4)].string_val)); (yyval.string_val) = (yyvsp[(1) - (4)].string_val); free((yyvsp[(3) - (4)].string_val)); ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 455 "compiler/c/parser/parser_c.y"
    { printf("[Expr] Call: %s()\n", (yyvsp[(1) - (3)].string_val)); (yyval.string_val) = (yyvsp[(1) - (3)].string_val); ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 459 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 460 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 461 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 462 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 463 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 464 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 465 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 466 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(2) - (3)].string_val); ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 471 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (1)].string_val); ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 473 "compiler/c/parser/parser_c.y"
    { (yyval.string_val) = (yyvsp[(1) - (3)].string_val); free((yyvsp[(3) - (3)].string_val)); ;}
    break;



/* Line 1464 of yacc.c  */
#line 2298 "compiler/c/parser/parser_c.tab.c"
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
#line 476 "compiler/c/parser/parser_c.y"


/* ------------------------------------------------------------------ */
/*  main() – standalone test driver                                     */
/*  Compile:  bison -d -o parser_c.tab.c parser_c.y                   */
/*            flex  -o lex.yy_c.c  lexer_c.l                          */
/*            g++ -o test_c parser_c.tab.c lex.yy_c.c                 */
/*  Run:      ./test_c < ../../examples/hello.c                        */
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

    printf("=== PolyCompile — C Flex/Bison Parser ===\n");
    yyparse();

    if (c_syntax_errors == 0)
        printf("\n[OK] Parsed successfully with 0 syntax errors.\n");
    else
        printf("\n[FAIL] %d syntax error(s) found.\n", c_syntax_errors);

    if (argc > 1) fclose(yyin);
    return (c_syntax_errors > 0) ? 1 : 0;
}

