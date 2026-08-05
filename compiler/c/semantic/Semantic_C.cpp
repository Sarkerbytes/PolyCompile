#include "Semantic_C.hpp"

bool Semantic_C::analyze(ASTNodePtr root) {
    reportLines.clear();
    DiagnosticEngine::clear();
    reportLines.push_back("C SEMANTIC ANALYSIS REPORT: ");
    reportLines.push_back(" ");

    if (!root) {
        reportLines.push_back("Empty AST provided.");
        return true;
    }

    checkNode(root);
    reportLines.push_back("Semantic analysis completed with " + std::to_string(DiagnosticEngine::getErrors().size()) + " errors.");
    return !DiagnosticEngine::hasErrors();
}

void Semantic_C::checkNode(ASTNodePtr node) {
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

            SymbolC* existing = symbolTable.lookup(func->name);
            if (existing && existing->isFunction && existing->type == func->returnType) {
                // Forward declaration redefinition is OK - skip re-insertion
                reportLines.push_back("Function defined (was forward declared): " + func->returnType + " " + func->name);
            } else if (!symbolTable.declare(func->name, func->returnType, true, paramTypes)) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Duplicate function declaration: " + func->name);
                reportLines.push_back("Error: Duplicate function '" + func->name + "'");
            } else {
                reportLines.push_back("Function declared: " + func->returnType + " " + func->name);
            }

            symbolTable.enterScope();
            currentFuncReturnType = func->returnType;
            for (const auto& p : func->parameters) {
                if (!symbolTable.declare(p.name, p.type)) {
                    DiagnosticEngine::logSemanticError(filename, 0, 0, "Duplicate parameter name: " + p.name);
                }
            }

            if (func->body) checkNode(func->body);
            symbolTable.exitScope();
            break;
        }
        case ASTNodeType::VAR_DECL: {
            auto vd = std::dynamic_pointer_cast<VarDeclNode>(node);
            if (!symbolTable.declare(vd->varName, vd->varType)) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Duplicate variable declaration: " + vd->varName);
                reportLines.push_back("Error: Duplicate variable '" + vd->varName + "'");
            } else {
                reportLines.push_back("Variable declared: " + vd->varType + " " + vd->varName);
            }
            if (vd->initExpr) checkNode(vd->initExpr);
            break;
        }
        case ASTNodeType::VAR_DECL_LIST: {
            auto vdl = std::dynamic_pointer_cast<VarDeclListNode>(node);
            for (const auto& decl : vdl->decls) {
                checkNode(decl);  // each child is a VAR_DECL processed in current scope
            }
            break;
        }
        case ASTNodeType::BLOCK: {
            auto block = std::dynamic_pointer_cast<BlockNode>(node);
            symbolTable.enterScope();
            for (const auto& s : block->statements) {
                checkNode(s);
            }
            symbolTable.exitScope();
            break;
        }
        case ASTNodeType::VAR_EXPR: {
            auto var = std::dynamic_pointer_cast<VarExprNode>(node);
            SymbolC* sym = symbolTable.lookup(var->name);
            if (!sym) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Undeclared variable: " + var->name);
                reportLines.push_back("Error: Undeclared variable '" + var->name + "'");
            }
            break;
        }
        case ASTNodeType::ASSIGN_STMT: {
            auto ass = std::dynamic_pointer_cast<AssignNode>(node);
            SymbolC* sym = symbolTable.lookup(ass->varName);
            if (!sym) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Undeclared variable assignment: " + ass->varName);
                reportLines.push_back("Error: Undeclared variable '" + ass->varName + "'");
            }
            if (ass->expr) checkNode(ass->expr);
            break;
        }
        case ASTNodeType::CALL_EXPR: {
            auto call = std::dynamic_pointer_cast<CallExprNode>(node);
            SymbolC* sym = symbolTable.lookup(call->funcName);
            if (!sym || !sym->isFunction) {
                DiagnosticEngine::logSemanticError(filename, 0, 0, "Undeclared function call: " + call->funcName);
                reportLines.push_back("Error: Undeclared function '" + call->funcName + "'");
            }
            for (const auto& arg : call->args) checkNode(arg);
            break;
        }
        case ASTNodeType::IF_STMT: {
            auto ifStmt = std::dynamic_pointer_cast<IfNode>(node);
            if (ifStmt->condition) checkNode(ifStmt->condition);
            if (ifStmt->thenBranch) checkNode(ifStmt->thenBranch);
            if (ifStmt->elseBranch) checkNode(ifStmt->elseBranch);
            break;
        }
        case ASTNodeType::WHILE_STMT: {
            auto whileStmt = std::dynamic_pointer_cast<WhileNode>(node);
            if (whileStmt->condition) checkNode(whileStmt->condition);
            if (whileStmt->body) checkNode(whileStmt->body);
            break;
        }
        case ASTNodeType::DO_WHILE_STMT: {
            auto doStmt = std::dynamic_pointer_cast<DoWhileNode>(node);
            if (doStmt->body) checkNode(doStmt->body);
            if (doStmt->condition) checkNode(doStmt->condition);
            break;
        }
        case ASTNodeType::FOR_STMT: {
            auto forStmt = std::dynamic_pointer_cast<ForNode>(node);
            if (forStmt->init) checkNode(forStmt->init);
            if (forStmt->condition) checkNode(forStmt->condition);
            if (forStmt->update) checkNode(forStmt->update);
            if (forStmt->body) checkNode(forStmt->body);
            break;
        }
        case ASTNodeType::BINARY_EXPR: {
            auto bin = std::dynamic_pointer_cast<BinaryExprNode>(node);
            if (bin->left) checkNode(bin->left);
            if (bin->right) checkNode(bin->right);
            break;
        }
        case ASTNodeType::RETURN_STMT: {
            auto ret = std::dynamic_pointer_cast<ReturnNode>(node);
            if (ret->expr) checkNode(ret->expr);
            break;
        }
        default:
            break;
    }
}

void Semantic_C::saveReports(const std::string& symTablePath, const std::string& reportPath) const {
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
