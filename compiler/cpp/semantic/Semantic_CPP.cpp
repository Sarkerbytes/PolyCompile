#include "Semantic_CPP.hpp"

bool Semantic_CPP::analyze(ASTNodePtr root) {
    reportLines.clear();
    DiagnosticEngine::clear();
    reportLines.push_back("C++ SEMANTIC ANALYSIS REPORT");
    reportLines.push_back("----------------------------");

    if (!root) {
        reportLines.push_back("Empty AST provided.");
        return true;
    }

    checkNode(root);
    reportLines.push_back("Semantic analysis completed with " + std::to_string(DiagnosticEngine::getErrors().size()) + " errors.");
    return !DiagnosticEngine::hasErrors();
}

void Semantic_CPP::checkNode(ASTNodePtr node) {
    if (!node) return;

    switch (node->getType()) {
        case ASTNodeType::PROGRAM: {
            auto prog = std::dynamic_pointer_cast<ProgramNode>(node);
            for (const auto& decl : prog->declarations) {
                checkNode(decl);
            }
            break;
        }
        case ASTNodeType::FUNCTION: {
            auto func = std::dynamic_pointer_cast<FunctionNode>(node);
            std::vector<std::string> paramTypes;
            for (const auto& p : func->parameters) paramTypes.push_back(p.type);

            SymbolCPP* existing = symbolTable.lookup(func->name);
            if (existing && existing->isFunction && existing->type == func->returnType) {
                reportLines.push_back("C++ Function defined (was forward declared): " + func->returnType + " " + func->name);
            } else if (!symbolTable.declare(func->name, func->returnType, true, paramTypes)) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Duplicate C++ function declaration: " + func->name);
                reportLines.push_back("Error: Duplicate function '" + func->name + "'");
            } else {
                reportLines.push_back("C++ Function declared: " + func->returnType + " " + func->name);
            }

            symbolTable.enterScope();
            for (const auto& p : func->parameters) {
                if (!symbolTable.declare(p.name, p.type)) {
                    DiagnosticEngine::logSemanticError(filename, 0, 0, "Duplicate C++ parameter name: " + p.name);
                }
            }

            if (func->body) checkNode(func->body);
            symbolTable.exitScope();
            break;
        }
        case ASTNodeType::VAR_DECL: {
            auto vd = std::dynamic_pointer_cast<VarDeclNode>(node);
            if (!symbolTable.declare(vd->varName, vd->varType)) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Duplicate C++ variable declaration: " + vd->varName);
                reportLines.push_back("Error: Duplicate variable '" + vd->varName + "'");
            } else {
                reportLines.push_back("C++ Variable declared: " + vd->varType + " " + vd->varName);
            }
            if (vd->initExpr) checkNode(vd->initExpr);
            break;
        }
        case ASTNodeType::BLOCK: {
            auto block = std::dynamic_pointer_cast<BlockNode>(node);
            symbolTable.enterScope();
            for (const auto& s : block->statements) checkNode(s);
            symbolTable.exitScope();
            break;
        }
        case ASTNodeType::VAR_EXPR: {
            auto var = std::dynamic_pointer_cast<VarExprNode>(node);
            SymbolCPP* sym = symbolTable.lookup(var->name);
            if (!sym) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Undeclared C++ variable: " + var->name);
                reportLines.push_back("Error: Undeclared variable '" + var->name + "'");
            }
            break;
        }
        case ASTNodeType::INPUT_STMT: {
            auto in = std::dynamic_pointer_cast<InputNode>(node);
            SymbolCPP* sym = symbolTable.lookup(in->targetVar);
            if (!sym) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Undeclared C++ cin target: " + in->targetVar);
                reportLines.push_back("Error: Undeclared cin target '" + in->targetVar + "'");
            }
            break;
        }
        case ASTNodeType::ASSIGN_STMT: {
            auto ass = std::dynamic_pointer_cast<AssignNode>(node);
            SymbolCPP* sym = symbolTable.lookup(ass->varName);
            if (!sym) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Undeclared C++ variable assignment: " + ass->varName);
                reportLines.push_back("Error: Undeclared variable '" + ass->varName + "'");
            }
            if (ass->expr) checkNode(ass->expr);
            break;
        }
        case ASTNodeType::CALL_EXPR: {
            auto call = std::dynamic_pointer_cast<CallExprNode>(node);
            SymbolCPP* sym = symbolTable.lookup(call->funcName);
            if (!sym || !sym->isFunction) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Undeclared C++ function call: " + call->funcName);
                reportLines.push_back("Error: Undeclared function '" + call->funcName + "'");
            }
            for (const auto& arg : call->args) checkNode(arg);
            break;
        }
        default:
            break;
    }
}

void Semantic_CPP::saveReports(const std::string& symTablePath, const std::string& reportPath) const {
    std::ofstream symFile(symTablePath.c_str());
    if (symFile.is_open()) {
        symFile << symbolTable.toString();
        symFile.close();
    }

    std::ofstream repFile(reportPath.c_str());
    if (repFile.is_open()) {
        for (const auto& line : reportLines) {
            repFile << line << "\n";
        }
        repFile.close();
    }
}
