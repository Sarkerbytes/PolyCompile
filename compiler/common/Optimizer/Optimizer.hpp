#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include <vector>
#include <string>
#include "../IR/IRGenerator.hpp"

class Optimizer {
public:
    static std::vector<TACInstruction> optimize(const std::vector<TACInstruction>& input);
    static void saveToFile(const std::vector<TACInstruction>& insts, const std::string& filepath);

private:
    static std::vector<TACInstruction> constantFoldingPass(const std::vector<TACInstruction>& insts);
    static std::vector<TACInstruction> constantPropagationPass(const std::vector<TACInstruction>& insts);
    static std::vector<TACInstruction> copyPropagationPass(const std::vector<TACInstruction>& insts);
    static std::vector<TACInstruction> algebraicSimplificationPass(const std::vector<TACInstruction>& insts);
    static std::vector<TACInstruction> deadCodeEliminationPass(const std::vector<TACInstruction>& insts);

    static bool isInteger(const std::string& str);
    static long long parseInteger(const std::string& str);
};

#endif // OPTIMIZER_HPP
