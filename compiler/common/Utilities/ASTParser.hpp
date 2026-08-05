#ifndef AST_PARSER_HPP
#define AST_PARSER_HPP

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "../Token/Token.hpp"
#include "ASTBase.hpp"

class ASTParser {
private:
    std::vector<Token> tokens;
    size_t pos;
    bool isJava;

    Token peek(int offset = 0) const {
        if (pos + offset >= tokens.size()) return Token(TokenType::END_OF_FILE, "EOF", 0, 0);
        return tokens[pos + offset];
    }

    Token advance() {
        if (pos < tokens.size()) return tokens[pos++];
        return Token(TokenType::END_OF_FILE, "EOF", 0, 0);
    }

    bool check(const std::string& lexeme) const {
        return peek().lexeme == lexeme;
    }

    bool match(const std::string& lexeme) {
        if (check(lexeme)) {
            advance();
            return true;
        }
        return false;
    }

    bool isAtEnd() const {
        return pos >= tokens.size() || peek().type == TokenType::END_OF_FILE;
    }

public:
    ASTParser(const std::vector<Token>& toks, bool javaMode = false)
        : tokens(toks), pos(0), isJava(javaMode) {}

    ASTNodePtr parseProgram() {
        auto prog = std::make_shared<ProgramNode>();

        while (!isAtEnd()) {
            Token t = peek();

            // Skip preprocessor, import, package, using
            if (t.lexeme == "#include" || t.lexeme.find("#include") == 0 || t.lexeme == "import" || t.lexeme == "using" || t.lexeme == "package") {
                while (!isAtEnd() && peek().lexeme != ";" && peek().line == t.line) advance();
                if (match(";")) {}
                continue;
            }

            // Skip class wrapper
            if (t.lexeme == "class" || (t.lexeme == "public" && peek(1).lexeme == "class")) {
                while (!isAtEnd() && peek().lexeme != "{") advance();
                match("{");
                continue;
            }

            // Look for function main
            if (t.lexeme == "int" || t.lexeme == "void" || t.lexeme == "public" || t.lexeme == "static") {
                std::string retType = isJava ? "void" : "int";
                size_t lookahead = 0;
                while (pos + lookahead < tokens.size() && tokens[pos + lookahead].lexeme != "main" && tokens[pos + lookahead].lexeme != "{") {
                    if (tokens[pos + lookahead].lexeme == "void") retType = "void";
                    lookahead++;
                }
                if (pos + lookahead < tokens.size() && tokens[pos + lookahead].lexeme == "main") {
                    pos += lookahead + 1;
                    while (!isAtEnd() && peek().lexeme != "{") advance();
                    if (match("{")) {
                        auto func = std::make_shared<FunctionNode>();
                        func->name = "main";
                        func->returnType = isJava ? "void" : retType;
                        func->body = parseBlock();
                        prog->declarations.push_back(func);
                        break;
                    }
                }
            }

            if (t.lexeme == "{") {
                match("{");
                auto func = std::make_shared<FunctionNode>();
                func->name = "main";
                func->returnType = isJava ? "void" : "int";
                func->body = parseBlock();
                prog->declarations.push_back(func);
                break;
            }

            advance();
        }

        if (prog->declarations.empty()) {
            pos = 0;
            auto func = std::make_shared<FunctionNode>();
            func->name = "main";
            func->returnType = isJava ? "void" : "int";
            auto block = std::make_shared<BlockNode>();
            while (!isAtEnd()) {
                Token t = peek();
                if (t.lexeme == "#include" || t.lexeme.find("#include") == 0 || t.lexeme == "import" || t.lexeme == "using" || t.lexeme == "class") {
                    advance();
                    continue;
                }
                auto stmt = parseStatement();
                if (stmt) block->statements.push_back(stmt);
                else advance();
            }
            func->body = block;
            prog->declarations.push_back(func);
        }

        return prog;
    }

private:
    ASTNodePtr parseBlock() {
        auto block = std::make_shared<BlockNode>();
        while (!isAtEnd() && peek().lexeme != "}") {
            auto stmt = parseStatement();
            if (stmt) {
                block->statements.push_back(stmt);
            } else {
                advance();
            }
        }
        match("}");
        return block;
    }

    ASTNodePtr parseStatement() {
        if (isAtEnd() || peek().lexeme == "}") return nullptr;

        Token t = peek();

        if (t.lexeme == "{") {
            match("{");
            return parseBlock();
        }

        if (t.lexeme == "while") {
            advance();
            match("(");
            auto cond = parseExpression();
            match(")");
            ASTNodePtr body = nullptr;
            if (check("{")) {
                match("{");
                body = parseBlock();
            } else {
                body = parseStatement();
            }
            auto node = std::make_shared<WhileNode>();
            node->condition = cond;
            node->body = body;
            return node;
        }

        if (t.lexeme == "for") {
            advance();
            match("(");
            ASTNodePtr init = nullptr;
            if (!check(";")) {
                init = parseStatement();
            } else {
                match(";");
            }
            ASTNodePtr cond = nullptr;
            if (!check(";")) {
                cond = parseExpression();
            }
            match(";");
            ASTNodePtr update = nullptr;
            if (!check(")")) {
                update = parseExpression();
            }
            match(")");
            ASTNodePtr body = nullptr;
            if (check("{")) {
                match("{");
                body = parseBlock();
            } else {
                body = parseStatement();
            }
            auto node = std::make_shared<ForNode>();
            node->init = init;
            node->condition = cond;
            node->update = update;
            node->body = body;
            return node;
        }

        if (t.lexeme == "if") {
            advance();
            match("(");
            auto cond = parseExpression();
            match(")");
            ASTNodePtr thenB = nullptr;
            if (check("{")) {
                match("{");
                thenB = parseBlock();
            } else {
                thenB = parseStatement();
            }
            ASTNodePtr elseB = nullptr;
            if (match("else")) {
                if (check("{")) {
                    match("{");
                    elseB = parseBlock();
                } else {
                    elseB = parseStatement();
                }
            }
            auto node = std::make_shared<IfNode>();
            node->condition = cond;
            node->thenBranch = thenB;
            node->elseBranch = elseB;
            return node;
        }

        if (t.lexeme == "switch") {
            advance();
            match("(");
            auto expr = parseExpression();
            match(")");
            match("{");
            auto node = std::make_shared<SwitchNode>();
            node->expression = expr;
            while (!isAtEnd() && !check("}")) {
                if (match("case")) {
                    SwitchCase sc;
                    sc.value = parseExpression();
                    match(":");
                    while (!isAtEnd() && !check("case") && !check("default") && !check("}")) {
                        auto s = parseStatement();
                        if (s) sc.body.push_back(s);
                    }
                    node->cases.push_back(sc);
                } else if (match("default")) {
                    match(":");
                    while (!isAtEnd() && !check("case") && !check("}") && !check("default")) {
                        auto s = parseStatement();
                        if (s) node->defaultBody.push_back(s);
                    }
                } else {
                    advance();
                }
            }
            match("}");
            return node;
        }

        if (t.lexeme == "return") {
            advance();
            ASTNodePtr expr = nullptr;
            if (!check(";")) {
                expr = parseExpression();
            }
            match(";");
            auto node = std::make_shared<ReturnNode>();
            node->expr = expr;
            return node;
        }

        if (t.lexeme == "break") {
            advance();
            match(";");
            return std::make_shared<BreakNode>();
        }
        if (t.lexeme == "continue") {
            advance();
            match(";");
            return std::make_shared<ContinueNode>();
        }

        if (t.lexeme == "printf" || t.lexeme == "cout" || t.lexeme == "System.out.println" || t.lexeme == "System.out.print" || (t.lexeme == "System" && peek(1).lexeme == "." && peek(2).lexeme == "out")) {
            return parseOutput();
        }

        if (t.lexeme == "scanf" || t.lexeme == "cin") {
            return parseInput();
        }

        if (t.lexeme == "int" || t.lexeme == "float" || t.lexeme == "double" || t.lexeme == "char" || t.lexeme == "String" || t.lexeme == "bool") {
            std::string typeStr = advance().lexeme;
            auto listNode = std::make_shared<VarDeclListNode>();

            while (!isAtEnd()) {
                if (peek().type != TokenType::IDENTIFIER) break;
                std::string varName = advance().lexeme;
                ASTNodePtr initExpr = nullptr;
                if (match("=")) {
                    initExpr = parseExpression();
                }
                auto vd = std::make_shared<VarDeclNode>();
                vd->varType = typeStr;
                vd->varName = varName;
                vd->initExpr = initExpr;
                listNode->decls.push_back(vd);

                if (match(",")) continue;
                break;
            }
            match(";");
            if (listNode->decls.size() == 1) return listNode->decls[0];
            return listNode;
        }

        if (t.type == TokenType::IDENTIFIER) {
            std::string varName = advance().lexeme;

            if (check("=") || check("+=") || check("-=") || check("*=") || check("/=")) {
                std::string op = advance().lexeme;
                auto expr = parseExpression();
                match(";");
                auto ass = std::make_shared<AssignNode>();
                ass->varName = varName;
                ass->op = op;
                ass->expr = expr;
                return ass;
            }
            if (check("++") || check("--")) {
                std::string op = advance().lexeme;
                match(";");
                auto un = std::make_shared<UnaryExprNode>();
                un->op = (op == "++") ? "post++" : "post--";
                un->operand = std::make_shared<VarExprNode>();
                std::dynamic_pointer_cast<VarExprNode>(un->operand)->name = varName;
                return un;
            }
        }

        auto expr = parseExpression();
        match(";");
        return expr;
    }

    ASTNodePtr parseOutput() {
        auto node = std::make_shared<OutputNode>();
        Token t = advance();

        if (t.lexeme == "printf") {
            match("(");
            while (!isAtEnd() && !check(")")) {
                auto arg = parseExpression();
                if (arg) node->args.push_back(arg);
                if (!match(",")) break;
            }
            match(")");
            match(";");
            node->hasNewline = true;
        } else if (t.lexeme == "cout") {
            while (!isAtEnd() && !check(";")) {
                if (match("<<")) {
                    if (check("endl")) {
                        advance();
                        node->hasNewline = true;
                    } else {
                        auto arg = parseExpression();
                        if (arg) node->args.push_back(arg);
                    }
                } else {
                    advance();
                }
            }
            match(";");
        } else {
            if (t.lexeme == "System") {
                while (!isAtEnd() && peek().lexeme != "println" && peek().lexeme != "print" && peek().lexeme != "(") advance();
                if (peek().lexeme == "println" || peek().lexeme == "print") t = advance();
            }
            if (t.lexeme.find("println") != std::string::npos) node->hasNewline = true;
            match("(");
            while (!isAtEnd() && !check(")")) {
                auto arg = parseExpression();
                if (arg) node->args.push_back(arg);
                if (!match("+") && !match(",")) break;
            }
            match(")");
            match(";");
        }
        return node;
    }

    ASTNodePtr parseInput() {
        auto node = std::make_shared<InputNode>();
        Token t = advance();
        if (t.lexeme == "scanf") {
            match("(");
            if (peek().type == TokenType::STRING_LITERAL) advance();
            while (!isAtEnd() && !check(")")) {
                if (match(",")) {}
                if (match("&")) {}
                if (peek().type == TokenType::IDENTIFIER) {
                    node->targetVars.push_back(advance().lexeme);
                } else {
                    advance();
                }
            }
            if (!node->targetVars.empty()) node->targetVar = node->targetVars[0];
            match(")");
            match(";");
        } else if (t.lexeme == "cin") {
            while (!isAtEnd() && !check(";")) {
                if (match(">>")) {
                    if (peek().type == TokenType::IDENTIFIER) {
                        node->targetVars.push_back(advance().lexeme);
                    }
                } else {
                    advance();
                }
            }
            if (!node->targetVars.empty()) node->targetVar = node->targetVars[0];
            match(";");
        }
        return node;
    }

    ASTNodePtr parseExpression() {
        return parseEquality();
    }

    ASTNodePtr parseEquality() {
        auto expr = parseRelational();
        while (check("==") || check("!=")) {
            std::string op = advance().lexeme;
            auto right = parseRelational();
            auto bin = std::make_shared<BinaryExprNode>();
            bin->op = op;
            bin->left = expr;
            bin->right = right;
            expr = bin;
        }
        return expr;
    }

    ASTNodePtr parseRelational() {
        auto expr = parseAdditive();
        while (check("<") || check(">") || check("<=") || check(">=")) {
            std::string op = advance().lexeme;
            auto right = parseAdditive();
            auto bin = std::make_shared<BinaryExprNode>();
            bin->op = op;
            bin->left = expr;
            bin->right = right;
            expr = bin;
        }
        return expr;
    }

    ASTNodePtr parseAdditive() {
        auto expr = parseMultiplicative();
        while (check("+") || check("-")) {
            std::string op = advance().lexeme;
            auto right = parseMultiplicative();
            auto bin = std::make_shared<BinaryExprNode>();
            bin->op = op;
            bin->left = expr;
            bin->right = right;
            expr = bin;
        }
        return expr;
    }

    ASTNodePtr parseMultiplicative() {
        auto expr = parsePrimary();
        while (check("*") || check("/") || check("%")) {
            std::string op = advance().lexeme;
            auto right = parsePrimary();
            auto bin = std::make_shared<BinaryExprNode>();
            bin->op = op;
            bin->left = expr;
            bin->right = right;
            expr = bin;
        }
        return expr;
    }

    ASTNodePtr parsePrimary() {
        if (isAtEnd()) return nullptr;

        Token t = peek();

        if (t.lexeme == "(") {
            advance();
            auto expr = parseExpression();
            match(")");
            return expr;
        }

        if (t.type == TokenType::INT_LITERAL || t.type == TokenType::FLOAT_LITERAL) {
            advance();
            auto lit = std::make_shared<LiteralNode>();
            lit->value = t.lexeme;
            lit->valueType = (t.type == TokenType::INT_LITERAL) ? "int" : "float";
            return lit;
        }

        if (t.type == TokenType::STRING_LITERAL) {
            advance();
            auto lit = std::make_shared<LiteralNode>();
            lit->value = t.lexeme;
            lit->valueType = "string";
            return lit;
        }

        if (t.lexeme == "true" || t.lexeme == "false") {
            advance();
            auto lit = std::make_shared<LiteralNode>();
            lit->value = t.lexeme;
            lit->valueType = "bool";
            return lit;
        }

        if (t.type == TokenType::IDENTIFIER) {
            advance();
            if (check("++") || check("--")) {
                std::string op = advance().lexeme;
                auto un = std::make_shared<UnaryExprNode>();
                un->op = (op == "++") ? "post++" : "post--";
                auto var = std::make_shared<VarExprNode>();
                var->name = t.lexeme;
                un->operand = var;
                return un;
            }
            auto var = std::make_shared<VarExprNode>();
            var->name = t.lexeme;
            return var;
        }

        advance();
        return nullptr;
    }
};

#endif // AST_PARSER_HPP
