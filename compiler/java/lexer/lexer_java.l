%{
/*
 * lexer_java.l – Flex Lexer for Java Language
 * PolyCompile Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YY_NEVER_INTERACTIVE 1

#include "parser_java.tab.h"

int java_line = 1;
int java_col  = 1;

static char* safe_strdup(const char* src) {
    if (!src) return NULL;
    char* dst = (char*)malloc(strlen(src) + 1);
    if (dst) strcpy(dst, src);
    return dst;
}

#define YY_USER_ACTION  java_col += yyleng;

%}

%option noyywrap
%option yylineno
%option batch

DIGIT       [0-9]
LETTER      [a-zA-Z_]
ALNUM       [a-zA-Z0-9_]
INT_CONST   {DIGIT}+[lL]?
FLOAT_CONST {DIGIT}+"."{DIGIT}*[fFdD]?|"."{DIGIT}+[fFdD]?
ID          {LETTER}{ALNUM}*

%x BLOCK_COMMENT

%%

    /* Whitespace & Comments */
[ \t\r]+            { }
\n                  { java_line++; java_col = 1; }
"//"[^\n]*          { }

"/*"                { BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>"*/" { BEGIN(INITIAL); }
<BLOCK_COMMENT>\n   { java_line++; java_col = 1; }
<BLOCK_COMMENT>.    { }

    /* Package & Import */
"import"[ \t][^\n;]*";" { printf("[Token] import: %s\n", yytext); }
"package"[ \t][^\n;]*";" { printf("[Token] package: %s\n", yytext); }

    /* Annotations */
"@"{ID}     { yylval.string_val = safe_strdup(yytext); return ANNOTATION; }

    /* Java Keywords */
"class"         { return KEYWORD_CLASS;     }
"interface"     { return KEYWORD_INTERFACE; }
"extends"       { return KEYWORD_EXTENDS;   }
"implements"    { return KEYWORD_IMPLEMENTS;}
"public"        { return KEYWORD_PUBLIC;    }
"private"       { return KEYWORD_PRIVATE;   }
"protected"     { return KEYWORD_PROTECTED; }
"static"        { return KEYWORD_STATIC;    }
"final"         { return KEYWORD_FINAL;     }
"abstract"      { return KEYWORD_ABSTRACT;  }
"new"           { return KEYWORD_NEW;       }
"this"          { return KEYWORD_THIS;      }
"super"         { return KEYWORD_SUPER;     }
"instanceof"    { return KEYWORD_INSTANCEOF;}
"throws"        { return KEYWORD_THROWS;    }
"throw"         { return KEYWORD_THROW;     }
"try"           { return KEYWORD_TRY;       }
"catch"         { return KEYWORD_CATCH;     }
"finally"       { return KEYWORD_FINALLY;   }

    /* Primitive types */
"int"           { yylval.string_val = safe_strdup(yytext); return KEYWORD_INT;     }
"float"         { yylval.string_val = safe_strdup(yytext); return KEYWORD_FLOAT;   }
"double"        { yylval.string_val = safe_strdup(yytext); return KEYWORD_DOUBLE;  }
"char"          { yylval.string_val = safe_strdup(yytext); return KEYWORD_CHAR;    }
"boolean"       { yylval.string_val = safe_strdup(yytext); return KEYWORD_BOOLEAN; }
"byte"          { yylval.string_val = safe_strdup(yytext); return KEYWORD_BYTE;    }
"short"         { yylval.string_val = safe_strdup(yytext); return KEYWORD_SHORT;   }
"long"          { yylval.string_val = safe_strdup(yytext); return KEYWORD_LONG;    }
"void"          { return KEYWORD_VOID;   }
"String"        { yylval.string_val = safe_strdup(yytext); return KEYWORD_STRING;  }

    /* Control-flow */
"if"            { return KEYWORD_IF;      }
"else"          { return KEYWORD_ELSE;    }
"while"         { return KEYWORD_WHILE;   }
"do"            { return KEYWORD_DO;      }
"for"           { return KEYWORD_FOR;     }
"switch"        { return KEYWORD_SWITCH;  }
"case"          { return KEYWORD_CASE;    }
"default"       { return KEYWORD_DEFAULT; }
"break"         { return KEYWORD_BREAK;   }
"continue"      { return KEYWORD_CONTINUE;}
"return"        { return KEYWORD_RETURN;  }

    /* Constants */
"true"          { yylval.string_val = safe_strdup(yytext); return CONST_BOOL_TRUE;  }
"false"         { yylval.string_val = safe_strdup(yytext); return CONST_BOOL_FALSE; }
"null"          { yylval.string_val = safe_strdup(yytext); return CONST_NULL;       }

    /* Standard library identifiers */
"System"        { yylval.string_val = safe_strdup(yytext); return IDENTIFIER; }
"Scanner"       { yylval.string_val = safe_strdup(yytext); return IDENTIFIER; }
"Math"          { yylval.string_val = safe_strdup(yytext); return IDENTIFIER; }

    /* Identifiers */
{ID}    { yylval.string_val = safe_strdup(yytext); return IDENTIFIER; }

    /* Literals */
{INT_CONST}         { yylval.string_val = safe_strdup(yytext); return CONST_INT;   }
{FLOAT_CONST}       { yylval.string_val = safe_strdup(yytext); return CONST_FLOAT; }
\"([^\"\\]|\\.)*\"  { yylval.string_val = safe_strdup(yytext); return STRING_LITERAL; }
\'([^\'\\]|\\.)\'   { yylval.string_val = safe_strdup(yytext); return CHAR_LITERAL;   }

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

    /* Single-char Operators & Delimiters */
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
.   { fprintf(stderr, "[Lexical Error] Line %d, Col %d: Unknown character '%s'\n", java_line, java_col - 1, yytext); }


%%
