#ifndef AST_BASE_HPP
#define AST_BASE_HPP

#include <string>
#include <vector>
#include <memory>
#include <sstream>

enum class ASTNodeType {
    PROGRAM,
    FUNCTION,
    VAR_DECL,
    VAR_DECL_LIST,
    BLOCK,
    IF_STMT,
    SWITCH_STMT,
    WHILE_STMT,
    DO_WHILE_STMT,
    FOR_STMT,
    RETURN_STMT,
    BREAK_STMT,
    CONTINUE_STMT,
    ASSIGN_STMT,
    BINARY_EXPR,
    UNARY_EXPR,
    LITERAL_EXPR,
    VAR_EXPR,
    CALL_EXPR,
    INPUT_STMT,
    OUTPUT_STMT
};

class ASTNode {
public:
    int line = 0;
    int col = 0;
    
    virtual ~ASTNode() {}
    virtual ASTNodeType getType() const = 0;
    virtual std::string toString(int indent = 0) const = 0;

protected:
    std::string getIndentStr(int indent) const {
        return std::string(indent * 2, ' ');
    }
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

class ProgramNode : public ASTNode {
public:
    std::vector<ASTNodePtr> declarations;

    ASTNodeType getType() const override { return ASTNodeType::PROGRAM; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "ProgramNode:\n";
        for (const auto& decl : declarations) {
            if (decl) ss << decl->toString(indent + 1);
        }
        return ss.str();
    }
};

struct Parameter {
    std::string type;
    std::string name;
};

class FunctionNode : public ASTNode {
public:
    std::string returnType;
    std::string name;
    std::vector<Parameter> parameters;
    ASTNodePtr body;

    ASTNodeType getType() const override { return ASTNodeType::FUNCTION; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "FunctionNode: " << returnType << " " << name << "(";
        for (size_t i = 0; i < parameters.size(); ++i) {
            ss << parameters[i].type << " " << parameters[i].name;
            if (i + 1 < parameters.size()) ss << ", ";
        }
        ss << ")\n";
        if (body) ss << body->toString(indent + 1);
        return ss.str();
    }
};

class VarDeclNode : public ASTNode {
public:
    std::string varType;
    std::string varName;
    ASTNodePtr initExpr;

    ASTNodeType getType() const override { return ASTNodeType::VAR_DECL; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "VarDeclNode: " << varType << " " << varName;
        if (initExpr) {
            ss << " =\n" << initExpr->toString(indent + 1);
        } else {
            ss << "\n";
        }
        return ss.str();
    }
};

// Represents comma-separated declarations: int a, b, c;
// Processed as a flat list — does NOT open a new scope.
class VarDeclListNode : public ASTNode {
public:
    std::vector<ASTNodePtr> decls;  // all VarDeclNode children

    ASTNodeType getType() const override { return ASTNodeType::VAR_DECL_LIST; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "VarDeclListNode:\n";
        for (const auto& d : decls) {
            if (d) ss << d->toString(indent + 1);
        }
        return ss.str();
    }
};


class BlockNode : public ASTNode {
public:
    std::vector<ASTNodePtr> statements;

    ASTNodeType getType() const override { return ASTNodeType::BLOCK; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "BlockNode:\n";
        for (const auto& stmt : statements) {
            if (stmt) ss << stmt->toString(indent + 1);
        }
        return ss.str();
    }
};

class IfNode : public ASTNode {
public:
    ASTNodePtr condition;
    ASTNodePtr thenBranch;
    ASTNodePtr elseBranch;

    ASTNodeType getType() const override { return ASTNodeType::IF_STMT; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "IfNode:\n";
        if (condition) ss << getIndentStr(indent + 1) << "Condition:\n" << condition->toString(indent + 2);
        if (thenBranch) ss << getIndentStr(indent + 1) << "Then:\n" << thenBranch->toString(indent + 2);
        if (elseBranch) ss << getIndentStr(indent + 1) << "Else:\n" << elseBranch->toString(indent + 2);
        return ss.str();
    }
};

struct SwitchCase {
    ASTNodePtr value;
    std::vector<ASTNodePtr> body;
};

class SwitchNode : public ASTNode {
public:
    ASTNodePtr expression;
    std::vector<SwitchCase> cases;
    std::vector<ASTNodePtr> defaultBody;

    ASTNodeType getType() const override { return ASTNodeType::SWITCH_STMT; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "SwitchNode:\n";
        if (expression) ss << expression->toString(indent + 1);
        for (const auto& c : cases) {
            ss << getIndentStr(indent + 1) << "Case:\n";
            if (c.value) ss << c.value->toString(indent + 2);
            for (const auto& s : c.body) ss << s->toString(indent + 2);
        }
        if (!defaultBody.empty()) {
            ss << getIndentStr(indent + 1) << "Default:\n";
            for (const auto& s : defaultBody) ss << s->toString(indent + 2);
        }
        return ss.str();
    }
};

class WhileNode : public ASTNode {
public:
    ASTNodePtr condition;
    ASTNodePtr body;

    ASTNodeType getType() const override { return ASTNodeType::WHILE_STMT; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "WhileNode:\n";
        if (condition) ss << condition->toString(indent + 1);
        if (body) ss << body->toString(indent + 1);
        return ss.str();
    }
};

class DoWhileNode : public ASTNode {
public:
    ASTNodePtr body;
    ASTNodePtr condition;

    ASTNodeType getType() const override { return ASTNodeType::DO_WHILE_STMT; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "DoWhileNode:\n";
        if (body) ss << body->toString(indent + 1);
        if (condition) ss << condition->toString(indent + 1);
        return ss.str();
    }
};

class ForNode : public ASTNode {
public:
    ASTNodePtr init;
    ASTNodePtr condition;
    ASTNodePtr update;
    ASTNodePtr body;

    ASTNodeType getType() const override { return ASTNodeType::FOR_STMT; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "ForNode:\n";
        if (init) ss << getIndentStr(indent + 1) << "Init:\n" << init->toString(indent + 2);
        if (condition) ss << getIndentStr(indent + 1) << "Cond:\n" << condition->toString(indent + 2);
        if (update) ss << getIndentStr(indent + 1) << "Update:\n" << update->toString(indent + 2);
        if (body) ss << getIndentStr(indent + 1) << "Body:\n" << body->toString(indent + 2);
        return ss.str();
    }
};

class ReturnNode : public ASTNode {
public:
    ASTNodePtr expr;

    ASTNodeType getType() const override { return ASTNodeType::RETURN_STMT; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "ReturnNode:\n";
        if (expr) ss << expr->toString(indent + 1);
        return ss.str();
    }
};

class BreakNode : public ASTNode {
public:
    ASTNodeType getType() const override { return ASTNodeType::BREAK_STMT; }
    std::string toString(int indent = 0) const override {
        return getIndentStr(indent) + "BreakNode\n";
    }
};

class ContinueNode : public ASTNode {
public:
    ASTNodeType getType() const override { return ASTNodeType::CONTINUE_STMT; }
    std::string toString(int indent = 0) const override {
        return getIndentStr(indent) + "ContinueNode\n";
    }
};

class AssignNode : public ASTNode {
public:
    std::string varName;
    std::string op;
    ASTNodePtr expr;

    ASTNodeType getType() const override { return ASTNodeType::ASSIGN_STMT; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "AssignNode: " << varName << " " << op << "\n";
        if (expr) ss << expr->toString(indent + 1);
        return ss.str();
    }
};

class BinaryExprNode : public ASTNode {
public:
    std::string op;
    ASTNodePtr left;
    ASTNodePtr right;

    ASTNodeType getType() const override { return ASTNodeType::BINARY_EXPR; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "BinaryExprNode: (" << op << ")\n";
        if (left) ss << left->toString(indent + 1);
        if (right) ss << right->toString(indent + 1);
        return ss.str();
    }
};

class UnaryExprNode : public ASTNode {
public:
    std::string op;
    ASTNodePtr operand;

    ASTNodeType getType() const override { return ASTNodeType::UNARY_EXPR; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "UnaryExprNode: (" << op << ")\n";
        if (operand) ss << operand->toString(indent + 1);
        return ss.str();
    }
};

class LiteralNode : public ASTNode {
public:
    std::string value;
    std::string valueType; // "int", "float", "string", "bool", "char"

    ASTNodeType getType() const override { return ASTNodeType::LITERAL_EXPR; }
    std::string toString(int indent = 0) const override {
        return getIndentStr(indent) + "LiteralNode (" + valueType + "): " + value + "\n";
    }
};

class VarExprNode : public ASTNode {
public:
    std::string name;

    ASTNodeType getType() const override { return ASTNodeType::VAR_EXPR; }
    std::string toString(int indent = 0) const override {
        return getIndentStr(indent) + "VarExprNode: " + name + "\n";
    }
};

class CallExprNode : public ASTNode {
public:
    std::string funcName;
    std::vector<ASTNodePtr> args;

    ASTNodeType getType() const override { return ASTNodeType::CALL_EXPR; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "CallExprNode: " << funcName << "\n";
        for (const auto& arg : args) {
            if (arg) ss << arg->toString(indent + 1);
        }
        return ss.str();
    }
};

class InputNode : public ASTNode {
public:
    std::string targetVar;          // first (or only) target variable
    std::vector<std::string> targetVars;  // all target variables (for multi-arg scanf)
    std::string promptMsg;

    ASTNodeType getType() const override { return ASTNodeType::INPUT_STMT; }
    std::string toString(int indent = 0) const override {
        std::string vars = targetVars.empty() ? targetVar
                         : (targetVars[0]);
        for (size_t i = 1; i < targetVars.size(); ++i) vars += ", " + targetVars[i];
        return getIndentStr(indent) + "InputNode: " + vars + "\n";
    }
};

class OutputNode : public ASTNode {
public:
    std::vector<ASTNodePtr> args;
    bool hasNewline;

    OutputNode() : hasNewline(false) {}

    ASTNodeType getType() const override { return ASTNodeType::OUTPUT_STMT; }
    std::string toString(int indent = 0) const override {
        std::stringstream ss;
        ss << getIndentStr(indent) << "OutputNode (newline=" << (hasNewline ? "true" : "false") << "):\n";
        for (const auto& arg : args) {
            if (arg) ss << arg->toString(indent + 1);
        }
        return ss.str();
    }
};

#endif // AST_BASE_HPP
