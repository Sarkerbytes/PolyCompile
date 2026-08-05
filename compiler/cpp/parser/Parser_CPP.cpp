#include "Parser_CPP.hpp"
#include "../../common/Utilities/DiagnosticEngine.hpp"

Parser_CPP::Parser_CPP(const std::vector<Token>& tks, const std::string& fname)
    : tokens(tks), filename(fname), current(0) {}

Token Parser_CPP::peek() const {
    if (current >= tokens.size()) return Token(TokenType::END_OF_FILE, "EOF", 0, 0);
    return tokens[current];
}

Token Parser_CPP::previous() const {
    if (current == 0) return Token(TokenType::UNKNOWN, "", 0, 0);
    return tokens[current - 1];
}

bool Parser_CPP::isAtEnd() const { return peek().type == TokenType::END_OF_FILE; }

Token Parser_CPP::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser_CPP::check(TokenType type, const std::string& lexeme) const {
    if (isAtEnd()) return false;
    if (peek().type != type) return false;
    if (!lexeme.empty() && peek().lexeme != lexeme) return false;
    return true;
}

bool Parser_CPP::match(TokenType type, const std::string& lexeme) {
    if (check(type, lexeme)) {
        advance();
        return true;
    }
    return false;
}

Token Parser_CPP::consume(TokenType type, const std::string& msg) {
    if (check(type)) return advance();
    Token t = peek();
    DiagnosticEngine::logSyntaxError(filename, t.line, t.column, msg + " (found '" + t.lexeme + "')");
    return t;
}

Token Parser_CPP::consumeLexeme(const std::string& lexeme, const std::string& msg) {
    if (peek().lexeme == lexeme) return advance();
    Token t = peek();
    DiagnosticEngine::logSyntaxError(filename, t.line, t.column, msg + " (expected '" + lexeme + "', found '" + t.lexeme + "')");
    return t;
}

ASTNodePtr Parser_CPP::parse() { return parseProgram(); }

ASTNodePtr Parser_CPP::parseProgram() {
    auto prog = std::make_shared<ProgramNode>();
    while (!isAtEnd()) {
        if (peek().lexeme.find("#include") == 0) { advance(); continue; }
        if (match(TokenType::KEYWORD, "using")) {
            match(TokenType::KEYWORD, "namespace");
            match(TokenType::KEYWORD, "std");
            consumeLexeme(";", "Expected ';' after using namespace std");
            continue;
        }
        auto decl = parseDeclaration();
        if (decl) prog->declarations.push_back(decl);
        else advance();
    }
    return prog;
}

ASTNodePtr Parser_CPP::parseDeclaration() {
    if (check(TokenType::KEYWORD, "int") || check(TokenType::KEYWORD, "float") ||
        check(TokenType::KEYWORD, "char") || check(TokenType::KEYWORD, "double") ||
        check(TokenType::KEYWORD, "bool") || check(TokenType::KEYWORD, "string") ||
        check(TokenType::KEYWORD, "void")) {
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

ASTNodePtr Parser_CPP::parseFunction(const std::string& retType, const std::string& name) {
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
        consumeLexeme(";", "Expected ';' after function prototype");
    }
    return func;
}

ASTNodePtr Parser_CPP::parseVarDecl(const std::string& type, const std::string& name) {
    auto vd = std::make_shared<VarDeclNode>();
    vd->varType = type;
    vd->varName = name;

    if (match(TokenType::OPERATOR, "=")) {
        vd->initExpr = parseExpression();
    }
    consumeLexeme(";", "Expected ';' after variable declaration");
    return vd;
}

ASTNodePtr Parser_CPP::parseBlock() {
    auto block = std::make_shared<BlockNode>();
    consumeLexeme("{", "Expected '{'");
    while (!check(TokenType::DELIMITER, "}") && !isAtEnd()) {
        auto stmt = parseDeclaration();
        if (stmt) block->statements.push_back(stmt);
    }
    consumeLexeme("}", "Expected '}'");
    return block;
}

ASTNodePtr Parser_CPP::parseStatement() {
    if (check(TokenType::DELIMITER, "{")) return parseBlock();
    if (match(TokenType::KEYWORD, "cout")) return parseCoutStatement();
    if (match(TokenType::KEYWORD, "cin")) return parseCinStatement();
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
    return parseExprStatement();
}

ASTNodePtr Parser_CPP::parseCoutStatement() {
    auto out = std::make_shared<OutputNode>();
    out->hasNewline = false;

    while (match(TokenType::OPERATOR, "<<")) {
        if (match(TokenType::KEYWORD, "endl")) {
            out->hasNewline = true;
            auto nlLit = std::make_shared<LiteralNode>();
            nlLit->value = "\"\\n\"";
            nlLit->valueType = "string";
            out->args.push_back(nlLit);
        } else {
            out->args.push_back(parseExpression());
        }
    }
    consumeLexeme(";", "Expected ';' after cout statement");
    return out;
}

ASTNodePtr Parser_CPP::parseCinStatement() {
    auto block = std::make_shared<BlockNode>();
    while (match(TokenType::OPERATOR, ">>")) {
        Token varTok = consume(TokenType::IDENTIFIER, "Expected variable name after '>>'");
        auto in = std::make_shared<InputNode>();
        in->targetVar = varTok.lexeme;
        block->statements.push_back(in);
    }
    consumeLexeme(";", "Expected ';' after cin statement");
    if (block->statements.size() == 1) {
        return block->statements[0];
    }
    return block;
}

ASTNodePtr Parser_CPP::parseIfStatement() {
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

ASTNodePtr Parser_CPP::parseSwitchStatement() {
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

ASTNodePtr Parser_CPP::parseWhileStatement() {
    auto node = std::make_shared<WhileNode>();
    consumeLexeme("(", "Expected '(' after 'while'");
    node->condition = parseExpression();
    consumeLexeme(")", "Expected ')' after condition");
    node->body = parseStatement();
    return node;
}

ASTNodePtr Parser_CPP::parseDoWhileStatement() {
    auto node = std::make_shared<DoWhileNode>();
    node->body = parseStatement();
    consumeLexeme("while", "Expected 'while' after do body");
    consumeLexeme("(", "Expected '(' after while");
    node->condition = parseExpression();
    consumeLexeme(")", "Expected ')' after condition");
    consumeLexeme(";", "Expected ';' after do-while");
    return node;
}

ASTNodePtr Parser_CPP::parseForStatement() {
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

ASTNodePtr Parser_CPP::parseReturnStatement() {
    auto node = std::make_shared<ReturnNode>();
    if (!check(TokenType::DELIMITER, ";")) {
        node->expr = parseExpression();
    }
    consumeLexeme(";", "Expected ';' after return");
    return node;
}

ASTNodePtr Parser_CPP::parseExprStatement() {
    auto expr = parseExpression();
    consumeLexeme(";", "Expected ';' after expression statement");
    return expr;
}

ASTNodePtr Parser_CPP::parseExpression() { return parseAssignment(); }

ASTNodePtr Parser_CPP::parseAssignment() {
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

ASTNodePtr Parser_CPP::parseLogicalOr() {
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

ASTNodePtr Parser_CPP::parseLogicalAnd() {
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

ASTNodePtr Parser_CPP::parseEquality() {
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

ASTNodePtr Parser_CPP::parseRelational() {
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

ASTNodePtr Parser_CPP::parseAdditive() {
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

ASTNodePtr Parser_CPP::parseMultiplicative() {
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

ASTNodePtr Parser_CPP::parseUnary() {
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

ASTNodePtr Parser_CPP::parsePrimary() {
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
    DiagnosticEngine::logSyntaxError(filename, t.line, t.column, "Unexpected token in primary C++ expression: " + t.lexeme);
    advance();
    return std::make_shared<LiteralNode>();
}
