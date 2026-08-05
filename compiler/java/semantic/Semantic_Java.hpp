#ifndef SEMANTIC_JAVA_HPP
#define SEMANTIC_JAVA_HPP

#include <string>
#include <vector>
#include <fstream>
#include "../symbol_table/SymbolTable_Java.hpp"
#include "../../common/Utilities/ASTBase.hpp"
#include "../../common/Utilities/DiagnosticEngine.hpp"

class Semantic_Java {
private:
    SymbolTable_Java symbolTable;
    std::string filename;
    std::vector<std::string> reportLines;
    bool foundMainMethod;

public:
    Semantic_Java(const std::string& fname = "source.java")
        : filename(fname), foundMainMethod(false) {}

    bool analyze(ASTNodePtr root);
    void checkNode(ASTNodePtr node);

    const SymbolTable_Java& getSymbolTable() const { return symbolTable; }
    void saveReports(const std::string& symTablePath, const std::string& reportPath) const;
};

#endif // SEMANTIC_JAVA_HPP
