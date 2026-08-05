#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <iostream>

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    INT_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,
    BOOL_LITERAL,
    OPERATOR,
    DELIMITER,
    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token(TokenType t = TokenType::UNKNOWN, const std::string& lex = "", int l = 1, int c = 1)
        : type(t), lexeme(lex), line(l), column(c) {}

    std::string typeToString() const {
        switch (type) {
            case TokenType::KEYWORD: return "KEYWORD";
            case TokenType::IDENTIFIER: return "IDENTIFIER";
            case TokenType::INT_LITERAL: return "INT_LITERAL";
            case TokenType::FLOAT_LITERAL: return "FLOAT_LITERAL";
            case TokenType::STRING_LITERAL: return "STRING_LITERAL";
            case TokenType::CHAR_LITERAL: return "CHAR_LITERAL";
            case TokenType::BOOL_LITERAL: return "BOOL_LITERAL";
            case TokenType::OPERATOR: return "OPERATOR";
            case TokenType::DELIMITER: return "DELIMITER";
            case TokenType::END_OF_FILE: return "EOF";
            default: return "UNKNOWN";
        }
    }
};

#endif // TOKEN_HPP
