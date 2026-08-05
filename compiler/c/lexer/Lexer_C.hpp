#ifndef LEXER_C_HPP
#define LEXER_C_HPP

#include <string>
#include <vector>
#include <set>
#include "../../common/Token/Token.hpp"

class Lexer_C {
private:
    std::string source;
    std::string filename;
    size_t cursor;
    int line;
    int column;
    std::set<std::string> keywords;

    void initKeywords();
    char peek() const;
    char get();
    void skipWhitespaceAndComments();

public:
    Lexer_C(const std::string& src = "", const std::string& fname = "source.c");
    std::vector<Token> tokenize();
};

#endif // LEXER_C_HPP
