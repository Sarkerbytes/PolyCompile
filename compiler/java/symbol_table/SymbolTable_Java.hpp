#ifndef SYMBOL_TABLE_JAVA_HPP
#define SYMBOL_TABLE_JAVA_HPP

#include <string>
#include <map>
#include <vector>
#include <sstream>

struct SymbolJava {
    std::string name;
    std::string type;
    int scopeLevel;
    bool isMethod;
    std::vector<std::string> paramTypes;
};

class SymbolTable_Java {
private:
    std::vector<std::map<std::string, SymbolJava>> scopes;

public:
    SymbolTable_Java() { enterScope(); }

    void enterScope() { scopes.push_back(std::map<std::string, SymbolJava>()); }
    void exitScope() { if (scopes.size() > 1) scopes.pop_back(); }

    bool declare(const std::string& name, const std::string& type, bool isMeth = false, const std::vector<std::string>& params = std::vector<std::string>()) {
        if (scopes.back().count(name)) return false;
        SymbolJava sym;
        sym.name = name;
        sym.type = type;
        sym.scopeLevel = scopes.size() - 1;
        sym.isMethod = isMeth;
        sym.paramTypes = params;
        scopes.back()[name] = sym;
        return true;
    }

    SymbolJava* lookup(const std::string& name) {
        for (int i = static_cast<int>(scopes.size()) - 1; i >= 0; --i) {
            auto it = scopes[i].find(name);
            if (it != scopes[i].end()) return &(it->second);
        }
        return nullptr;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "\n";
        ss << "           JAVA SYMBOL TABLE            \n";
        ss << "\n";
        ss << "Scope Level | Name | Type | Kind | Params\n";
        ss << "----------------------------------------\n";
        for (size_t level = 0; level < scopes.size(); ++level) {
            for (const auto& pair : scopes[level]) {
                const auto& sym = pair.second;
                ss << "  Level " << level << "   | " << sym.name << " | " << sym.type << " | "
                   << (sym.isMethod ? "Method" : "Variable") << " | ";
                for (size_t p = 0; p < sym.paramTypes.size(); ++p) {
                    ss << sym.paramTypes[p];
                    if (p + 1 < sym.paramTypes.size()) ss << ", ";
                }
                ss << "\n";
            }
        }
        ss << "========================================\n";
        return ss.str();
    }
};

#endif // SYMBOL_TABLE_JAVA_HPP
