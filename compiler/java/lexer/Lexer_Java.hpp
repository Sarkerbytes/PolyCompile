#ifndef LEXER_JAVA_HPP
#define LEXER_JAVA_HPP

#include <string>
#include <vector>
#include <set>
#include "../../common/Token/Token.hpp"

class Lexer_Java {
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
    Lexer_Java(const std::string& src = "", const std::string& fname = "source.java");
    std::vector<Token> tokenize();
};

#endif // LEXER_JAVA_HPP
