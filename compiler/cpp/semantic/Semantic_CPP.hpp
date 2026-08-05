#ifndef SEMANTIC_CPP_HPP
#define SEMANTIC_CPP_HPP

#include <string>
#include <vector>
#include <fstream>
#include "../symbol_table/SymbolTable_CPP.hpp"
#include "../../common/Utilities/ASTBase.hpp"
#include "../../common/Utilities/DiagnosticEngine.hpp"

class Semantic_CPP {
private:
    SymbolTable_CPP symbolTable;
    std::string filename;
    std::vector<std::string> reportLines;

public:
    Semantic_CPP(const std::string& fname = "source.cpp") : filename(fname) {}

    bool analyze(ASTNodePtr root);
    void checkNode(ASTNodePtr node);

    const SymbolTable_CPP& getSymbolTable() const { return symbolTable; }
    void saveReports(const std::string& symTablePath, const std::string& reportPath) const;
};

#endif // SEMANTIC_CPP_HPP
