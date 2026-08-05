#include "Lexer_Java.hpp"
#include "../../common/Utilities/DiagnosticEngine.hpp"
#include <cctype>

Lexer_Java::Lexer_Java(const std::string& src, const std::string& fname)
    : source(src), filename(fname), cursor(0), line(1), column(1) {
    initKeywords();
}

void Lexer_Java::initKeywords() {
    keywords = {
        "class", "public", "private", "protected", "static", "final", "abstract",
        "void", "int", "float", "double", "char", "boolean", "String", "long", "short", "byte",
        "if", "else", "while", "do", "for", "switch", "case", "default",
        "break", "continue", "return", "new", "import", "package",
        "true", "false", "null",
        "System", "out", "println", "print", "Scanner"
    };
}

char Lexer_Java::peek() const {
    if (cursor >= source.size()) return '\0';
    return source[cursor];
}

char Lexer_Java::get() {
    if (cursor >= source.size()) return '\0';
    char ch = source[cursor++];
    if (ch == '\n') { line++; column = 1; } else { column++; }
    return ch;
}

void Lexer_Java::skipWhitespaceAndComments() {
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
                    get(); get(); break;
                }
                get();
            }
        } else {
            break;
        }
    }
}

std::vector<Token> Lexer_Java::tokenize() {
    std::vector<Token> tokens;

    while (cursor < source.size()) {
        skipWhitespaceAndComments();
        if (cursor >= source.size()) break;

        int startLine = line;
        int startCol = column;
        char ch = peek();

        // Skip import / package directives
        if (ch == 'i' || ch == 'p') {
            size_t savedCursor = cursor;
            int savedLine = line;
            int savedCol = column;
            std::string lex;
            while (cursor < source.size() && (std::isalnum(peek()) || peek() == '_')) {
                lex += get();
            }
            if (lex == "import" || lex == "package") {
                while (cursor < source.size() && peek() != ';' && peek() != '\n') get();
                if (peek() == ';') get();
                continue;
            }
            // Backtrack
            cursor = savedCursor;
            line = savedLine;
            column = savedCol;
        }

        // Identifier or keyword
        if (std::isalpha(ch) || ch == '_') {
            std::string lex;
            while (cursor < source.size() && (std::isalnum(peek()) || peek() == '_')) {
                lex += get();
            }
            // Handle qualified identifiers like System.out.println
            if (peek() == '.') {
                lex += get(); // consume '.'
                std::string part;
                while (cursor < source.size() && (std::isalnum(peek()) || peek() == '_')) {
                    part += get();
                }
                if (part == "out" && peek() == '.') {
                    lex += part + get();
                    std::string method;
                    while (cursor < source.size() && (std::isalnum(peek()) || peek() == '_')) {
                        method += get();
                    }
                    lex += method;
                } else {
                    lex += part;
                }
            }
            TokenType type = (keywords.count(lex) > 0 ||
                              lex.find("System.out") == 0 ||
                              lex == "Scanner") ? TokenType::KEYWORD : TokenType::IDENTIFIER;
            if (lex == "true" || lex == "false") type = TokenType::BOOL_LITERAL;
            if (lex == "null") type = TokenType::KEYWORD;
            tokens.push_back(Token(type, lex, startLine, startCol));
            continue;
        }

        // Numbers
        if (std::isdigit(ch)) {
            std::string lex;
            bool isFloat = false;
            while (cursor < source.size() && (std::isdigit(peek()) || peek() == '.')) {
                if (peek() == '.') isFloat = true;
                lex += get();
            }
            // Java long suffix
            if (peek() == 'L' || peek() == 'l') get();
            tokens.push_back(Token(isFloat ? TokenType::FLOAT_LITERAL : TokenType::INT_LITERAL, lex, startLine, startCol));
            continue;
        }

        // String literal
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
                DiagnosticEngine::logLexicalError(filename, startLine, startCol, "Unterminated string literal in Java code");
            }
            continue;
        }

        // Character literal
        if (ch == '\'') {
            get();
            std::string lex = "'";
            if (peek() == '\\' && cursor + 1 < source.size()) lex += get();
            lex += get();
            if (peek() == '\'') {
                lex += get();
                tokens.push_back(Token(TokenType::CHAR_LITERAL, lex, startLine, startCol));
            } else {
                DiagnosticEngine::logLexicalError(filename, startLine, startCol, "Unterminated char literal in Java code");
            }
            continue;
        }

        // Operators
        std::string opStr;
        if (ch == '=' || ch == '!' || ch == '<' || ch == '>' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
            opStr += get();
            char nextCh = peek();
            if ((ch == '=' && nextCh == '=') || (ch == '!' && nextCh == '=') ||
                (ch == '<' && nextCh == '=') || (ch == '>' && nextCh == '=') ||
                (ch == '+' && (nextCh == '+' || nextCh == '=')) ||
                (ch == '-' && (nextCh == '-' || nextCh == '='))) {
                opStr += get();
            }
            tokens.push_back(Token(TokenType::OPERATOR, opStr, startLine, startCol));
            continue;
        }

        // Delimiters
        if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' ||
            ch == ';' || ch == ',' || ch == ':' || ch == '.' || ch == '@') {
            opStr += get();
            tokens.push_back(Token(TokenType::DELIMITER, opStr, startLine, startCol));
            continue;
        }

        // Unknown
        std::string unk(1, get());
        DiagnosticEngine::logLexicalError(filename, startLine, startCol, "Unrecognized character in Java source: " + unk);
    }

    tokens.push_back(Token(TokenType::END_OF_FILE, "EOF", line, column));
    return tokens;
}
