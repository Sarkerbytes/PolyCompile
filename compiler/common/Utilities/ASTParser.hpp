#ifndef AST_PARSER_HPP
#define AST_PARSER_HPP

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "../Token/Token.hpp"
#include "ASTBase.hpp"
#include "DiagnosticEngine.hpp"

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

    
    bool expect(const std::string& lexeme) {
        if (check(lexeme)) {
            advance();
            return true;
        }
        Token t = peek();
        DiagnosticEngine::logSyntaxError("source", t.line, t.column, "expected '" + lexeme + "' but found '" + t.lexeme + "'");
        return false;
    }
bool isAtEnd() const {
        return pos >= tokens.size() || peek().type == TokenType::END_OF_FILE;
    }

public:
    template<typename T>
    std::shared_ptr<T> createNode() {
        auto node = std::make_shared<T>();
        if (!tokens.empty()) {
            size_t idx = (pos > 0) ? pos - 1 : 0;
            if (idx < tokens.size()) {
                node->line = tokens[idx].line;
                node->col = tokens[idx].column;
            }
        }
        return node;
    }

    ASTParser(const std::vector<Token>& toks, bool javaMode = false)
        : tokens(toks), pos(0), isJava(javaMode) {}

    ASTNodePtr parseProgram() {
        auto prog = createNode<ProgramNode>();

        while (!isAtEnd()) {
            Token t = peek();

            // Skip preprocessor, import, package, using
            if (t.lexeme == "#include" || t.lexeme.find("#include") == 0) {
                bool hasAngle = (t.lexeme.find('<') != std::string::npos && t.lexeme.find('>') != std::string::npos);
                bool hasQuotes = (t.lexeme.find('"') != std::string::npos && t.lexeme.rfind('"') != t.lexeme.find('"'));
                if (!hasAngle && !hasQuotes) {
                    DiagnosticEngine::logSyntaxError("source", t.line, t.column, "invalid #include syntax, expected <...> or \"...\"");
                }
                while (!isAtEnd() && peek().line == t.line) advance();
                continue;
            }
            if (t.lexeme == "import" || t.lexeme == "package") {
                advance();
                bool hasDot = false;
                while (!isAtEnd() && peek().lexeme != ";" && peek().line == t.line) {
                    if (peek().lexeme == ".") hasDot = true;
                    advance();
                }
                if (t.lexeme == "import" && !hasDot) {
                    DiagnosticEngine::logSyntaxError("source", t.line, t.column, "invalid import syntax, expected dotted path");
                }
                if (match(";")) {}
                continue;
            }
            if (t.lexeme == "using") {
                advance();
                bool hasNamespace = false;
                while (!isAtEnd() && peek().lexeme != ";" && peek().line == t.line) {
                    if (peek().lexeme == "namespace") hasNamespace = true;
                    advance();
                }
                if (!hasNamespace) {
                    DiagnosticEngine::logSyntaxError("source", t.line, t.column, "invalid using syntax, expected 'namespace'");
                }
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
                        auto func = createNode<FunctionNode>();
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
                auto func = createNode<FunctionNode>();
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
            auto func = createNode<FunctionNode>();
            func->name = "main";
            func->returnType = isJava ? "void" : "int";
            auto block = createNode<BlockNode>();
            while (!isAtEnd()) {
                Token t = peek();
                if (t.lexeme == "#include" || t.lexeme.find("#include") == 0) {
                    if (t.lexeme.find('<') != std::string::npos && t.lexeme.find('>') == std::string::npos) {
                        DiagnosticEngine::logSyntaxError("source", t.line, t.column, "missing closing '>' in #include");
                    }
                    while (!isAtEnd() && peek().line == t.line) advance();
                    continue;
                }
                if (t.lexeme == "import" || t.lexeme == "using" || t.lexeme == "class") {
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
        auto block = createNode<BlockNode>();
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
            expect("("); auto cond = parseExpression(); expect(")");
            ASTNodePtr body = nullptr;
            if (check("{")) {
                match("{");
                body = parseBlock();
            } else {
                body = parseStatement();
            }
            auto node = createNode<WhileNode>();
            node->condition = cond;
            node->body = body;
            return node;
        }

        if (t.lexeme == "for") {
            advance();
            expect("("); ASTNodePtr init = nullptr;
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
            expect(")"); ASTNodePtr body = nullptr;
            if (check("{")) {
                match("{");
                body = parseBlock();
            } else {
                body = parseStatement();
            }
            auto node = createNode<ForNode>();
            node->init = init;
            node->condition = cond;
            node->update = update;
            node->body = body;
            return node;
        }

        if (t.lexeme == "if") {
            advance();
            expect("("); auto cond = parseExpression(); expect(")");
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
            auto node = createNode<IfNode>();
            node->condition = cond;
            node->thenBranch = thenB;
            node->elseBranch = elseB;
            return node;
        }

        if (t.lexeme == "switch") {
            advance();
            expect("("); auto expr = parseExpression(); expect(")"); expect("{");
            auto node = createNode<SwitchNode>();
            node->expression = expr;
            while (!isAtEnd() && !check("}")) {
                if (match("case")) {
                    SwitchCase sc;
                    sc.value = parseExpression();
                    expect(":"); while (!isAtEnd() && !check("case") && !check("default") && !check("}")) {
                        auto s = parseStatement();
                        if (s) sc.body.push_back(s);
                    }
                    node->cases.push_back(sc);
                } else if (match("default")) {
                    expect(":"); while (!isAtEnd() && !check("case") && !check("}") && !check("default")) {
                        auto s = parseStatement();
                        if (s) node->defaultBody.push_back(s);
                    }
                } else {
                    advance();
                }
            }
            expect("}"); return node;
        }

        if (t.lexeme == "return") {
            advance();
            ASTNodePtr expr = nullptr;
            if (!check(";")) {
                expr = parseExpression();
            }
            expect(";"); auto node = createNode<ReturnNode>();
            node->expr = expr;
            return node;
        }

        if (t.lexeme == "break") {
            advance();
            expect(";"); return createNode<BreakNode>();
        }
        if (t.lexeme == "continue") {
            advance();
            expect(";"); return createNode<ContinueNode>();
        }

        if (t.lexeme == "printf" || t.lexeme == "cout" || t.lexeme == "System.out.println" || t.lexeme == "System.out.print" || (t.lexeme == "System" && peek(1).lexeme == "." && peek(2).lexeme == "out")) {
            return parseOutput();
        }

        if (t.lexeme == "scanf" || t.lexeme == "cin") {
            return parseInput();
        }

        if (t.lexeme == "int" || t.lexeme == "float" || t.lexeme == "double" || t.lexeme == "char" || t.lexeme == "String" || t.lexeme == "bool") {
            std::string typeStr = advance().lexeme;
            auto listNode = createNode<VarDeclListNode>();

            while (!isAtEnd()) {
                if (peek().type != TokenType::IDENTIFIER) break;
                std::string varName = advance().lexeme;
                ASTNodePtr initExpr = nullptr;
                if (match("=")) {
                    initExpr = parseExpression();
                }
                auto vd = createNode<VarDeclNode>();
                vd->varType = typeStr;
                vd->varName = varName;
                vd->initExpr = initExpr;
                listNode->decls.push_back(vd);

                if (match(",")) continue;
                break;
            }
            expect(";"); if (listNode->decls.size() == 1) return listNode->decls[0];
            return listNode;
        }

        if (t.type == TokenType::IDENTIFIER) {
            std::string varName = advance().lexeme;

            if (check("=") || check("+=") || check("-=") || check("*=") || check("/=")) {
                std::string op = advance().lexeme;
                auto expr = parseExpression(); expect(";");
                auto ass = createNode<AssignNode>();
                ass->varName = varName;
                ass->op = op;
                ass->expr = expr;
                return ass;
            }
            if (check("++") || check("--")) {
                std::string op = advance().lexeme;
                expect(";"); auto un = createNode<UnaryExprNode>();
                un->op = (op == "++") ? "post++" : "post--";
                un->operand = createNode<VarExprNode>();
                std::dynamic_pointer_cast<VarExprNode>(un->operand)->name = varName;
                return un;
            }
        }

        auto expr = parseExpression(); expect(";");
        return expr;
    }

    ASTNodePtr parseOutput() {
        auto node = createNode<OutputNode>();
        Token t = advance();

        if (t.lexeme == "printf") {
            expect("(");
            while (!isAtEnd() && !check(")")) {
                auto arg = parseExpression();
                if (arg) node->args.push_back(arg);
                if (!match(",")) break;
            }
            expect(")"); expect(";"); node->hasNewline = true;
        } else if (t.lexeme == "cout") {
            while (!isAtEnd() && !check(";")) {
                if (expect("<<")) {
                    if (check("endl")) {
                        advance();
                        node->hasNewline = true;
                    } else {
                        auto arg = parseExpression();
                        if (arg) node->args.push_back(arg);
                    }
                } else {
                    break;
                }
            }
            expect(";"); 
        } else {
            if (t.lexeme == "System") {
                while (!isAtEnd() && peek().lexeme != "println" && peek().lexeme != "print" && peek().lexeme != "(" && peek().lexeme != ";") advance();
                if (peek().lexeme == "println" || peek().lexeme == "print") t = advance();
            }
            if (t.lexeme.find("println") != std::string::npos) node->hasNewline = true;
            expect("(");
            while (!isAtEnd() && !check(")")) {
                auto arg = parseExpression();
                if (arg) node->args.push_back(arg);
                if (!match("+") && !match(",")) break;
            }
            expect(")"); expect(";"); 
        }
        return node;
    }

    ASTNodePtr parseInput() {
        auto node = createNode<InputNode>();
        Token t = advance();
        if (t.lexeme == "scanf") { expect("(");
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
            expect(")"); expect(";"); } else if (t.lexeme == "cin") {
            while (!isAtEnd() && !check(";")) {
                if (expect(">>")) {
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
            auto bin = createNode<BinaryExprNode>();
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
            auto bin = createNode<BinaryExprNode>();
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
            auto bin = createNode<BinaryExprNode>();
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
            auto bin = createNode<BinaryExprNode>();
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
            auto lit = createNode<LiteralNode>();
            lit->value = t.lexeme;
            lit->valueType = (t.type == TokenType::INT_LITERAL) ? "int" : "float";
            return lit;
        }

        if (t.type == TokenType::STRING_LITERAL) {
            advance();
            auto lit = createNode<LiteralNode>();
            lit->value = t.lexeme;
            lit->valueType = "string";
            return lit;
        }

        if (t.lexeme == "true" || t.lexeme == "false") {
            advance();
            auto lit = createNode<LiteralNode>();
            lit->value = t.lexeme;
            lit->valueType = "bool";
            return lit;
        }

        if (t.type == TokenType::IDENTIFIER) {
            advance();
            if (check("++") || check("--")) {
                std::string op = advance().lexeme;
                auto un = createNode<UnaryExprNode>();
                un->op = (op == "++") ? "post++" : "post--";
                auto var = createNode<VarExprNode>();
                var->name = t.lexeme;
                un->operand = var;
                return un;
            }
            auto var = createNode<VarExprNode>();
            var->name = t.lexeme;
            return var;
        }

        advance();
        return nullptr;
    }
};

#endif // AST_PARSER_HPP
