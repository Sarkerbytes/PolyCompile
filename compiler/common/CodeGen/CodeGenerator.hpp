#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include <vector>
#include <string>
#include "../IR/IRGenerator.hpp"

class CodeGenerator {
public:
    static std::vector<std::string> generateAssembly(const std::vector<TACInstruction>& tacInsts);
    static void saveToFile(const std::vector<std::string>& asmInsts, const std::string& filepath);
};

#endif // CODE_GENERATOR_HPP
