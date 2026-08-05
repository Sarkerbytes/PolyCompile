#include "Parser_Java.hpp"
#include "../../common/Utilities/DiagnosticEngine.hpp"

Parser_Java::Parser_Java(const std::vector<Token>& tks, const std::string& fname)
    : tokens(tks), filename(fname), current(0) {}

Token Parser_Java::peek() const {
    if (current >= tokens.size()) return Token(TokenType::END_OF_FILE, "EOF", 0, 0);
    return tokens[current];
}
Token Parser_Java::previous() const {
    if (current == 0) return Token(TokenType::UNKNOWN, "", 0, 0);
    return tokens[current - 1];
}
bool Parser_Java::isAtEnd() const { return peek().type == TokenType::END_OF_FILE; }
Token Parser_Java::advance() {
    if (!isAtEnd()) current++;
    return previous();
}
bool Parser_Java::check(TokenType type, const std::string& lexeme) const {
    if (isAtEnd()) return false;
    if (peek().type != type) return false;
    if (!lexeme.empty() && peek().lexeme != lexeme) return false;
    return true;
}
bool Parser_Java::match(TokenType type, const std::string& lexeme) {
    if (check(type, lexeme)) { advance(); return true; }
    return false;
}
Token Parser_Java::consume(TokenType type, const std::string& msg) {
    if (check(type)) return advance();
    Token t = peek();
    DiagnosticEngine::logSyntaxError(filename, t.line, t.column, msg + " (found '" + t.lexeme + "')");
    return t;
}
Token Parser_Java::consumeLexeme(const std::string& lexeme, const std::string& msg) {
    if (peek().lexeme == lexeme) return advance();
    Token t = peek();
    DiagnosticEngine::logSyntaxError(filename, t.line, t.column, msg + " (expected '" + lexeme + "', found '" + t.lexeme + "')");
    return t;
}

bool Parser_Java::isTypeKeyword() const {
    const std::string& l = peek().lexeme;
    return (l == "int" || l == "float" || l == "double" || l == "char" || l == "boolean"
            || l == "String" || l == "long" || l == "short" || l == "byte" || l == "void");
}

std::string Parser_Java::currentTypeKeyword() {
    return advance().lexeme;
}

ASTNodePtr Parser_Java::parse() { return parseProgram(); }

ASTNodePtr Parser_Java::parseProgram() {
    auto prog = std::make_shared<ProgramNode>();
    while (!isAtEnd()) {
        // skip access modifiers
        if (match(TokenType::KEYWORD, "public") || match(TokenType::KEYWORD, "private")
            || match(TokenType::KEYWORD, "protected") || match(TokenType::KEYWORD, "static")
            || match(TokenType::KEYWORD, "final") || match(TokenType::KEYWORD, "abstract")) {
            continue;
        }
        if (match(TokenType::KEYWORD, "class")) {
            auto classDecl = parseClassDecl();
            if (classDecl) prog->declarations.push_back(classDecl);
            continue;
        }
        advance();
    }
    return prog;
}

ASTNodePtr Parser_Java::parseClassDecl() {
    Token nameTok = consume(TokenType::IDENTIFIER, "Expected class name");
    auto classFunc = std::make_shared<FunctionNode>();
    classFunc->returnType = "class";
    classFunc->name = nameTok.lexeme;

    consumeLexeme("{", "Expected '{' after class declaration");
    auto body = std::make_shared<BlockNode>();

    while (!check(TokenType::DELIMITER, "}") && !isAtEnd()) {
        // skip modifiers
        while (peek().lexeme == "public" || peek().lexeme == "private" || peek().lexeme == "protected"
               || peek().lexeme == "static" || peek().lexeme == "final") {
            advance();
        }
        if (isTypeKeyword()) {
            std::string typeStr = currentTypeKeyword();
            Token mNameTok = consume(TokenType::IDENTIFIER, "Expected method/field name");
            if (check(TokenType::DELIMITER, "(")) {
                auto method = parseMethodDecl(typeStr, mNameTok.lexeme);
                if (method) body->statements.push_back(method);
            } else {
                auto field = parseVarDecl(typeStr, mNameTok.lexeme);
                if (field) body->statements.push_back(field);
            }
        } else {
            advance();
        }
    }
    consumeLexeme("}", "Expected '}' after class body");
    classFunc->body = body;
    return classFunc;
}

ASTNodePtr Parser_Java::parseMethodDecl(const std::string& retType, const std::string& name) {
    auto func = std::make_shared<FunctionNode>();
    func->returnType = retType;
    func->name = name;

    consumeLexeme("(", "Expected '(' after method name");
    if (!check(TokenType::DELIMITER, ")")) {
        do {
            // Handle "String[] args" - consume modifiers/brackets
            while (peek().lexeme == "final") advance();
            if (isAtEnd() || check(TokenType::DELIMITER, ")")) break;
            std::string pType = advance().lexeme;
            // Handle array type e.g. String[]
            if (match(TokenType::DELIMITER, "[")) {
                pType += "[]";
                consumeLexeme("]", "Expected ']' after '['");
            }
            if (check(TokenType::IDENTIFIER)) {
                Token pName = advance();
                func->parameters.push_back({pType, pName.lexeme});
            }
        } while (match(TokenType::DELIMITER, ","));
    }
    consumeLexeme(")", "Expected ')' after parameter list");

    if (check(TokenType::DELIMITER, "{")) {
        func->body = parseBlock();
    } else {
        consumeLexeme(";", "Expected ';' after method declaration");
    }
    return func;
}

ASTNodePtr Parser_Java::parseVarDecl(const std::string& type, const std::string& name) {
    auto vd = std::make_shared<VarDeclNode>();
    vd->varType = type;
    vd->varName = name;

    // Handle array declaration
    if (match(TokenType::DELIMITER, "[")) {
        vd->varType += "[]";
        consumeLexeme("]", "Expected ']' in array type");
    }

    if (match(TokenType::OPERATOR, "=")) {
        // Handle 'new Scanner(System.in)' or 'new Type(...)'
        if (match(TokenType::KEYWORD, "new")) {
            Token typeName = advance(); // Scanner or other type
            if (check(TokenType::DELIMITER, "(")) {
                consumeLexeme("(", "Expected '(' after new Type");
                // Consume constructor args
                int depth = 1;
                while (!isAtEnd() && depth > 0) {
                    if (check(TokenType::DELIMITER, "(")) depth++;
                    else if (check(TokenType::DELIMITER, ")")) depth--;
                    if (depth > 0) advance();
                }
                consumeLexeme(")", "Expected ')' after constructor args");
                // Create a special call node
                auto call = std::make_shared<CallExprNode>();
                call->funcName = "new_" + typeName.lexeme;
                vd->initExpr = call;
            }
        } else {
            vd->initExpr = parseExpression();
        }
    }
    consumeLexeme(";", "Expected ';' after variable declaration");
    return vd;
}

ASTNodePtr Parser_Java::parseBlock() {
    auto block = std::make_shared<BlockNode>();
    consumeLexeme("{", "Expected '{'");
    while (!check(TokenType::DELIMITER, "}") && !isAtEnd()) {
        // skip modifiers
        while (peek().lexeme == "public" || peek().lexeme == "private"
               || peek().lexeme == "static" || peek().lexeme == "final") {
            advance();
        }
        auto stmt = parseStatement();
        if (stmt) block->statements.push_back(stmt);
    }
    consumeLexeme("}", "Expected '}'");
    return block;
}

ASTNodePtr Parser_Java::parseStatement() {
    if (check(TokenType::DELIMITER, "{")) return parseBlock();

    // System.out.println / System.out.print
    if (check(TokenType::KEYWORD) && (peek().lexeme == "System.out.println" || peek().lexeme == "System.out.print")) {
        return parsePrintStatement();
    }

    if (match(TokenType::KEYWORD, "if")) return parseIfStatement();
    if (match(TokenType::KEYWORD, "switch")) return parseSwitchStatement();
    if (match(TokenType::KEYWORD, "while")) return parseWhileStatement();
    if (match(TokenType::KEYWORD, "do")) return parseDoWhileStatement();
    if (match(TokenType::KEYWORD, "for")) return parseForStatement();
    if (match(TokenType::KEYWORD, "return")) return parseReturnStatement();
    if (match(TokenType::KEYWORD, "break")) {
        consumeLexeme(";", "Expected ';' after break");
        return std::make_shared<BreakNode>();
    }
    if (match(TokenType::KEYWORD, "continue")) {
        consumeLexeme(";", "Expected ';' after continue");
        return std::make_shared<ContinueNode>();
    }

    // Variable declaration
    if (isTypeKeyword()) {
        std::string typeStr = currentTypeKeyword();
        // Handle Scanner sc = new Scanner(System.in)
        if (typeStr == "Scanner" || peek().type == TokenType::IDENTIFIER) {
            if (peek().type == TokenType::IDENTIFIER) {
                Token nameTok = advance();
                return parseVarDecl(typeStr, nameTok.lexeme);
            }
        }
        if (peek().type == TokenType::IDENTIFIER) {
            Token nameTok = advance();
            return parseVarDecl(typeStr, nameTok.lexeme);
        }
    }
    if (check(TokenType::KEYWORD, "Scanner")) {
        advance();
        Token nameTok = consume(TokenType::IDENTIFIER, "Expected scanner variable name");
        return parseScannerDecl();
    }

    // Check if this is a scanner.nextInt() etc. read call
    if (peek().type == TokenType::IDENTIFIER) {
        size_t savedCurrent = current;
        Token idTok = advance();
        if (match(TokenType::OPERATOR, "=")) {
            // Could be a scanner read like: x = sc.nextInt();
            if (peek().type == TokenType::IDENTIFIER) {
                size_t savedC2 = current;
                Token sc = advance();
                if (match(TokenType::DELIMITER, ".")) {
                    std::string method;
                    if (peek().type == TokenType::IDENTIFIER || peek().type == TokenType::KEYWORD) {
                        method = advance().lexeme;
                    }
                    if (method == "nextInt" || method == "nextFloat" || method == "nextDouble"
                        || method == "nextLine" || method == "next") {
                        consumeLexeme("(", "Expected '('");
                        consumeLexeme(")", "Expected ')'");
                        consumeLexeme(";", "Expected ';'");
                        auto in = std::make_shared<InputNode>();
                        in->targetVar = idTok.lexeme;
                        return in;
                    }
                }
                current = savedC2;
            }
            // Regular assignment
            ASTNodePtr val = parseExpression();
            consumeLexeme(";", "Expected ';'");
            auto assign = std::make_shared<AssignNode>();
            assign->varName = idTok.lexeme;
            assign->op = "=";
            assign->expr = val;
            return assign;
        }
        current = savedCurrent;
    }

    return parseExprStatement();
}

ASTNodePtr Parser_Java::parsePrintStatement() {
    bool hasNewline = (peek().lexeme == "System.out.println");
    advance(); // consume System.out.println or System.out.print

    auto out = std::make_shared<OutputNode>();
    out->hasNewline = hasNewline;

    consumeLexeme("(", "Expected '(' after println/print");
    if (!check(TokenType::DELIMITER, ")")) {
        out->args.push_back(parseExpression());
    }
    consumeLexeme(")", "Expected ')' after print args");

    if (hasNewline) {
        auto nl = std::make_shared<LiteralNode>();
        nl->value = "\"\\n\"";
        nl->valueType = "string";
        out->args.push_back(nl);
    }

    consumeLexeme(";", "Expected ';' after println");
    return out;
}

ASTNodePtr Parser_Java::parseScannerDecl() {
    // Already consumed "Scanner name", now handle = new Scanner(...)
    if (match(TokenType::OPERATOR, "=")) {
        if (match(TokenType::KEYWORD, "new")) {
            consume(TokenType::KEYWORD, "Expected Scanner");
            consumeLexeme("(", "Expected '('");
            // Consume System.in or whatever
            while (!check(TokenType::DELIMITER, ")") && !isAtEnd()) advance();
            consumeLexeme(")", "Expected ')'");
        }
    }
    consumeLexeme(";", "Expected ';' after Scanner declaration");
    // Return an empty block - scanner declared for use
    return std::make_shared<BlockNode>();
}

ASTNodePtr Parser_Java::parseScannerRead(const std::string& varName) {
    auto in = std::make_shared<InputNode>();
    in->targetVar = varName;
    return in;
}

ASTNodePtr Parser_Java::parseIfStatement() {
    auto node = std::make_shared<IfNode>();
    consumeLexeme("(", "Expected '(' after 'if'");
    node->condition = parseExpression();
    consumeLexeme(")", "Expected ')' after condition");
    node->thenBranch = parseStatement();
    if (match(TokenType::KEYWORD, "else")) {
        node->elseBranch = parseStatement();
    }
    return node;
}

ASTNodePtr Parser_Java::parseSwitchStatement() {
    auto node = std::make_shared<SwitchNode>();
    consumeLexeme("(", "Expected '(' after 'switch'");
    node->expression = parseExpression();
    consumeLexeme(")", "Expected ')' after switch expression");
    consumeLexeme("{", "Expected '{' for switch body");

    while (!check(TokenType::DELIMITER, "}") && !isAtEnd()) {
        if (match(TokenType::KEYWORD, "case")) {
            SwitchCase sc;
            sc.value = parseExpression();
            consumeLexeme(":", "Expected ':' after case value");
            while (!check(TokenType::KEYWORD, "case") && !check(TokenType::KEYWORD, "default")
                   && !check(TokenType::DELIMITER, "}") && !isAtEnd()) {
                sc.body.push_back(parseStatement());
            }
            node->cases.push_back(sc);
        } else if (match(TokenType::KEYWORD, "default")) {
            consumeLexeme(":", "Expected ':' after default");
            while (!check(TokenType::KEYWORD, "case") && !check(TokenType::DELIMITER, "}") && !isAtEnd()) {
                node->defaultBody.push_back(parseStatement());
            }
        } else {
            advance();
        }
    }
    consumeLexeme("}", "Expected '}' after switch body");
    return node;
}

ASTNodePtr Parser_Java::parseWhileStatement() {
    auto node = std::make_shared<WhileNode>();
    consumeLexeme("(", "Expected '(' after 'while'");
    node->condition = parseExpression();
    consumeLexeme(")", "Expected ')' after while condition");
    node->body = parseStatement();
    return node;
}

ASTNodePtr Parser_Java::parseDoWhileStatement() {
    auto node = std::make_shared<DoWhileNode>();
    node->body = parseStatement();
    consumeLexeme("while", "Expected 'while' after do body");
    consumeLexeme("(", "Expected '(' after while");
    node->condition = parseExpression();
    consumeLexeme(")", "Expected ')'");
    consumeLexeme(";", "Expected ';' after do-while");
    return node;
}

ASTNodePtr Parser_Java::parseForStatement() {
    auto node = std::make_shared<ForNode>();
    consumeLexeme("(", "Expected '(' after 'for'");

    if (!match(TokenType::DELIMITER, ";")) {
        if (isTypeKeyword()) {
            std::string typeStr = currentTypeKeyword();
            Token nameTok = consume(TokenType::IDENTIFIER, "Expected for variable name");
            node->init = parseVarDecl(typeStr, nameTok.lexeme);
        } else {
            node->init = parseExprStatement();
        }
    }
    if (!check(TokenType::DELIMITER, ";")) {
        node->condition = parseExpression();
    }
    consumeLexeme(";", "Expected ';' in for control");
    if (!check(TokenType::DELIMITER, ")")) {
        node->update = parseExpression();
    }
    consumeLexeme(")", "Expected ')' after for control");
    node->body = parseStatement();
    return node;
}

ASTNodePtr Parser_Java::parseReturnStatement() {
    auto node = std::make_shared<ReturnNode>();
    if (!check(TokenType::DELIMITER, ";")) {
        node->expr = parseExpression();
    }
    consumeLexeme(";", "Expected ';' after return");
    return node;
}

ASTNodePtr Parser_Java::parseExprStatement() {
    auto expr = parseExpression();
    consumeLexeme(";", "Expected ';' after expression statement");
    return expr;
}

ASTNodePtr Parser_Java::parseExpression() { return parseAssignment(); }

ASTNodePtr Parser_Java::parseAssignment() {
    ASTNodePtr left = parseLogicalOr();
    if (match(TokenType::OPERATOR, "=") || match(TokenType::OPERATOR, "+=") || match(TokenType::OPERATOR, "-=")) {
        std::string opStr = previous().lexeme;
        ASTNodePtr right = parseAssignment();
        if (left->getType() == ASTNodeType::VAR_EXPR) {
            auto var = std::dynamic_pointer_cast<VarExprNode>(left);
            auto assign = std::make_shared<AssignNode>();
            assign->varName = var->name;
            assign->op = opStr;
            assign->expr = right;
            return assign;
        }
    }
    return left;
}

ASTNodePtr Parser_Java::parseLogicalOr() {
    ASTNodePtr left = parseLogicalAnd();
    while (match(TokenType::OPERATOR, "||")) {
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = "||"; bin->left = left; bin->right = parseLogicalAnd();
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_Java::parseLogicalAnd() {
    ASTNodePtr left = parseEquality();
    while (match(TokenType::OPERATOR, "&&")) {
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = "&&"; bin->left = left; bin->right = parseEquality();
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_Java::parseEquality() {
    ASTNodePtr left = parseRelational();
    while (match(TokenType::OPERATOR, "==") || match(TokenType::OPERATOR, "!=")) {
        std::string op = previous().lexeme;
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = op; bin->left = left; bin->right = parseRelational();
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_Java::parseRelational() {
    ASTNodePtr left = parseAdditive();
    while (match(TokenType::OPERATOR, "<") || match(TokenType::OPERATOR, ">") ||
           match(TokenType::OPERATOR, "<=") || match(TokenType::OPERATOR, ">=")) {
        std::string op = previous().lexeme;
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = op; bin->left = left; bin->right = parseAdditive();
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_Java::parseAdditive() {
    ASTNodePtr left = parseMultiplicative();
    while (match(TokenType::OPERATOR, "+") || match(TokenType::OPERATOR, "-")) {
        std::string op = previous().lexeme;
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = op; bin->left = left; bin->right = parseMultiplicative();
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_Java::parseMultiplicative() {
    ASTNodePtr left = parseUnary();
    while (match(TokenType::OPERATOR, "*") || match(TokenType::OPERATOR, "/") || match(TokenType::OPERATOR, "%")) {
        std::string op = previous().lexeme;
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = op; bin->left = left; bin->right = parseUnary();
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_Java::parseUnary() {
    // Pre-increment / pre-decrement
    if (match(TokenType::OPERATOR, "++") || match(TokenType::OPERATOR, "--")) {
        std::string op = previous().lexeme;
        auto un = std::make_shared<UnaryExprNode>();
        un->op = op; un->operand = parseUnary();
        return un;
    }
    if (match(TokenType::OPERATOR, "!") || match(TokenType::OPERATOR, "-")) {
        std::string op = previous().lexeme;
        auto un = std::make_shared<UnaryExprNode>();
        un->op = op; un->operand = parseUnary();
        return un;
    }
    ASTNodePtr node = parsePrimary();
    // Post-increment / post-decrement
    if (match(TokenType::OPERATOR, "++") || match(TokenType::OPERATOR, "--")) {
        std::string op = "post" + previous().lexeme;
        auto un = std::make_shared<UnaryExprNode>();
        un->op = op; un->operand = node;
        return un;
    }
    return node;
}

ASTNodePtr Parser_Java::parsePrimary() {
    if (match(TokenType::INT_LITERAL)) {
        auto lit = std::make_shared<LiteralNode>(); lit->value = previous().lexeme; lit->valueType = "int"; return lit;
    }
    if (match(TokenType::FLOAT_LITERAL)) {
        auto lit = std::make_shared<LiteralNode>(); lit->value = previous().lexeme; lit->valueType = "float"; return lit;
    }
    if (match(TokenType::STRING_LITERAL)) {
        auto lit = std::make_shared<LiteralNode>(); lit->value = previous().lexeme; lit->valueType = "string"; return lit;
    }
    if (match(TokenType::CHAR_LITERAL)) {
        auto lit = std::make_shared<LiteralNode>(); lit->value = previous().lexeme; lit->valueType = "char"; return lit;
    }
    if (match(TokenType::BOOL_LITERAL)) {
        auto lit = std::make_shared<LiteralNode>(); lit->value = previous().lexeme; lit->valueType = "bool"; return lit;
    }
    if (match(TokenType::KEYWORD, "null")) {
        auto lit = std::make_shared<LiteralNode>(); lit->value = "null"; lit->valueType = "null"; return lit;
    }
    if (match(TokenType::IDENTIFIER)) {
        std::string idName = previous().lexeme;
        // Method call via dot notation e.g. sc.nextInt()
        if (match(TokenType::DELIMITER, ".")) {
            std::string method;
            if (peek().type == TokenType::IDENTIFIER || peek().type == TokenType::KEYWORD) {
                method = advance().lexeme;
            }
            if (match(TokenType::DELIMITER, "(")) {
                auto call = std::make_shared<CallExprNode>();
                call->funcName = idName + "." + method;
                if (!check(TokenType::DELIMITER, ")")) {
                    do { call->args.push_back(parseExpression()); } while (match(TokenType::DELIMITER, ","));
                }
                consumeLexeme(")", "Expected ')' after call args");
                return call;
            }
        }
        if (match(TokenType::DELIMITER, "(")) {
            auto call = std::make_shared<CallExprNode>();
            call->funcName = idName;
            if (!check(TokenType::DELIMITER, ")")) {
                do { call->args.push_back(parseExpression()); } while (match(TokenType::DELIMITER, ","));
            }
            consumeLexeme(")", "Expected ')' after call args");
            return call;
        }
        auto var = std::make_shared<VarExprNode>(); var->name = idName; return var;
    }
    if (match(TokenType::DELIMITER, "(")) {
        auto expr = parseExpression();
        consumeLexeme(")", "Expected ')' after expression");
        return expr;
    }

    Token t = peek();
    DiagnosticEngine::logSyntaxError(filename, t.line, t.column, "Unexpected token in Java primary: " + t.lexeme);
    advance();
    return std::make_shared<LiteralNode>();
}
