#ifndef FRONTEND_C_HPP
#define FRONTEND_C_HPP

#include <string>
#include <vector>
#include "../../common/Token/Token.hpp"
#include "../../common/Utilities/ASTBase.hpp"
#include "../lexer/Lexer_C.hpp"
#include "../parser/Parser_C.hpp"
#include "../semantic/Semantic_C.hpp"
#include "../ast/AST_C.hpp"

class Frontend_C {
private:
    std::string sourceCode;
    std::string filename;
    std::vector<Token> tokens;
    ASTNodePtr astRoot;

public:
    Frontend_C(const std::string& src, const std::string& fname = "source.c")
        : sourceCode(src), filename(fname) {}

    bool runLexer(const std::string& outputTokensPath);
    bool runParser(const std::string& outputASTPath);
    bool runSemantic(const std::string& outputSymPath, const std::string& outputReportPath);

    const std::vector<Token>& getTokens() const { return tokens; }
    ASTNodePtr getAST() const { return astRoot; }
};

#endif // FRONTEND_C_HPP
