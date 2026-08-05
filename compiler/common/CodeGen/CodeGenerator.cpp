#include "CodeGenerator.hpp"
#include <fstream>
#include <sstream>

std::vector<std::string> CodeGenerator::generateAssembly(const std::vector<TACInstruction>& tacInsts) {
    std::vector<std::string> asmLines;

    asmLines.push_back(".DATA");
    asmLines.push_back(".CODE");

    for (const auto& inst : tacInsts) {
        switch (inst.op) {
            case TACOp::LABEL:
                asmLines.push_back(inst.result + ":");
                break;
            case TACOp::ASSIGN:
                asmLines.push_back("  MOV R1, " + inst.arg1);
                asmLines.push_back("  STORE R1, " + inst.result);
                break;
            case TACOp::ADD:
                asmLines.push_back("  LOAD R1, " + inst.arg1);
                asmLines.push_back("  LOAD R2, " + inst.arg2);
                asmLines.push_back("  ADD R1, R2");
                asmLines.push_back("  STORE R1, " + inst.result);
                break;
            case TACOp::SUB:
                asmLines.push_back("  LOAD R1, " + inst.arg1);
                asmLines.push_back("  LOAD R2, " + inst.arg2);
                asmLines.push_back("  SUB R1, R2");
                asmLines.push_back("  STORE R1, " + inst.result);
                break;
            case TACOp::MUL:
                asmLines.push_back("  LOAD R1, " + inst.arg1);
                asmLines.push_back("  LOAD R2, " + inst.arg2);
                asmLines.push_back("  MUL R1, R2");
                asmLines.push_back("  STORE R1, " + inst.result);
                break;
            case TACOp::DIV:
                asmLines.push_back("  LOAD R1, " + inst.arg1);
                asmLines.push_back("  LOAD R2, " + inst.arg2);
                asmLines.push_back("  DIV R1, R2");
                asmLines.push_back("  STORE R1, " + inst.result);
                break;
            case TACOp::CMP_EQ:
            case TACOp::CMP_NE:
            case TACOp::CMP_LT:
            case TACOp::CMP_GT:
            case TACOp::CMP_LE:
            case TACOp::CMP_GE:
                asmLines.push_back("  LOAD R1, " + inst.arg1);
                asmLines.push_back("  LOAD R2, " + inst.arg2);
                asmLines.push_back("  CMP R1, R2");
                asmLines.push_back("  STORE R1, " + inst.result);
                break;
            case TACOp::GOTO:
                asmLines.push_back("  JMP " + inst.result);
                break;
            case TACOp::IF_FALSE_GOTO:
                asmLines.push_back("  LOAD R1, " + inst.arg1);
                asmLines.push_back("  CMP R1, 0");
                asmLines.push_back("  JMP_EQ " + inst.result);
                break;
            case TACOp::IF_TRUE_GOTO:
                asmLines.push_back("  LOAD R1, " + inst.arg1);
                asmLines.push_back("  CMP R1, 0");
                asmLines.push_back("  JMP_NE " + inst.result);
                break;
            case TACOp::PARAM:
                asmLines.push_back("  PUSH " + inst.arg1);
                break;
            case TACOp::CALL:
                asmLines.push_back("  CALL " + inst.arg1);
                if (!inst.result.empty()) {
                    asmLines.push_back("  STORE R1, " + inst.result);
                }
                break;
            case TACOp::RETURN:
                if (!inst.arg1.empty()) {
                    asmLines.push_back("  LOAD R1, " + inst.arg1);
                }
                asmLines.push_back("  RET");
                break;
            case TACOp::READ:
                asmLines.push_back("  READ R1");
                asmLines.push_back("  STORE R1, " + inst.result);
                break;
            case TACOp::PRINT:
                asmLines.push_back("  LOAD R1, " + inst.arg1);
                asmLines.push_back("  PRINT R1");
                break;
            default:
                break;
        }
    }
    return asmLines;
}

void CodeGenerator::saveToFile(const std::vector<std::string>& asmInsts, const std::string& filepath) {
    std::ofstream file(filepath.c_str());
    if (file.is_open()) {
        for (const auto& line : asmInsts) {
            file << line << "\n";
        }
        file.close();
    }
}
