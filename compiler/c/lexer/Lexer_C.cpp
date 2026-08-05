#include "Lexer_C.hpp"
#include "../../common/Utilities/DiagnosticEngine.hpp"
#include <cctype>

Lexer_C::Lexer_C(const std::string& src, const std::string& fname)
    : source(src), filename(fname), cursor(0), line(1), column(1) {
    initKeywords();
}

void Lexer_C::initKeywords() {
    keywords = {"include", "stdio.h", "int", "float", "char", "double", "bool", "void",
                "printf", "scanf", "if", "else", "while", "do", "for", "switch", "case",
                "default", "break", "continue", "return", "true", "false"};
}

char Lexer_C::peek() const {
    if (cursor >= source.size()) return '\0';
    return source[cursor];
}

char Lexer_C::get() {
    if (cursor >= source.size()) return '\0';
    char ch = source[cursor++];
    if (ch == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return ch;
}

void Lexer_C::skipWhitespaceAndComments() {
    while (cursor < source.size()) {
        char ch = peek();
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
            get();
        } else if (ch == '/' && cursor + 1 < source.size() && source[cursor + 1] == '/') {
            // Single-line comment
            while (cursor < source.size() && peek() != '\n') get();
        } else if (ch == '/' && cursor + 1 < source.size() && source[cursor + 1] == '*') {
            // Multi-line comment
            get(); get();
            while (cursor < source.size()) {
                if (peek() == '*' && cursor + 1 < source.size() && source[cursor + 1] == '/') {
                    get(); get();
                    break;
                }
                get();
            }
        } else {
            break;
        }
    }
}

std::vector<Token> Lexer_C::tokenize() {
    std::vector<Token> tokens;

    while (cursor < source.size()) {
        skipWhitespaceAndComments();
        if (cursor >= source.size()) break;

        int startLine = line;
        int startCol = column;
        char ch = peek();

        // Check C preprocessor directives #include <stdio.h>
        if (ch == '#') {
            std::string lex;
            while (cursor < source.size() && peek() != '\n') {
                lex += get();
            }
            tokens.push_back(Token(TokenType::KEYWORD, lex, startLine, startCol));
            continue;
        }

        // Identifiers / Keywords
        if (std::isalpha(ch) || ch == '_') {
            std::string lex;
            while (cursor < source.size() && (std::isalnum(peek()) || peek() == '_' || peek() == '.')) {
                lex += get();
            }
            TokenType type = (keywords.count(lex) > 0) ? TokenType::KEYWORD : TokenType::IDENTIFIER;
            if (lex == "true" || lex == "false") type = TokenType::BOOL_LITERAL;
            tokens.push_back(Token(type, lex, startLine, startCol));
            continue;
        }

        // Numbers (Int / Float)
        if (std::isdigit(ch)) {
            std::string lex;
            bool isFloat = false;
            while (cursor < source.size() && (std::isdigit(peek()) || peek() == '.')) {
                if (peek() == '.') isFloat = true;
                lex += get();
            }
            tokens.push_back(Token(isFloat ? TokenType::FLOAT_LITERAL : TokenType::INT_LITERAL, lex, startLine, startCol));
            continue;
        }

        // String Literals
        if (ch == '"') {
            get(); // skip open quote
            std::string lex = "\"";
            while (cursor < source.size() && peek() != '"') {
                if (peek() == '\\' && cursor + 1 < source.size()) {
                    lex += get();
                }
                lex += get();
            }
            if (peek() == '"') {
                lex += get(); // skip close quote
                tokens.push_back(Token(TokenType::STRING_LITERAL, lex, startLine, startCol));
            } else {
                DiagnosticEngine::logLexicalError(filename, startLine, startCol, "Unterminated string literal in C code");
            }
            continue;
        }

        // Character Literals
        if (ch == '\'') {
            get();
            std::string lex = "'";
            if (peek() == '\\' && cursor + 1 < source.size()) lex += get();
            lex += get();
            if (peek() == '\'') {
                lex += get();
                tokens.push_back(Token(TokenType::CHAR_LITERAL, lex, startLine, startCol));
            } else {
                DiagnosticEngine::logLexicalError(filename, startLine, startCol, "Unterminated character literal in C code");
            }
            continue;
        }

        // Operators (Multi-char and single-char)
        std::string opStr;
        if (ch == '=' || ch == '!' || ch == '<' || ch == '>' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
            opStr += get();
            char nextCh = peek();
            if ((ch == '=' && nextCh == '=') || (ch == '!' && nextCh == '=') ||
                (ch == '<' && nextCh == '=') || (ch == '>' && nextCh == '=') ||
                (ch == '+' && (nextCh == '+' || nextCh == '=')) ||
                (ch == '-' && (nextCh == '-' || nextCh == '=')) ||
                (ch == '&' && nextCh == '&') || (ch == '|' && nextCh == '|')) {
                opStr += get();
            }
            tokens.push_back(Token(TokenType::OPERATOR, opStr, startLine, startCol));
            continue;
        }

        // Delimiters
        if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' ||
            ch == ';' || ch == ',' || ch == ':' || ch == '&') {
            opStr += get();
            tokens.push_back(Token(TokenType::DELIMITER, opStr, startLine, startCol));
            continue;
        }

        // Unknown character
        std::string unk(1, get());
        DiagnosticEngine::logLexicalError(filename, startLine, startCol, "Unrecognized character in C source: " + unk);
    }

    tokens.push_back(Token(TokenType::END_OF_FILE, "EOF", line, column));
    return tokens;
}
