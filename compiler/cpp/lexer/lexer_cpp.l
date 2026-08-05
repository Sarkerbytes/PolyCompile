%{
/*
 * lexer_cpp.l – Flex Lexer for C++ Language
 * PolyCompile Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YY_NEVER_INTERACTIVE 1

#include "parser_cpp.tab.h"

int cpp_line = 1;
int cpp_col  = 1;

static char* safe_strdup(const char* src) {
    if (!src) return NULL;
    char* dst = (char*)malloc(strlen(src) + 1);
    if (dst) strcpy(dst, src);
    return dst;
}

#define YY_USER_ACTION  cpp_col += yyleng;

%}

%option noyywrap
%option yylineno
%option batch

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ALNUM       [a-zA-Z0-9_]
INT_CONST   {DIGIT}+
FLOAT_CONST {DIGIT}+"."{DIGIT}*|"."{DIGIT}+
ID          {LETTER}{ALNUM}*

%x BLOCK_COMMENT

%%

    /* Whitespace & Comments */
[ \t\r]+            { }
\n                  { cpp_line++; cpp_col = 1; }
"//"[^\n]*          { }

"/*"                { BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>"*/" { BEGIN(INITIAL); }
<BLOCK_COMMENT>\n   { cpp_line++; cpp_col = 1; }
<BLOCK_COMMENT>.    { }

    /* Preprocessor / Include */
"#include"[ \t]*"<"[a-zA-Z0-9_./]+">" {
    yylval.string_val = safe_strdup(yytext);
    return HEADER_DIRECTIVE;
}
"#include"[ \t]*"\""[a-zA-Z0-9_./]+"\"" {
    yylval.string_val = safe_strdup(yytext);
    return HEADER_DIRECTIVE;
}
"#define"[^\n]*     { }

    /* C++ Keywords */
"using"     { return KEYWORD_USING;     }
"namespace" { return KEYWORD_NAMESPACE; }
"std"       { yylval.string_val = safe_strdup(yytext); return IDENTIFIER; }
"cout"      { return KEYWORD_COUT;      }
"cin"       { return KEYWORD_CIN;       }
"endl"      { return KEYWORD_ENDL;      }
"class"     { return KEYWORD_CLASS;     }
"new"       { return KEYWORD_NEW;       }
"delete"    { return KEYWORD_DELETE;    }
"this"      { return KEYWORD_THIS;      }
"public"    { return KEYWORD_PUBLIC;    }
"private"   { return KEYWORD_PRIVATE;   }
"protected" { return KEYWORD_PROTECTED; }
"string"    { yylval.string_val = safe_strdup(yytext); return KEYWORD_STRING; }

    /* Shared Keywords */
"int"       { yylval.string_val = safe_strdup(yytext); return KEYWORD_INT;      }
"float"     { yylval.string_val = safe_strdup(yytext); return KEYWORD_FLOAT;    }
"char"      { yylval.string_val = safe_strdup(yytext); return KEYWORD_CHAR;     }
"double"    { yylval.string_val = safe_strdup(yytext); return KEYWORD_DOUBLE;   }
"bool"      { yylval.string_val = safe_strdup(yytext); return KEYWORD_BOOL;     }
"void"      { return KEYWORD_VOID;   }
"if"        { return KEYWORD_IF;     }
"else"      { return KEYWORD_ELSE;   }
"while"     { return KEYWORD_WHILE;  }
"do"        { return KEYWORD_DO;     }
"for"       { return KEYWORD_FOR;    }
"switch"    { return KEYWORD_SWITCH; }
"case"      { return KEYWORD_CASE;   }
"default"   { return KEYWORD_DEFAULT;}
"break"     { return KEYWORD_BREAK;  }
"continue"  { return KEYWORD_CONTINUE;}
"return"    { return KEYWORD_RETURN; }
"true"      { yylval.string_val = safe_strdup(yytext); return CONST_BOOL_TRUE;  }
"false"     { yylval.string_val = safe_strdup(yytext); return CONST_BOOL_FALSE; }

    /* Identifiers */
{ID}        { yylval.string_val = safe_strdup(yytext); return IDENTIFIER; }

    /* Literals */
{INT_CONST}         { yylval.string_val = safe_strdup(yytext); return CONST_INT;   }
{FLOAT_CONST}       { yylval.string_val = safe_strdup(yytext); return CONST_FLOAT; }
\"([^\"\\]|\\.)*\"  { yylval.string_val = safe_strdup(yytext); return STRING_LITERAL; }
\'([^\'\\]|\\.)\'   { yylval.string_val = safe_strdup(yytext); return CHAR_LITERAL;   }

    /* C++ Stream Operators */
"<<"    { return STREAM_OUT; }
">>"    { return STREAM_IN;  }

    /* Multi-character Operators */
"=="    { return OP_EQ;   }
"!="    { return OP_NEQ;  }
"<="    { return OP_LEQ;  }
">="    { return OP_GEQ;  }
"&&"    { return OP_AND;  }
"||"    { return OP_OR;   }
"++"    { return OP_INC;  }
"--"    { return OP_DEC;  }
"+="    { return OP_PLUS_ASSIGN;  }
"-="    { return OP_MINUS_ASSIGN; }
"*="    { return OP_MUL_ASSIGN;   }
"/="    { return OP_DIV_ASSIGN;   }
"::"    { return SCOPE_RES; }

    /* Operators & Delimiters */
"="     { return ASSIGN;     }
"+"     { return '+';        }
"-"     { return '-';        }
"*"     { return '*';        }
"/"     { return '/';        }
"%"     { return '%';        }
"<"     { return '<';        }
">"     { return '>';        }
"!"     { return '!';        }
"&"     { return '&';        }
"|"     { return '|';        }
"~"     { return '~';        }

"("     { return LPAREN;     }
")"     { return RPAREN;     }
"{"     { return LBRACE;     }
"}"     { return RBRACE;     }
"["     { return LBRACKET;   }
"]"     { return RBRACKET;   }
";"     { return SEMICOLON;  }
","     { return COMMA;      }
":"     { return COLON;      }
"."     { return DOT;        }

    /* Unknown */
.   { fprintf(stderr, "[Lexical Error] Line %d, Col %d: Unknown character '%s'\n", cpp_line, cpp_col - 1, yytext); }

%%
