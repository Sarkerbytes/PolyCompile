#include "Lexer_CPP.hpp"
#include "../../common/Utilities/DiagnosticEngine.hpp"
#include <cctype>

Lexer_CPP::Lexer_CPP(const std::string& src, const std::string& fname)
    : source(src), filename(fname), cursor(0), line(1), column(1) {
    initKeywords();
}

void Lexer_CPP::initKeywords() {
    keywords = {"include", "iostream", "using", "namespace", "std", "cout", "cin", "endl",
                "string", "bool", "int", "float", "double", "char", "void", "if", "else",
                "while", "do", "for", "switch", "case", "default", "break", "continue",
                "return", "true", "false"};
}

char Lexer_CPP::peek() const {
    if (cursor >= source.size()) return '\0';
    return source[cursor];
}

char Lexer_CPP::get() {
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

void Lexer_CPP::skipWhitespaceAndComments() {
    while (cursor < source.size()) {
        char ch = peek();
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
            get();
        } else if (ch == '/' && cursor + 1 < source.size() && source[cursor + 1] == '/') {
            while (cursor < source.size() && peek() != '\n') get();
        } else if (ch == '/' && cursor + 1 < source.size() && source[cursor + 1] == '*') {
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

std::vector<Token> Lexer_CPP::tokenize() {
    std::vector<Token> tokens;

    while (cursor < source.size()) {
        skipWhitespaceAndComments();
        if (cursor >= source.size()) break;

        int startLine = line;
        int startCol = column;
        char ch = peek();

        if (ch == '#') {
            std::string lex;
            while (cursor < source.size() && peek() != '\n') lex += get();
            tokens.push_back(Token(TokenType::KEYWORD, lex, startLine, startCol));
            continue;
        }

        if (std::isalpha(ch) || ch == '_') {
            std::string lex;
            while (cursor < source.size() && (std::isalnum(peek()) || peek() == '_')) {
                lex += get();
            }
            TokenType type = (keywords.count(lex) > 0) ? TokenType::KEYWORD : TokenType::IDENTIFIER;
            if (lex == "true" || lex == "false") type = TokenType::BOOL_LITERAL;
            tokens.push_back(Token(type, lex, startLine, startCol));
            continue;
        }

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

        if (ch == '"') {
            get();
            std::string lex = "\"";
            while (cursor < source.size() && peek() != '"') {
                if (peek() == '\\' && cursor + 1 < source.size()) lex += get();
                lex += get();
            }
            if (peek() == '"') {
                lex += get();
                tokens.push_back(Token(TokenType::STRING_LITERAL, lex, startLine, startCol));
            } else {
                DiagnosticEngine::logLexicalError(filename, startLine, startCol, "Unterminated string literal in C++ code");
            }
            continue;
        }

        if (ch == '\'') {
            get();
            std::string lex = "'";
            if (peek() == '\\' && cursor + 1 < source.size()) lex += get();
            lex += get();
            if (peek() == '\'') {
                lex += get();
                tokens.push_back(Token(TokenType::CHAR_LITERAL, lex, startLine, startCol));
            } else {
                DiagnosticEngine::logLexicalError(filename, startLine, startCol, "Unterminated char literal in C++ code");
            }
            continue;
        }

        std::string opStr;
        if (ch == '<' || ch == '>') {
            opStr += get();
            if (peek() == ch || peek() == '=') opStr += get();
            tokens.push_back(Token(TokenType::OPERATOR, opStr, startLine, startCol));
            continue;
        }

        if (ch == '=' || ch == '!' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
            opStr += get();
            char nextCh = peek();
            if ((ch == '=' && nextCh == '=') || (ch == '!' && nextCh == '=') ||
                (ch == '+' && (nextCh == '+' || nextCh == '=')) ||
                (ch == '-' && (nextCh == '-' || nextCh == '='))) {
                opStr += get();
            }
            tokens.push_back(Token(TokenType::OPERATOR, opStr, startLine, startCol));
            continue;
        }

        if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' ||
            ch == ';' || ch == ',' || ch == ':') {
            opStr += get();
            tokens.push_back(Token(TokenType::DELIMITER, opStr, startLine, startCol));
            continue;
        }

        std::string unk(1, get());
        DiagnosticEngine::logLexicalError(filename, startLine, startCol, "Unrecognized character in C++ source: " + unk);
    }

    tokens.push_back(Token(TokenType::END_OF_FILE, "EOF", line, column));
    return tokens;
}
