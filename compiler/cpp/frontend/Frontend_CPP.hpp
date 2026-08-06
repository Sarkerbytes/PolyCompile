#ifndef FRONTEND_CPP_HPP
#define FRONTEND_CPP_HPP

#include <string>
#include <vector>
#include "../../common/Token/Token.hpp"
#include "../../common/Utilities/ASTBase.hpp"
#include "../../common/Utilities/ASTParser.hpp"
#include "../semantic/Semantic_CPP.hpp"
#include "../ast/AST_CPP.hpp"

class Frontend_CPP {
private:
    std::string sourceCode;
    std::string filename;
    std::vector<Token> tokens;
    ASTNodePtr astRoot;

public:
    Frontend_CPP(const std::string& src, const std::string& fname = "source.cpp")
        : sourceCode(src), filename(fname) {}

    bool runLexer(const std::string& outputTokensPath);
    bool runParser(const std::string& outputASTPath);
    bool runSemantic(const std::string& outputSymPath, const std::string& outputReportPath);
    
    std::vector<Token> getTokens() const { return tokens; }
    ASTNodePtr getAST() const { return astRoot; }
};

#endif
