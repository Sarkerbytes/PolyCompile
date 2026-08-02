#include "Optimizer.hpp"
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <cstdlib>
#include <cctype>

bool Optimizer::isInteger(const std::string& str) {
    if (str.empty()) return false;
    size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
    if (start >= str.size()) return false;
    for (size_t i = start; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) return false;
    }
    return true;
}

long long Optimizer::parseInteger(const std::string& str) {
    return std::atoll(str.c_str());
}

std::vector<TACInstruction> Optimizer::constantFoldingPass(const std::vector<TACInstruction>& insts) {
    std::vector<TACInstruction> result;
    for (auto inst : insts) {
        if ((inst.op == TACOp::ADD || inst.op == TACOp::SUB || inst.op == TACOp::MUL || inst.op == TACOp::DIV || inst.op == TACOp::MOD)
            && isInteger(inst.arg1) && isInteger(inst.arg2)) {
            long long v1 = parseInteger(inst.arg1);
            long long v2 = parseInteger(inst.arg2);
            long long resVal = 0;
            bool folded = true;
            if (inst.op == TACOp::ADD) resVal = v1 + v2;
            else if (inst.op == TACOp::SUB) resVal = v1 - v2;
            else if (inst.op == TACOp::MUL) resVal = v1 * v2;
            else if (inst.op == TACOp::DIV) { if (v2 != 0) resVal = v1 / v2; else folded = false; }
            else if (inst.op == TACOp::MOD) { if (v2 != 0) resVal = v1 % v2; else folded = false; }

            if (folded) {
                std::stringstream ss;
                ss << resVal;
                result.push_back({TACOp::ASSIGN, inst.result, ss.str(), ""});
                continue;
            }
        }
        result.push_back(inst);
    }
    return result;
}

std::vector<TACInstruction> Optimizer::constantPropagationPass(const std::vector<TACInstruction>& insts) {
    std::vector<TACInstruction> result;
    std::map<std::string, std::string> constMap;

    for (auto inst : insts) {
        // Clear maps at labels/branches
        if (inst.op == TACOp::LABEL || inst.op == TACOp::GOTO || inst.op == TACOp::IF_FALSE_GOTO || inst.op == TACOp::IF_TRUE_GOTO || inst.op == TACOp::CALL) {
            constMap.clear();
        }

        if (constMap.count(inst.arg1)) inst.arg1 = constMap[inst.arg1];
        if (constMap.count(inst.arg2)) inst.arg2 = constMap[inst.arg2];

        if (inst.op == TACOp::ASSIGN && isInteger(inst.arg1)) {
            constMap[inst.result] = inst.arg1;
        } else if (!inst.result.empty()) {
            constMap.erase(inst.result);
        }

        result.push_back(inst);
    }
    return result;
}

std::vector<TACInstruction> Optimizer::copyPropagationPass(const std::vector<TACInstruction>& insts) {
    std::vector<TACInstruction> result;
    std::map<std::string, std::string> copyMap;

    for (auto inst : insts) {
        if (inst.op == TACOp::LABEL || inst.op == TACOp::GOTO || inst.op == TACOp::IF_FALSE_GOTO || inst.op == TACOp::IF_TRUE_GOTO || inst.op == TACOp::CALL) {
            copyMap.clear();
        }

        if (copyMap.count(inst.arg1)) inst.arg1 = copyMap[inst.arg1];
        if (copyMap.count(inst.arg2)) inst.arg2 = copyMap[inst.arg2];

        if (inst.op == TACOp::ASSIGN && !isInteger(inst.arg1) && inst.arg1[0] != '"') {
            copyMap[inst.result] = inst.arg1;
        } else if (!inst.result.empty()) {
            copyMap.erase(inst.result);
            // invalidate any copy targeting inst.result
            for (auto it = copyMap.begin(); it != copyMap.end();) {
                if (it->second == inst.result) it = copyMap.erase(it);
                else ++it;
            }
        }

        result.push_back(inst);
    }
    return result;
}

std::vector<TACInstruction> Optimizer::algebraicSimplificationPass(const std::vector<TACInstruction>& insts) {
    std::vector<TACInstruction> result;
    for (auto inst : insts) {
        if (inst.op == TACOp::ADD) {
            if (inst.arg1 == "0") { result.push_back({TACOp::ASSIGN, inst.result, inst.arg2, ""}); continue; }
            if (inst.arg2 == "0") { result.push_back({TACOp::ASSIGN, inst.result, inst.arg1, ""}); continue; }
        } else if (inst.op == TACOp::SUB) {
            if (inst.arg2 == "0") { result.push_back({TACOp::ASSIGN, inst.result, inst.arg1, ""}); continue; }
            if (inst.arg1 == inst.arg2) { result.push_back({TACOp::ASSIGN, inst.result, "0", ""}); continue; }
        } else if (inst.op == TACOp::MUL) {
            if (inst.arg1 == "1") { result.push_back({TACOp::ASSIGN, inst.result, inst.arg2, ""}); continue; }
            if (inst.arg2 == "1") { result.push_back({TACOp::ASSIGN, inst.result, inst.arg1, ""}); continue; }
            if (inst.arg1 == "0" || inst.arg2 == "0") { result.push_back({TACOp::ASSIGN, inst.result, "0", ""}); continue; }
        }
        result.push_back(inst);
    }
    return result;
}

std::vector<TACInstruction> Optimizer::deadCodeEliminationPass(const std::vector<TACInstruction>& insts) {
    // Find all used variables
    std::set<std::string> usedVars;
    for (const auto& inst : insts) {
        if (inst.op != TACOp::LABEL && inst.op != TACOp::ASSIGN && inst.op != TACOp::READ) {
            if (!inst.arg1.empty() && !isInteger(inst.arg1) && inst.arg1[0] != '"') usedVars.insert(inst.arg1);
            if (!inst.arg2.empty() && !isInteger(inst.arg2) && inst.arg2[0] != '"') usedVars.insert(inst.arg2);
        }
        if (inst.op == TACOp::IF_FALSE_GOTO || inst.op == TACOp::IF_TRUE_GOTO || inst.op == TACOp::PRINT || inst.op == TACOp::RETURN || inst.op == TACOp::PARAM) {
            if (!inst.arg1.empty() && !isInteger(inst.arg1) && inst.arg1[0] != '"') usedVars.insert(inst.arg1);
            if (!inst.result.empty() && inst.op != TACOp::LABEL) usedVars.insert(inst.result);
        }
    }

    std::vector<TACInstruction> result;
    for (const auto& inst : insts) {
        // Keep instruction if it's a temporary assignment that is never used
        if (inst.op == TACOp::ASSIGN && !inst.result.empty() && inst.result[0] == 't') {
            if (usedVars.find(inst.result) == usedVars.end()) {
                continue; // eliminate dead temp assignment
            }
        }
        result.push_back(inst);
    }
    return result;
}

std::vector<TACInstruction> Optimizer::optimize(const std::vector<TACInstruction>& input) {
    std::vector<TACInstruction> current = input;
    current = constantFoldingPass(current);
    current = constantPropagationPass(current);
    current = copyPropagationPass(current);
    current = algebraicSimplificationPass(current);
    current = deadCodeEliminationPass(current);
    return current;
}

void Optimizer::saveToFile(const std::vector<TACInstruction>& insts, const std::string& filepath) {
    std::ofstream file(filepath.c_str());
    if (file.is_open()) {
        for (const auto& inst : insts) {
            file << inst.toString() << "\n";
        }
        file.close();
    }
}
