#ifndef AST_C_HPP
#define AST_C_HPP

#include <string>
#include <fstream>
#include "../../common/Utilities/ASTBase.hpp"

class AST_C {
public:
    static void saveToFile(ASTNodePtr root, const std::string& filepath) {
        std::ofstream file(filepath.c_str());
        if (file.is_open() && root) {
            file << "";
            file << "            C ABSTRACT SYNTAX TREE       \n";
            file << "";
            file << root->toString(0);
            file.close();
        }
    }
};

#endif // AST_C_HPP
