#include "Parser_C.hpp"
#include "../../common/Utilities/DiagnosticEngine.hpp"
#include <iostream>

Parser_C::Parser_C(const std::vector<Token>& tks, const std::string& fname)
    : tokens(tks), filename(fname), current(0) {}

Token Parser_C::peek() const {
    if (current >= tokens.size()) return Token(TokenType::END_OF_FILE, "EOF", 0, 0);
    return tokens[current];
}

Token Parser_C::previous() const {
    if (current == 0) return Token(TokenType::UNKNOWN, "", 0, 0);
    return tokens[current - 1];
}

bool Parser_C::isAtEnd() const {
    return peek().type == TokenType::END_OF_FILE;
}

Token Parser_C::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser_C::check(TokenType type, const std::string& lexeme) const {
    if (isAtEnd()) return false;
    if (peek().type != type) return false;
    if (!lexeme.empty() && peek().lexeme != lexeme) return false;
    return true;
}

bool Parser_C::match(TokenType type, const std::string& lexeme) {
    if (check(type, lexeme)) {
        advance();
        return true;
    }
    return false;
}

Token Parser_C::consume(TokenType type, const std::string& msg) {
    if (check(type)) return advance();
    Token t = peek();
    DiagnosticEngine::logSyntaxError(filename, t.line, t.column, msg + " (found '" + t.lexeme + "')");
    return t;
}

Token Parser_C::consumeLexeme(const std::string& lexeme, const std::string& msg) {
    if (peek().lexeme == lexeme) return advance();
    Token t = peek();
    DiagnosticEngine::logSyntaxError(filename, t.line, t.column, msg + " (expected '" + lexeme + "', found '" + t.lexeme + "')");
    return t;
}

ASTNodePtr Parser_C::parse() {
    return parseProgram();
}

ASTNodePtr Parser_C::parseProgram() {
    auto prog = std::make_shared<ProgramNode>();
    while (!isAtEnd()) {
        // Skip preprocessor directives in parse
        if (peek().lexeme.find("#include") == 0) {
            advance();
            continue;
        }
        auto decl = parseDeclaration();
        if (decl) prog->declarations.push_back(decl);
        else advance();
    }
    return prog;
}

ASTNodePtr Parser_C::parseDeclaration() {
    if (check(TokenType::KEYWORD, "int") || check(TokenType::KEYWORD, "float") ||
        check(TokenType::KEYWORD, "char") || check(TokenType::KEYWORD, "double") ||
        check(TokenType::KEYWORD, "bool") || check(TokenType::KEYWORD, "void")) {
        std::string typeStr = advance().lexeme;
        Token nameTok = consume(TokenType::IDENTIFIER, "Expected identifier after type");

        if (check(TokenType::DELIMITER, "(")) {
            return parseFunction(typeStr, nameTok.lexeme);
        } else {
            return parseVarDecl(typeStr, nameTok.lexeme);
        }
    }
    return parseStatement();
}

ASTNodePtr Parser_C::parseFunction(const std::string& retType, const std::string& name) {
    auto func = std::make_shared<FunctionNode>();
    func->returnType = retType;
    func->name = name;

    consumeLexeme("(", "Expected '(' after function name");
    if (!check(TokenType::DELIMITER, ")")) {
        do {
            Token pTypeTok = advance();
            Token pNameTok = consume(TokenType::IDENTIFIER, "Expected parameter name");
            func->parameters.push_back({pTypeTok.lexeme, pNameTok.lexeme});
        } while (match(TokenType::DELIMITER, ","));
    }
    consumeLexeme(")", "Expected ')' after parameter list");

    if (check(TokenType::DELIMITER, "{")) {
        func->body = parseBlock();
    } else {
        consumeLexeme(";", "Expected ';' after function declaration");
    }
    return func;
}

ASTNodePtr Parser_C::parseVarDecl(const std::string& type, const std::string& name) {
    // Parse the first (already-consumed) variable, with optional initializer
    auto firstVd = std::make_shared<VarDeclNode>();
    firstVd->varType = type;
    firstVd->varName = name;
    if (match(TokenType::OPERATOR, "=")) {
        firstVd->initExpr = parseExpression();
    }

    // If no comma follows, simple single-variable declaration
    if (!check(TokenType::DELIMITER, ",")) {
        consumeLexeme(";", "Expected ';' after variable declaration");
        return firstVd;
    }

    // Multiple declarations: int a = 10, b = 5, c;
    auto list = std::make_shared<VarDeclListNode>();
    list->decls.push_back(firstVd);

    while (match(TokenType::DELIMITER, ",")) {
        Token extra = consume(TokenType::IDENTIFIER, "Expected variable name after ','");
        auto vd = std::make_shared<VarDeclNode>();
        vd->varType = type;
        vd->varName = extra.lexeme;
        if (match(TokenType::OPERATOR, "=")) {
            vd->initExpr = parseExpression();
        }
        list->decls.push_back(vd);
    }
    consumeLexeme(";", "Expected ';' after variable declaration");
    return list;
}

ASTNodePtr Parser_C::parseBlock() {
    auto block = std::make_shared<BlockNode>();
    consumeLexeme("{", "Expected '{'");
    while (!check(TokenType::DELIMITER, "}") && !isAtEnd()) {
        auto stmt = parseDeclaration();
        if (stmt) block->statements.push_back(stmt);
    }
    consumeLexeme("}", "Expected '}'");
    return block;
}

ASTNodePtr Parser_C::parseStatement() {
    if (check(TokenType::DELIMITER, "{")) return parseBlock();
    if (match(TokenType::KEYWORD, "if")) return parseIfStatement();
    if (match(TokenType::KEYWORD, "switch")) return parseSwitchStatement();
    if (match(TokenType::KEYWORD, "while")) return parseWhileStatement();
    if (match(TokenType::KEYWORD, "do")) return parseDoWhileStatement();
    if (match(TokenType::KEYWORD, "for")) return parseForStatement();
    if (match(TokenType::KEYWORD, "printf")) return parsePrintfStatement();
    if (match(TokenType::KEYWORD, "scanf")) return parseScanfStatement();
    if (match(TokenType::KEYWORD, "return")) return parseReturnStatement();
    if (match(TokenType::KEYWORD, "break")) {
        consumeLexeme(";", "Expected ';' after break");
        return std::make_shared<BreakNode>();
    }
    if (match(TokenType::KEYWORD, "continue")) {
        consumeLexeme(";", "Expected ';' after continue");
        return std::make_shared<ContinueNode>();
    }
    return parseExprStatement();
}

ASTNodePtr Parser_C::parseIfStatement() {
    auto node = std::make_shared<IfNode>();
    consumeLexeme("(", "Expected '(' after 'if'");
    node->condition = parseExpression();
    consumeLexeme(")", "Expected ')' after if condition");

    node->thenBranch = parseStatement();
    if (match(TokenType::KEYWORD, "else")) {
        node->elseBranch = parseStatement();
    }
    return node;
}

ASTNodePtr Parser_C::parseSwitchStatement() {
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
            while (!check(TokenType::KEYWORD, "case") && !check(TokenType::KEYWORD, "default") && !check(TokenType::DELIMITER, "}") && !isAtEnd()) {
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

ASTNodePtr Parser_C::parseWhileStatement() {
    auto node = std::make_shared<WhileNode>();
    consumeLexeme("(", "Expected '(' after 'while'");
    node->condition = parseExpression();
    consumeLexeme(")", "Expected ')' after while condition");
    node->body = parseStatement();
    return node;
}

ASTNodePtr Parser_C::parseDoWhileStatement() {
    auto node = std::make_shared<DoWhileNode>();
    node->body = parseStatement();
    consumeLexeme("while", "Expected 'while' after do body");
    consumeLexeme("(", "Expected '(' after while");
    node->condition = parseExpression();
    consumeLexeme(")", "Expected ')' after while condition");
    consumeLexeme(";", "Expected ';' after do-while");
    return node;
}

ASTNodePtr Parser_C::parseForStatement() {
    auto node = std::make_shared<ForNode>();
    consumeLexeme("(", "Expected '(' after 'for'");

    if (!match(TokenType::DELIMITER, ";")) {
        node->init = parseDeclaration();
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

ASTNodePtr Parser_C::parsePrintfStatement() {
    auto out = std::make_shared<OutputNode>();
    out->hasNewline = false;
    consumeLexeme("(", "Expected '(' after 'printf'");

    // Format string or arguments
    if (!check(TokenType::DELIMITER, ")")) {
        do {
            auto expr = parseExpression();
            // Check if string contains \n
            if (expr->getType() == ASTNodeType::LITERAL_EXPR) {
                auto lit = std::dynamic_pointer_cast<LiteralNode>(expr);
                if (lit && lit->value.find("\\n") != std::string::npos) {
                    out->hasNewline = true;
                }
            }
            out->args.push_back(expr);
        } while (match(TokenType::DELIMITER, ","));
    }
    consumeLexeme(")", "Expected ')' after printf arguments");
    consumeLexeme(";", "Expected ';' after printf");
    return out;
}

ASTNodePtr Parser_C::parseScanfStatement() {
    auto in = std::make_shared<InputNode>();
    consumeLexeme("(", "Expected '(' after 'scanf'");
    Token fmtTok = consume(TokenType::STRING_LITERAL, "Expected format string for scanf");
    // Parse all comma-separated &var arguments
    while (match(TokenType::DELIMITER, ",")) {
        std::string varName;
        if (match(TokenType::DELIMITER, "&")) {
            Token varTok = consume(TokenType::IDENTIFIER, "Expected variable name after '&'");
            varName = varTok.lexeme;
        } else {
            Token varTok = consume(TokenType::IDENTIFIER, "Expected variable name");
            varName = varTok.lexeme;
        }
        if (in->targetVar.empty()) {
            in->targetVar = varName;  // first var (primary target)
        }
        in->targetVars.push_back(varName);
    }
    consumeLexeme(")", "Expected ')' after scanf arguments");
    consumeLexeme(";", "Expected ';' after scanf");
    return in;
}

ASTNodePtr Parser_C::parseReturnStatement() {
    auto node = std::make_shared<ReturnNode>();
    if (!check(TokenType::DELIMITER, ";")) {
        node->expr = parseExpression();
    }
    consumeLexeme(";", "Expected ';' after return value");
    return node;
}

ASTNodePtr Parser_C::parseExprStatement() {
    auto expr = parseExpression();
    consumeLexeme(";", "Expected ';' after expression statement");
    return expr;
}

ASTNodePtr Parser_C::parseExpression() {
    return parseAssignment();
}

ASTNodePtr Parser_C::parseAssignment() {
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

ASTNodePtr Parser_C::parseLogicalOr() {
    ASTNodePtr left = parseLogicalAnd();
    while (match(TokenType::OPERATOR, "||")) {
        std::string opStr = previous().lexeme;
        ASTNodePtr right = parseLogicalAnd();
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = opStr;
        bin->left = left;
        bin->right = right;
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_C::parseLogicalAnd() {
    ASTNodePtr left = parseEquality();
    while (match(TokenType::OPERATOR, "&&")) {
        std::string opStr = previous().lexeme;
        ASTNodePtr right = parseEquality();
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = opStr;
        bin->left = left;
        bin->right = right;
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_C::parseEquality() {
    ASTNodePtr left = parseRelational();
    while (match(TokenType::OPERATOR, "==") || match(TokenType::OPERATOR, "!=")) {
        std::string opStr = previous().lexeme;
        ASTNodePtr right = parseRelational();
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = opStr;
        bin->left = left;
        bin->right = right;
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_C::parseRelational() {
    ASTNodePtr left = parseAdditive();
    while (match(TokenType::OPERATOR, "<") || match(TokenType::OPERATOR, ">") ||
           match(TokenType::OPERATOR, "<=") || match(TokenType::OPERATOR, ">=")) {
        std::string opStr = previous().lexeme;
        ASTNodePtr right = parseAdditive();
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = opStr;
        bin->left = left;
        bin->right = right;
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_C::parseAdditive() {
    ASTNodePtr left = parseMultiplicative();
    while (match(TokenType::OPERATOR, "+") || match(TokenType::OPERATOR, "-")) {
        std::string opStr = previous().lexeme;
        ASTNodePtr right = parseMultiplicative();
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = opStr;
        bin->left = left;
        bin->right = right;
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_C::parseMultiplicative() {
    ASTNodePtr left = parseUnary();
    while (match(TokenType::OPERATOR, "*") || match(TokenType::OPERATOR, "/") || match(TokenType::OPERATOR, "%")) {
        std::string opStr = previous().lexeme;
        ASTNodePtr right = parseUnary();
        auto bin = std::make_shared<BinaryExprNode>();
        bin->op = opStr;
        bin->left = left;
        bin->right = right;
        left = bin;
    }
    return left;
}

ASTNodePtr Parser_C::parseUnary() {
    // Pre-increment / pre-decrement
    if (match(TokenType::OPERATOR, "++") || match(TokenType::OPERATOR, "--")) {
        std::string opStr = previous().lexeme;
        ASTNodePtr operand = parseUnary();
        auto un = std::make_shared<UnaryExprNode>();
        un->op = opStr;
        un->operand = operand;
        return un;
    }
    if (match(TokenType::OPERATOR, "!") || match(TokenType::OPERATOR, "-")) {
        std::string opStr = previous().lexeme;
        ASTNodePtr operand = parseUnary();
        auto un = std::make_shared<UnaryExprNode>();
        un->op = opStr;
        un->operand = operand;
        return un;
    }
    ASTNodePtr node = parsePrimary();
    // Post-increment / post-decrement
    if (match(TokenType::OPERATOR, "++") || match(TokenType::OPERATOR, "--")) {
        std::string opStr = "post" + previous().lexeme;
        auto un = std::make_shared<UnaryExprNode>();
        un->op = opStr;
        un->operand = node;
        return un;
    }
    return node;
}

ASTNodePtr Parser_C::parsePrimary() {
    if (match(TokenType::INT_LITERAL)) {
        auto lit = std::make_shared<LiteralNode>();
        lit->value = previous().lexeme;
        lit->valueType = "int";
        return lit;
    }
    if (match(TokenType::FLOAT_LITERAL)) {
        auto lit = std::make_shared<LiteralNode>();
        lit->value = previous().lexeme;
        lit->valueType = "float";
        return lit;
    }
    if (match(TokenType::STRING_LITERAL)) {
        auto lit = std::make_shared<LiteralNode>();
        lit->value = previous().lexeme;
        lit->valueType = "string";
        return lit;
    }
    if (match(TokenType::CHAR_LITERAL)) {
        auto lit = std::make_shared<LiteralNode>();
        lit->value = previous().lexeme;
        lit->valueType = "char";
        return lit;
    }
    if (match(TokenType::BOOL_LITERAL)) {
        auto lit = std::make_shared<LiteralNode>();
        lit->value = previous().lexeme;
        lit->valueType = "bool";
        return lit;
    }
    if (match(TokenType::IDENTIFIER)) {
        std::string idName = previous().lexeme;
        if (match(TokenType::DELIMITER, "(")) {
            auto call = std::make_shared<CallExprNode>();
            call->funcName = idName;
            if (!check(TokenType::DELIMITER, ")")) {
                do {
                    call->args.push_back(parseExpression());
                } while (match(TokenType::DELIMITER, ","));
            }
            consumeLexeme(")", "Expected ')' after call arguments");
            return call;
        }
        auto var = std::make_shared<VarExprNode>();
        var->name = idName;
        return var;
    }
    if (match(TokenType::DELIMITER, "(")) {
        auto expr = parseExpression();
        consumeLexeme(")", "Expected ')' after expression");
        return expr;
    }

    Token t = peek();
    DiagnosticEngine::logSyntaxError(filename, t.line, t.column, "Unexpected token in primary expression: " + t.lexeme);
    advance();
    return std::make_shared<LiteralNode>();
}
