#ifndef AST_JAVA_HPP
#define AST_JAVA_HPP

#include <string>
#include <fstream>
#include "../../common/Utilities/ASTBase.hpp"

class AST_Java {
public:
    static void saveToFile(ASTNodePtr root, const std::string& filepath) {
        std::ofstream file(filepath.c_str());
        if (file.is_open() && root) {
            file << "\n";
            file << "          JAVA ABSTRACT SYNTAX TREE     \n";
            file << "\n";
            file << root->toString(0);
            file.close();
        }
    }
};

#endif // AST_JAVA_HPP
