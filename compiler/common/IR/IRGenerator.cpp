#include "IRGenerator.hpp"
#include <fstream>
#include <iostream>

std::vector<TACInstruction> IRGenerator::generate(ASTNodePtr root) {
    instructions.clear();
    tempCount = 0;
    labelCount = 0;
    if (root) {
        generateStmt(root);
    }
    return instructions;
}

std::string IRGenerator::generateExpr(ASTNodePtr expr) {
    if (!expr) return "";

    switch (expr->getType()) {
        case ASTNodeType::LITERAL_EXPR: {
            auto lit = std::dynamic_pointer_cast<LiteralNode>(expr);
            return lit ? lit->value : "";
        }
        case ASTNodeType::VAR_EXPR: {
            auto var = std::dynamic_pointer_cast<VarExprNode>(expr);
            return var ? var->name : "";
        }
        case ASTNodeType::BINARY_EXPR: {
            auto bin = std::dynamic_pointer_cast<BinaryExprNode>(expr);
            if (!bin) return "";
            std::string left = generateExpr(bin->left);
            std::string right = generateExpr(bin->right);
            std::string temp = newTemp();

            TACOp op = TACOp::ADD;
            if (bin->op == "+") op = TACOp::ADD;
            else if (bin->op == "-") op = TACOp::SUB;
            else if (bin->op == "*") op = TACOp::MUL;
            else if (bin->op == "/") op = TACOp::DIV;
            else if (bin->op == "%") op = TACOp::MOD;
            else if (bin->op == "==") op = TACOp::CMP_EQ;
            else if (bin->op == "!=") op = TACOp::CMP_NE;
            else if (bin->op == "<") op = TACOp::CMP_LT;
            else if (bin->op == ">") op = TACOp::CMP_GT;
            else if (bin->op == "<=") op = TACOp::CMP_LE;
            else if (bin->op == ">=") op = TACOp::CMP_GE;
            else if (bin->op == "&&") op = TACOp::LOGICAL_AND;
            else if (bin->op == "||") op = TACOp::LOGICAL_OR;

            instructions.push_back({op, temp, left, right});
            return temp;
        }
        case ASTNodeType::UNARY_EXPR: {
            auto un = std::dynamic_pointer_cast<UnaryExprNode>(expr);
            if (!un) return "";
            std::string operand = generateExpr(un->operand);
            std::string temp = newTemp();

            if (un->op == "!") {
                instructions.push_back({TACOp::LOGICAL_NOT, temp, operand, ""});
            } else if (un->op == "-") {
                instructions.push_back({TACOp::SUB, temp, "0", operand});
            } else if (un->op == "++" || un->op == "pre++") {
                // Pre-increment: temp = operand + 1; operand = temp
                instructions.push_back({TACOp::ADD, temp, operand, "1"});
                instructions.push_back({TACOp::ASSIGN, operand, temp, ""});
            } else if (un->op == "--" || un->op == "pre--") {
                // Pre-decrement
                instructions.push_back({TACOp::SUB, temp, operand, "1"});
                instructions.push_back({TACOp::ASSIGN, operand, temp, ""});
            } else if (un->op == "post++") {
                // Post-increment: return old value, then increment
                instructions.push_back({TACOp::ASSIGN, temp, operand, ""});
                std::string inc = newTemp();
                instructions.push_back({TACOp::ADD, inc, operand, "1"});
                instructions.push_back({TACOp::ASSIGN, operand, inc, ""});
            } else if (un->op == "post--") {
                // Post-decrement
                instructions.push_back({TACOp::ASSIGN, temp, operand, ""});
                std::string dec = newTemp();
                instructions.push_back({TACOp::SUB, dec, operand, "1"});
                instructions.push_back({TACOp::ASSIGN, operand, dec, ""});
            }
            return temp;
        }
        case ASTNodeType::CALL_EXPR: {
            auto call = std::dynamic_pointer_cast<CallExprNode>(expr);
            if (!call) return "";

            std::vector<std::string> argTemps;
            for (const auto& arg : call->args) {
                argTemps.push_back(generateExpr(arg));
            }
            for (const auto& at : argTemps) {
                instructions.push_back({TACOp::PARAM, "", at, ""});
            }

            std::string temp = newTemp();
            std::stringstream ss;
            ss << call->args.size();
            instructions.push_back({TACOp::CALL, temp, call->funcName, ss.str()});
            return temp;
        }
        default:
            return "";
    }
}

void IRGenerator::generateStmt(ASTNodePtr stmt, const std::string& breakLabel, const std::string& continueLabel) {
    if (!stmt) return;

    switch (stmt->getType()) {
        case ASTNodeType::PROGRAM: {
            auto prog = std::dynamic_pointer_cast<ProgramNode>(stmt);
            if (prog) {
                for (const auto& decl : prog->declarations) {
                    generateStmt(decl, breakLabel, continueLabel);
                }
            }
            break;
        }
        case ASTNodeType::FUNCTION: {
            auto func = std::dynamic_pointer_cast<FunctionNode>(stmt);
            if (func) {
                instructions.push_back({TACOp::LABEL, func->name, "", ""});
                for (size_t i = 0; i < func->parameters.size(); ++i) {
                    std::stringstream ss;
                    ss << "__param_" << i << "__";
                    instructions.push_back({TACOp::ASSIGN, func->parameters[i].name, ss.str(), ""});
                }
                if (func->body) {
                    generateStmt(func->body, breakLabel, continueLabel);
                }
                // Add default return if not present
                instructions.push_back({TACOp::RETURN, "", "0", ""});
            }
            break;
        }
        case ASTNodeType::VAR_DECL: {
            auto vd = std::dynamic_pointer_cast<VarDeclNode>(stmt);
            if (vd && vd->initExpr) {
                std::string val = generateExpr(vd->initExpr);
                instructions.push_back({TACOp::ASSIGN, vd->varName, val, ""});
            }
            break;
        }
        case ASTNodeType::VAR_DECL_LIST: {
            auto vdl = std::dynamic_pointer_cast<VarDeclListNode>(stmt);
            if (vdl) {
                for (const auto& d : vdl->decls) {
                    generateStmt(d, breakLabel, continueLabel);
                }
            }
            break;
        }
        case ASTNodeType::BLOCK: {
            auto block = std::dynamic_pointer_cast<BlockNode>(stmt);
            if (block) {
                for (const auto& s : block->statements) {
                    generateStmt(s, breakLabel, continueLabel);
                }
            }
            break;
        }
        case ASTNodeType::ASSIGN_STMT: {
            auto ass = std::dynamic_pointer_cast<AssignNode>(stmt);
            if (ass) {
                std::string val = generateExpr(ass->expr);
                if (ass->op == "=") {
                    instructions.push_back({TACOp::ASSIGN, ass->varName, val, ""});
                } else if (ass->op == "+=") {
                    std::string temp = newTemp();
                    instructions.push_back({TACOp::ADD, temp, ass->varName, val});
                    instructions.push_back({TACOp::ASSIGN, ass->varName, temp, ""});
                } else if (ass->op == "-=") {
                    std::string temp = newTemp();
                    instructions.push_back({TACOp::SUB, temp, ass->varName, val});
                    instructions.push_back({TACOp::ASSIGN, ass->varName, temp, ""});
                }
            }
            break;
        }
        case ASTNodeType::IF_STMT: {
            auto ifStmt = std::dynamic_pointer_cast<IfNode>(stmt);
            if (ifStmt) {
                std::string condVal = generateExpr(ifStmt->condition);
                std::string elseLbl = newLabel();
                std::string endLbl = newLabel();

                if (ifStmt->elseBranch) {
                    instructions.push_back({TACOp::IF_FALSE_GOTO, elseLbl, condVal, ""});
                    generateStmt(ifStmt->thenBranch, breakLabel, continueLabel);
                    instructions.push_back({TACOp::GOTO, endLbl, "", ""});
                    instructions.push_back({TACOp::LABEL, elseLbl, "", ""});
                    generateStmt(ifStmt->elseBranch, breakLabel, continueLabel);
                    instructions.push_back({TACOp::LABEL, endLbl, "", ""});
                } else {
                    instructions.push_back({TACOp::IF_FALSE_GOTO, endLbl, condVal, ""});
                    generateStmt(ifStmt->thenBranch, breakLabel, continueLabel);
                    instructions.push_back({TACOp::LABEL, endLbl, "", ""});
                }
            }
            break;
        }
        case ASTNodeType::WHILE_STMT: {
            auto whileStmt = std::dynamic_pointer_cast<WhileNode>(stmt);
            if (whileStmt) {
                std::string startLbl = newLabel();
                std::string endLbl = newLabel();

                instructions.push_back({TACOp::LABEL, startLbl, "", ""});
                std::string condVal = generateExpr(whileStmt->condition);
                instructions.push_back({TACOp::IF_FALSE_GOTO, endLbl, condVal, ""});

                generateStmt(whileStmt->body, endLbl, startLbl);

                instructions.push_back({TACOp::GOTO, startLbl, "", ""});
                instructions.push_back({TACOp::LABEL, endLbl, "", ""});
            }
            break;
        }
        case ASTNodeType::DO_WHILE_STMT: {
            auto doStmt = std::dynamic_pointer_cast<DoWhileNode>(stmt);
            if (doStmt) {
                std::string startLbl = newLabel();
                std::string condLbl = newLabel();
                std::string endLbl = newLabel();

                instructions.push_back({TACOp::LABEL, startLbl, "", ""});
                generateStmt(doStmt->body, endLbl, condLbl);

                instructions.push_back({TACOp::LABEL, condLbl, "", ""});
                std::string condVal = generateExpr(doStmt->condition);
                instructions.push_back({TACOp::IF_TRUE_GOTO, startLbl, condVal, ""});
                instructions.push_back({TACOp::LABEL, endLbl, "", ""});
            }
            break;
        }
        case ASTNodeType::FOR_STMT: {
            auto forStmt = std::dynamic_pointer_cast<ForNode>(stmt);
            if (forStmt) {
                if (forStmt->init) generateStmt(forStmt->init, breakLabel, continueLabel);

                std::string startLbl = newLabel();
                std::string incrLbl = newLabel();
                std::string endLbl = newLabel();

                instructions.push_back({TACOp::LABEL, startLbl, "", ""});
                if (forStmt->condition) {
                    std::string condVal = generateExpr(forStmt->condition);
                    instructions.push_back({TACOp::IF_FALSE_GOTO, endLbl, condVal, ""});
                }

                generateStmt(forStmt->body, endLbl, incrLbl);

                instructions.push_back({TACOp::LABEL, incrLbl, "", ""});
                if (forStmt->update) generateStmt(forStmt->update, breakLabel, continueLabel);
                instructions.push_back({TACOp::GOTO, startLbl, "", ""});
                instructions.push_back({TACOp::LABEL, endLbl, "", ""});
            }
            break;
        }
        case ASTNodeType::SWITCH_STMT: {
            auto sw = std::dynamic_pointer_cast<SwitchNode>(stmt);
            if (sw) {
                std::string exprVal = generateExpr(sw->expression);
                std::string endLbl = newLabel();

                std::vector<std::string> caseLabels;
                for (size_t i = 0; i < sw->cases.size(); ++i) {
                    caseLabels.push_back(newLabel());
                }
                std::string defaultLbl = sw->defaultBody.empty() ? endLbl : newLabel();

                for (size_t i = 0; i < sw->cases.size(); ++i) {
                    std::string caseVal = generateExpr(sw->cases[i].value);
                    std::string cmpTemp = newTemp();
                    instructions.push_back({TACOp::CMP_EQ, cmpTemp, exprVal, caseVal});
                    instructions.push_back({TACOp::IF_TRUE_GOTO, caseLabels[i], cmpTemp, ""});
                }
                instructions.push_back({TACOp::GOTO, defaultLbl, "", ""});

                for (size_t i = 0; i < sw->cases.size(); ++i) {
                    instructions.push_back({TACOp::LABEL, caseLabels[i], "", ""});
                    for (const auto& s : sw->cases[i].body) {
                        generateStmt(s, endLbl, continueLabel);
                    }
                }

                if (!sw->defaultBody.empty()) {
                    instructions.push_back({TACOp::LABEL, defaultLbl, "", ""});
                    for (const auto& s : sw->defaultBody) {
                        generateStmt(s, endLbl, continueLabel);
                    }
                }
                instructions.push_back({TACOp::LABEL, endLbl, "", ""});
            }
            break;
        }
        case ASTNodeType::RETURN_STMT: {
            auto ret = std::dynamic_pointer_cast<ReturnNode>(stmt);
            if (ret) {
                std::string val = ret->expr ? generateExpr(ret->expr) : "";
                instructions.push_back({TACOp::RETURN, "", val, ""});
            }
            break;
        }
        case ASTNodeType::BREAK_STMT: {
            if (!breakLabel.empty()) {
                instructions.push_back({TACOp::GOTO, breakLabel, "", ""});
            }
            break;
        }
        case ASTNodeType::CONTINUE_STMT: {
            if (!continueLabel.empty()) {
                instructions.push_back({TACOp::GOTO, continueLabel, "", ""});
            }
            break;
        }
        case ASTNodeType::INPUT_STMT: {
            auto in = std::dynamic_pointer_cast<InputNode>(stmt);
            if (in) {
                // Emit a READ for every variable listed in the scanf call.
                // targetVars holds ALL targets; fall back to targetVar for
                // legacy single-variable nodes that may not populate targetVars.
                if (!in->targetVars.empty()) {
                    for (const auto& var : in->targetVars) {
                        instructions.push_back({TACOp::READ, var, "", ""});
                    }
                } else if (!in->targetVar.empty()) {
                    instructions.push_back({TACOp::READ, in->targetVar, "", ""});
                }
            }
            break;
        }
        case ASTNodeType::OUTPUT_STMT: {
            auto out = std::dynamic_pointer_cast<OutputNode>(stmt);
            if (out) {
                for (const auto& arg : out->args) {
                    std::string val = generateExpr(arg);
                    instructions.push_back({TACOp::PRINT, "", val, ""});
                }
            }
            break;
        }
        default:
            generateExpr(stmt);
            break;
    }
}

void IRGenerator::saveToFile(const std::string& filepath) const {
    std::ofstream file(filepath.c_str());
    if (file.is_open()) {
        for (const auto& inst : instructions) {
            file << inst.toString() << "\n";
        }
        file.close();
    }
}
