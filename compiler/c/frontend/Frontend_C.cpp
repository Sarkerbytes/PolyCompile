#include "Frontend_C.hpp"
#include <fstream>

bool Frontend_C::runLexer(const std::string& outputTokensPath) {
    Lexer_C lexer(sourceCode, filename);
    tokens = lexer.tokenize();

    std::ofstream file(outputTokensPath.c_str());
    if (file.is_open()) {
        file << "\n";
        file << "              C TOKENS                  \n";
        file << "\n";
        file << "Line : Col | Type          | Lexeme     \n";
        file << "----------------------------------------\n";
        for (const auto& tok : tokens) {
            file << "  " << tok.line << "  :  " << tok.column << "  | "
                 << tok.typeToString();
            for (size_t s = tok.typeToString().size(); s < 13; ++s) file << " ";
            file << " | " << tok.lexeme << "\n";
        }
        file << "\n";
        file.close();
    }
    return !tokens.empty();
}

bool Frontend_C::runParser(const std::string& outputASTPath) {
    Parser_C parser(tokens, filename);
    astRoot = parser.parse();
    if (astRoot) {
        AST_C::saveToFile(astRoot, outputASTPath);
        return true;
    }
    return false;
}

bool Frontend_C::runSemantic(const std::string& outputSymPath, const std::string& outputReportPath) {
    Semantic_C semantic(filename);
    bool ok = semantic.analyze(astRoot);
    semantic.saveReports(outputSymPath, outputReportPath);
    return ok;
}
