#ifndef LEXER_CPP_HPP
#define LEXER_CPP_HPP

#include <string>
#include <vector>
#include <set>
#include "../../common/Token/Token.hpp"

class Lexer_CPP {
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
    Lexer_CPP(const std::string& src = "", const std::string& fname = "source.cpp");
    std::vector<Token> tokenize();
};

#endif // LEXER_CPP_HPP
