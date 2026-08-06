#include "Frontend_Java.hpp"
#include "../../common/Utilities/DiagnosticEngine.hpp"
#include "../../common/Utilities/ASTParser.hpp"
#include <fstream>
#include <sstream>
#include <cctype>

bool Frontend_Java::runLexer(const std::string& outputTokensPath) {
    tokens.clear();
    std::stringstream ss(sourceCode);
    std::string lineStr;
    int lineNum = 1;

    while (std::getline(ss, lineStr)) {
        size_t i = 0;
        while (i < lineStr.size()) {
            if (std::isspace(lineStr[i])) { i++; continue; }
            if (lineStr[i] == '/' && i + 1 < lineStr.size() && lineStr[i+1] == '/') break;

            int col = (int)i + 1;
            if (lineStr[i] == '#' && lineStr.find("#include", i) == i) {
                std::string lex;
                while (i < lineStr.size()) lex += lineStr[i++];
                tokens.push_back(Token(TokenType::KEYWORD, lex, lineNum, col));
            } else if (std::isalpha(lineStr[i]) || lineStr[i] == '_') {
                std::string lex;
                while (i < lineStr.size() && (std::isalnum(lineStr[i]) || lineStr[i] == '_')) {
                    lex += lineStr[i++];
                }
                TokenType type = (lex == "int" || lex == "float" || lex == "double" || lex == "char" || lex == "void" ||
                                  lex == "return" || lex == "printf" || lex == "scanf" || lex == "while" || lex == "for" ||
                                  lex == "if" || lex == "else" || lex == "switch" || lex == "case" || lex == "default" ||
                                  lex == "break" || lex == "continue" || lex == "do") ? TokenType::KEYWORD : TokenType::IDENTIFIER;
                tokens.push_back(Token(type, lex, lineNum, col));
            } else if (std::isdigit(lineStr[i])) {
                std::string lex;
                while (i < lineStr.size() && (std::isdigit(lineStr[i]) || lineStr[i] == '.')) lex += lineStr[i++];
                tokens.push_back(Token(TokenType::INT_LITERAL, lex, lineNum, col));
            } else if (lineStr[i] == '"') {
                std::string lex;
                lex += lineStr[i++];
                while (i < lineStr.size() && lineStr[i] != '"') {
                    if (lineStr[i] == '\\' && i + 1 < lineStr.size()) {
                        lex += lineStr[i++];
                    }
                    lex += lineStr[i++];
                }
                if (i < lineStr.size()) lex += lineStr[i++];
                tokens.push_back(Token(TokenType::STRING_LITERAL, lex, lineNum, col));
            } else {
                std::string op;
                if (i + 1 < lineStr.size()) {
                    std::string sub2 = lineStr.substr(i, 2);
                    if (sub2 == "<=" || sub2 == ">=" || sub2 == "==" || sub2 == "!=" ||
                        sub2 == "++" || sub2 == "--" || sub2 == "&&" || sub2 == "||" ||
                        sub2 == "+=" || sub2 == "-=" || sub2 == "*=" || sub2 == "/=" || sub2 == "<<" || sub2 == ">>") {
                        op = sub2;
                        i += 2;
                    }
                }
                if (op.empty()) {
                    op = std::string(1, lineStr[i++]);
                }
                tokens.push_back(Token(TokenType::OPERATOR, op, lineNum, col));
            }
        }
        lineNum++;
    }
    tokens.push_back(Token(TokenType::END_OF_FILE, "EOF", lineNum, 1));

    std::ofstream file(outputTokensPath.c_str());
    if (file.is_open()) {
        file << "\n              JAVA TOKENS                  \n\n";
        file << "Line : Col | Type          | Lexeme     \n";
        file << "----------------------------------------\n";
        for (const auto& tok : tokens) {
            file << "  " << tok.line << "  :  " << tok.column << "  | " << tok.typeToString();
            for (size_t s = tok.typeToString().size(); s < 13; ++s) file << " ";
            file << " | " << tok.lexeme << "\n";
        }
        file << "\n";
        file.close();
    }
    return true;
}

bool Frontend_Java::runParser(const std::string& outputASTPath) {
    ASTParser parser(tokens, true);
    astRoot = parser.parseProgram();

    if (DiagnosticEngine::hasErrors()) return false;
    if (astRoot) {
        AST_Java::saveToFile(astRoot, outputASTPath);
        return true;
    }
    return false;
}

bool Frontend_Java::runSemantic(const std::string& outputSymPath, const std::string& outputReportPath) {
    Semantic_Java semantic(filename);
    bool ok = semantic.analyze(astRoot);
    semantic.saveReports(outputSymPath, outputReportPath);
    return ok;
}

