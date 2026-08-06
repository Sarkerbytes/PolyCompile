#ifndef SYMBOL_TABLE_CPP_HPP
#define SYMBOL_TABLE_CPP_HPP

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct SymbolCPP {
  std::string name;
  std::string type;
  int scopeLevel;
  bool isFunction;
  std::vector<std::string> paramTypes;
};

class SymbolTable_CPP {
private:
  std::vector<std::map<std::string, SymbolCPP>> scopes;
  std::vector<SymbolCPP> allSymbols; // permanent record of every declared symbol

public:
  SymbolTable_CPP() {
    enterScope(); // Global scope
  }

  void enterScope() { scopes.push_back(std::map<std::string, SymbolCPP>()); }

  void exitScope() {
    if (scopes.size() > 1) {
      scopes.pop_back();
    }
  }

  bool declare(const std::string &name, const std::string &type, bool isFunc = false,
               const std::vector<std::string> &params = std::vector<std::string>()) {
    if (scopes.back().count(name)) {
      return false; // Duplicate declaration in current scope
    }
    SymbolCPP sym;
    sym.name = name;
    sym.type = type;
    sym.scopeLevel = scopes.size() - 1;
    sym.isFunction = isFunc;
    sym.paramTypes = params;
    scopes.back()[name] = sym;
    allSymbols.push_back(sym); // keep a permanent copy
    return true;
  }

  SymbolCPP *lookup(const std::string &name) {
    for (int i = static_cast<int>(scopes.size()) - 1; i >= 0; --i) {
      auto it = scopes[i].find(name);
      if (it != scopes[i].end()) {
        return &(it->second);
      }
    }
    return nullptr;
  }

  std::string toString() const {
    std::stringstream ss;
    ss << "\n";
    ss << "           C++ SYMBOL TABLE             \n";
    ss << "\n";
    ss << "Scope Level | Name | Type | Kind | Params\n";
    ss << "----------------------------------------\n";
    for (const auto &sym : allSymbols) {
      ss << "  Level " << sym.scopeLevel << "   | " << sym.name << " | " << sym.type
         << " | " << (sym.isFunction ? "Function" : "Variable") << " | ";
      for (size_t p = 0; p < sym.paramTypes.size(); ++p) {
        ss << sym.paramTypes[p];
        if (p + 1 < sym.paramTypes.size())
          ss << ", ";
      }
      ss << "\n";
    }
    ss << "========================================\n";
    return ss.str();
  }
};

#endif // SYMBOL_TABLE_CPP_HPP
