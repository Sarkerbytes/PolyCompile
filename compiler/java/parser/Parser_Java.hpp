#ifndef PARSER_JAVA_HPP
#define PARSER_JAVA_HPP

#include <vector>
#include <string>
#include "../../common/Token/Token.hpp"
#include "../../common/Utilities/ASTBase.hpp"

class Parser_Java {
private:
    std::vector<Token> tokens;
    std::string filename;
    size_t current;

    Token peek() const;
    Token previous() const;
    bool isAtEnd() const;
    Token advance();
    bool check(TokenType type, const std::string& lexeme = "") const;
    bool match(TokenType type, const std::string& lexeme = "");
    Token consume(TokenType type, const std::string& msg);
    Token consumeLexeme(const std::string& lexeme, const std::string& msg);

    ASTNodePtr parseProgram();
    ASTNodePtr parseClassDecl();
    ASTNodePtr parseMethodDecl(const std::string& retType, const std::string& name);
    ASTNodePtr parseVarDecl(const std::string& type, const std::string& name);
    ASTNodePtr parseStatement();
    ASTNodePtr parseBlock();
    ASTNodePtr parsePrintStatement();
    ASTNodePtr parseScannerDecl();
    ASTNodePtr parseScannerRead(const std::string& varName);
    ASTNodePtr parseIfStatement();
    ASTNodePtr parseSwitchStatement();
    ASTNodePtr parseWhileStatement();
    ASTNodePtr parseDoWhileStatement();
    ASTNodePtr parseForStatement();
    ASTNodePtr parseReturnStatement();
    ASTNodePtr parseExprStatement();

    ASTNodePtr parseExpression();
    ASTNodePtr parseAssignment();
    ASTNodePtr parseLogicalOr();
    ASTNodePtr parseLogicalAnd();
    ASTNodePtr parseEquality();
    ASTNodePtr parseRelational();
    ASTNodePtr parseAdditive();
    ASTNodePtr parseMultiplicative();
    ASTNodePtr parseUnary();
    ASTNodePtr parsePrimary();

    bool isTypeKeyword() const;
    std::string currentTypeKeyword();

public:
    Parser_Java(const std::vector<Token>& tks, const std::string& fname = "source.java");
    ASTNodePtr parse();
};

#endif // PARSER_JAVA_HPP
