#ifndef IR_GENERATOR_HPP
#define IR_GENERATOR_HPP

#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include "../Utilities/ASTBase.hpp"

enum class TACOp {
    ASSIGN,
    ADD, SUB, MUL, DIV, MOD,
    CMP_EQ, CMP_NE, CMP_LT, CMP_GT, CMP_LE, CMP_GE,
    LOGICAL_AND, LOGICAL_OR, LOGICAL_NOT,
    LABEL,
    GOTO,
    IF_FALSE_GOTO,
    IF_TRUE_GOTO,
    PARAM,
    CALL,
    RETURN,
    READ,
    PRINT
};

struct TACInstruction {
    TACOp op;
    std::string result;
    std::string arg1;
    std::string arg2;

    std::string toString() const {
        std::stringstream ss;
        switch (op) {
            case TACOp::ASSIGN:
                ss << result << " = " << arg1;
                break;
            case TACOp::ADD:
                ss << result << " = " << arg1 << " + " << arg2;
                break;
            case TACOp::SUB:
                ss << result << " = " << arg1 << " - " << arg2;
                break;
            case TACOp::MUL:
                ss << result << " = " << arg1 << " * " << arg2;
                break;
            case TACOp::DIV:
                ss << result << " = " << arg1 << " / " << arg2;
                break;
            case TACOp::MOD:
                ss << result << " = " << arg1 << " % " << arg2;
                break;
            case TACOp::CMP_EQ:
                ss << result << " = " << arg1 << " == " << arg2;
                break;
            case TACOp::CMP_NE:
                ss << result << " = " << arg1 << " != " << arg2;
                break;
            case TACOp::CMP_LT:
                ss << result << " = " << arg1 << " < " << arg2;
                break;
            case TACOp::CMP_GT:
                ss << result << " = " << arg1 << " > " << arg2;
                break;
            case TACOp::CMP_LE:
                ss << result << " = " << arg1 << " <= " << arg2;
                break;
            case TACOp::CMP_GE:
                ss << result << " = " << arg1 << " >= " << arg2;
                break;
            case TACOp::LOGICAL_AND:
                ss << result << " = " << arg1 << " && " << arg2;
                break;
            case TACOp::LOGICAL_OR:
                ss << result << " = " << arg1 << " || " << arg2;
                break;
            case TACOp::LOGICAL_NOT:
                ss << result << " = !" << arg1;
                break;
            case TACOp::LABEL:
                ss << result << ":";
                break;
            case TACOp::GOTO:
                ss << "goto " << result;
                break;
            case TACOp::IF_FALSE_GOTO:
                ss << "ifFalse " << arg1 << " goto " << result;
                break;
            case TACOp::IF_TRUE_GOTO:
                ss << "ifTrue " << arg1 << " goto " << result;
                break;
            case TACOp::PARAM:
                ss << "param " << arg1;
                break;
            case TACOp::CALL:
                if (!result.empty()) ss << result << " = ";
                ss << "call " << arg1 << ", " << arg2;
                break;
            case TACOp::RETURN:
                ss << "return " << arg1;
                break;
            case TACOp::READ:
                ss << "read " << result;
                break;
            case TACOp::PRINT:
                ss << "print " << arg1;
                break;
        }
        return ss.str();
    }
};

class IRGenerator {
private:
    int tempCount;
    int labelCount;
    std::vector<TACInstruction> instructions;

    std::string newTemp() {
        std::stringstream ss;
        ss << "t" << tempCount++;
        return ss.str();
    }

    std::string newLabel() {
        std::stringstream ss;
        ss << "L" << labelCount++;
        return ss.str();
    }

public:
    IRGenerator() : tempCount(0), labelCount(0) {}

    std::vector<TACInstruction> generate(ASTNodePtr root);
    std::string generateExpr(ASTNodePtr expr);
    void generateStmt(ASTNodePtr stmt, const std::string& breakLabel = "", const std::string& continueLabel = "");

    const std::vector<TACInstruction>& getInstructions() const { return instructions; }
    void saveToFile(const std::string& filepath) const;
};

#endif // IR_GENERATOR_HPP
