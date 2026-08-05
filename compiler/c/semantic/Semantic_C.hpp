#ifndef SEMANTIC_C_HPP
#define SEMANTIC_C_HPP

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "../symbol_table/SymbolTable_C.hpp"
#include "../../common/Utilities/ASTBase.hpp"
#include "../../common/Utilities/DiagnosticEngine.hpp"

class Semantic_C {
private:
    SymbolTable_C symbolTable;
    std::string filename;
    std::vector<std::string> reportLines;
    std::string currentFuncReturnType;

public:
    Semantic_C(const std::string& fname = "source.c") : filename(fname) {}

    bool analyze(ASTNodePtr root);
    void checkNode(ASTNodePtr node);

    const SymbolTable_C& getSymbolTable() const { return symbolTable; }
    void saveReports(const std::string& symTablePath, const std::string& reportPath) const;
};

#endif // SEMANTIC_C_HPP
