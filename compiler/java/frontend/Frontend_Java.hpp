#ifndef FRONTEND_JAVA_HPP
#define FRONTEND_JAVA_HPP

#include <string>
#include <vector>
#include "../../common/Token/Token.hpp"
#include "../../common/Utilities/ASTBase.hpp"
#include "../lexer/Lexer_Java.hpp"
#include "../parser/Parser_Java.hpp"
#include "../semantic/Semantic_Java.hpp"
#include "../ast/AST_Java.hpp"

class Frontend_Java {
private:
    std::string sourceCode;
    std::string filename;
    std::vector<Token> tokens;
    ASTNodePtr astRoot;

public:
    Frontend_Java(const std::string& src, const std::string& fname = "source.java")
        : sourceCode(src), filename(fname) {}

    bool runLexer(const std::string& outputTokensPath);
    bool runParser(const std::string& outputASTPath);
    bool runSemantic(const std::string& outputSymPath, const std::string& outputReportPath);

    const std::vector<Token>& getTokens() const { return tokens; }
    ASTNodePtr getAST() const { return astRoot; }
};

#endif // FRONTEND_JAVA_HPP
