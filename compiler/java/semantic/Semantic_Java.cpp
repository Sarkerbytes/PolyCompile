#include "Semantic_Java.hpp"
#include <set>

bool Semantic_Java::analyze(ASTNodePtr root) {
    reportLines.clear();
    DiagnosticEngine::clear();
    foundMainMethod = false;
    reportLines.push_back("JAVA SEMANTIC ANALYSIS REPORT");
    reportLines.push_back("------------------------------");

    if (!root) {
        reportLines.push_back("Empty AST provided.");
        return true;
    }

    checkNode(root);

    if (!foundMainMethod) {
        DiagnosticEngine::logSemanticError(filename, 0, 0,
            "Java program must contain a 'public static void main(String[] args)' method");
        reportLines.push_back("Warning: No main method found.");
    }

    reportLines.push_back("Semantic analysis completed with " +
        std::to_string(DiagnosticEngine::getErrors().size()) + " errors.");
    return !DiagnosticEngine::hasErrors();
}

void Semantic_Java::checkNode(ASTNodePtr node) {
    if (!node) return;

    switch (node->getType()) {
        case ASTNodeType::PROGRAM: {
            auto prog = std::dynamic_pointer_cast<ProgramNode>(node);
            for (const auto& decl : prog->declarations) checkNode(decl);
            break;
        }
        case ASTNodeType::FUNCTION: {
            auto func = std::dynamic_pointer_cast<FunctionNode>(node);
            std::vector<std::string> paramTypes;
            for (const auto& p : func->parameters) paramTypes.push_back(p.type);

            // Check for main method
            if (func->name == "main" && func->returnType == "void") {
                foundMainMethod = true;
                reportLines.push_back("Main method found: void main(String[] args)");
            }

            if (!symbolTable.declare(func->name, func->returnType, true, paramTypes)) {
                DiagnosticEngine::logSemanticError(filename, 0, 0,
                    "Duplicate Java method declaration: " + func->name);
                reportLines.push_back("Error: Duplicate method '" + func->name + "'");
            } else {
                reportLines.push_back("Java Method declared: " + func->returnType + " " + func->name);
            }

            symbolTable.enterScope();
            for (const auto& p : func->parameters) {
                symbolTable.declare(p.name, p.type);
            }
            if (func->body) checkNode(func->body);
            symbolTable.exitScope();
            break;
        }
        case ASTNodeType::VAR_DECL: {
            auto vd = std::dynamic_pointer_cast<VarDeclNode>(node);
            if (!symbolTable.declare(vd->varName, vd->varType)) {
                DiagnosticEngine::logSemanticError(filename, 0, 0,
                    "Duplicate Java variable declaration: " + vd->varName);
                reportLines.push_back("Error: Duplicate variable '" + vd->varName + "'");
            } else {
                reportLines.push_back("Java Variable declared: " + vd->varType + " " + vd->varName);
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
            SymbolJava* sym = symbolTable.lookup(var->name);
            if (!sym) {
                // Suppress common Java built-in names
                static const std::set<std::string> builtins = {
                    "System", "Scanner", "Math", "Integer", "String", "args"
                };
                if (builtins.find(var->name) == builtins.end()) {
                    DiagnosticEngine::logSemanticError(filename, 0, 0,
                        "Undeclared Java variable: " + var->name);
                    reportLines.push_back("Error: Undeclared variable '" + var->name + "'");
                }
            }
            break;
        }
        case ASTNodeType::ASSIGN_STMT: {
            auto ass = std::dynamic_pointer_cast<AssignNode>(node);
            SymbolJava* sym = symbolTable.lookup(ass->varName);
            if (!sym) {
                DiagnosticEngine::logSemanticError(filename, 0, 0,
                    "Undeclared Java variable in assignment: " + ass->varName);
                reportLines.push_back("Error: Undeclared variable '" + ass->varName + "'");
            }
            if (ass->expr) checkNode(ass->expr);
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
        default: break;
    }
}

void Semantic_Java::saveReports(const std::string& symTablePath, const std::string& reportPath) const {
    std::ofstream symFile(symTablePath.c_str());
    if (symFile.is_open()) {
        symFile << symbolTable.toString();
        symFile.close();
    }
    std::ofstream repFile(reportPath.c_str());
    if (repFile.is_open()) {
        for (const auto& line : reportLines) repFile << line << "\n";
        repFile.close();
    }
}
