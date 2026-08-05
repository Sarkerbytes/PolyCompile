/*
 * ============================================================
 *  PolyCompiler - Professional Multi-Language Compiler
 *  Supports: C, C++, and Java subsets
 *  Pipeline: Lexer -> Parser -> Semantic -> IR -> Optimizer -> CodeGen -> Executor
 *  Author: PolyCompile Team
 * ============================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>
#include <iomanip>
#include <queue>

// Common
#include "compiler/common/LanguageDetector/LanguageDetector.hpp"
#include "compiler/common/Utilities/DiagnosticEngine.hpp"
#include "compiler/common/Utilities/FileReader.hpp"
#include "compiler/common/IR/IRGenerator.hpp"
#include "compiler/common/Optimizer/Optimizer.hpp"
#include "compiler/common/CodeGen/CodeGenerator.hpp"
#include "compiler/common/Executor/Executor.hpp"

// C Frontend
#include "compiler/c/frontend/Frontend_C.hpp"

// C++ Frontend
#include "compiler/cpp/frontend/Frontend_CPP.hpp"

// Java Frontend
#include "compiler/java/frontend/Frontend_Java.hpp"

// Output directory
static const std::string OUTPUT_DIR = "output/";

// Forward declarations
bool ensureOutputDir();
void printUsage(const char* progName);
void printTokensToConsole(const std::vector<Token>& tokens);
void printASTTree(ASTNodePtr root, const std::map<std::string,std::string>& identMap);
void printFileToConsole(const std::string& filepath);
void printDebugPhase(int phase, const std::string& phaseName, bool success);
void printFileIndented(const std::string& filepath, int indentSpaces = 2);
void printTACColumnar(const std::vector<TACInstruction>& tac, bool showOrigExpr);

// 
//  MAIN
// 
int main(int argc, char* argv[]) {

    // --- Parse arguments ---
    bool debugMode     = false;
    bool showTokens    = false;
    bool showAST       = false;
    bool showSymTable  = false;
    bool showTAC       = false;
    bool showOptTAC    = false;
    bool showASM       = false;
    std::string sourceFile;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if      (arg == "--debug")        debugMode   = true;
        else if (arg == "--tokens")       showTokens  = true;
        else if (arg == "--ast")          showAST     = true;
        else if (arg == "--symbol-table") showSymTable= true;
        else if (arg == "--tac")          showTAC     = true;
        else if (arg == "--opt")          showOptTAC  = true;
        else if (arg == "--asm")          showASM     = true;
        else if (arg == "--help" || arg == "-h") { printUsage(argv[0]); return 0; }
        else if (arg[0] != '-')           sourceFile  = arg;
    }

    if (sourceFile.empty()) {
        std::cerr << "PolyCompiler Error: No source file specified.\n";
        printUsage(argv[0]);
        return 1;
    }

    // --- Read source file ---
    std::string sourceCode = FileReader::read(sourceFile);
    if (sourceCode.empty() && DiagnosticEngine::hasErrors()) {
        return 1;
    }

    // --- Detect language ---
    Language lang = LanguageDetector::detect(sourceFile);
    if (lang == Language::UNKNOWN) {
        std::cerr << "PolyCompiler Error: Cannot determine language from file extension: " << sourceFile << "\n";
        std::cerr << "  Supported extensions: .c, .cpp, .java\n";
        return 1;
    }

    // Ensure output/ directory exists
    ensureOutputDir();

    std::string tokensPath   = OUTPUT_DIR + "tokens.txt";
    std::string astPath      = OUTPUT_DIR + "ast.txt";
    std::string symTablePath = OUTPUT_DIR + "symbol_table.txt";
    std::string reportPath   = OUTPUT_DIR + "semantic_report.txt";
    std::string tacPath      = OUTPUT_DIR + "tac.txt";
    std::string optTacPath   = OUTPUT_DIR + "optimized_tac.txt";
    std::string asmPath      = OUTPUT_DIR + "target_code.asm";

    //  Run Language Frontend (Silently)

    std::vector<Token> tokens;
    ASTNodePtr astRoot;
    bool frontendOK = true;

    if (lang == Language::C) {
        Frontend_C frontend(sourceCode, sourceFile);

        frontend.runLexer(tokensPath);
        tokens = frontend.getTokens();

        frontend.runParser(astPath);
        astRoot = frontend.getAST();
        if (!astRoot) frontendOK = false;

        if (frontendOK) {
            bool semOK = frontend.runSemantic(symTablePath, reportPath);
            if (!semOK) frontendOK = false;
        }

    } else if (lang == Language::CPP) {
        Frontend_CPP frontend(sourceCode, sourceFile);

        frontend.runLexer(tokensPath);
        tokens = frontend.getTokens();

        frontend.runParser(astPath);
        astRoot = frontend.getAST();
        if (!astRoot) frontendOK = false;

        if (frontendOK) {
            bool semOK = frontend.runSemantic(symTablePath, reportPath);
            if (!semOK) frontendOK = false;
        }

    } else { // Java
        Frontend_Java frontend(sourceCode, sourceFile);

        frontend.runLexer(tokensPath);
        tokens = frontend.getTokens();

        frontend.runParser(astPath);
        astRoot = frontend.getAST();
        if (!astRoot) frontendOK = false;

        if (frontendOK) {
            bool semOK = frontend.runSemantic(symTablePath, reportPath);
            if (!semOK) frontendOK = false;
        }
    }

    if (!frontendOK) {
        std::cerr << "PolyCompiler: Frontend failed. Compilation aborted.\n";
        return 1;
    }

    
    //  Phase 4: IR Generation (TAC)

    IRGenerator irGen;
    std::vector<TACInstruction> tac = irGen.generate(astRoot);
    irGen.saveToFile(tacPath);

    //  Phase 5: Optimization
    
    std::vector<TACInstruction> optimizedTAC = Optimizer::optimize(tac);
    Optimizer::saveToFile(optimizedTAC, optTacPath);

    
    //  Phase 6: Target Code Generation
    
    std::vector<std::string> asmCode = CodeGenerator::generateAssembly(optimizedTAC);
    CodeGenerator::saveToFile(asmCode, asmPath);

    
    //  Print Debug Mode Pipeline
    
    if (debugMode) {
        
        // Build identifier -> id mapping from token stream
        
        std::map<std::string, std::string> identMap;  // name -> id1, id2 ...
        std::vector<std::pair<std::string,std::string>> identOrder; // ordered
        int idCounter = 1;
        for (const auto& tok : tokens) {
            if (tok.type == TokenType::IDENTIFIER) {
                if (identMap.find(tok.lexeme) == identMap.end()) {
                    std::string idName = "id" + std::to_string(idCounter++);
                    identMap[tok.lexeme] = idName;
                    identOrder.push_back({tok.lexeme, idName});
                }
            }
        }

        
        // HEADER
        
        std::cout << "\n";
        std::cout << "  PolyCompiler - Debug Mode\n";
        std::cout << "  Source File : " << sourceFile << "\n";
        std::cout << "  Language    : " << LanguageDetector::languageToString(lang) << "\n";
        std::cout << "\n";

        
        // PHASE 1: Symbol Table   
        
        std::cout << "- Symbol table -\n";
        std::cout << "      Identifiers | No.\n";
        std::cout << "      -----------+-----\n";
        for (const auto& kv : identOrder) {
            std::cout << "      " << std::left << std::setw(12) << kv.first
                      << "| " << kv.second << "\n";
        }
        if (identOrder.empty()) {
            std::cout << "      (no user-defined identifiers)\n";
        }
        std::cout << "\n";

        
        // PHASE 2: Tokenization
        
        std::cout << "- Tokenization -\n";
        std::cout << "      ";
        for (const auto& tok : tokens) {
            if (tok.type == TokenType::END_OF_FILE) continue;
            if (tok.type == TokenType::IDENTIFIER) {
                std::cout << "<" << identMap[tok.lexeme] << ">";
            } else {
                std::cout << "<" << tok.lexeme << ">";
            }
        }
        std::cout << "\n\n";

        
        // PHASE 3: Syntax Analysis : Parse Tree
        
        std::cout << "- Syntax Analysis : Parse Tree -\n\n";
        if (astRoot) {
            printASTTree(astRoot, identMap);
        }
        std::cout << "\n";

        
        // PHASE 4: Intermediate Code Generator
        
        std::cout << "- INTERMEDIATE CODE GENERATOR -\n";
       // std::cout << "            " << std::string(28, '-') << "\n";
        std::cout << "\n";
        std::cout << "- We assign address to every expression in the equation.\n";
        std::cout << "\n";
        printTACColumnar(tac, true);
        std::cout << "\n";

        
        // PHASE 5: Code Optimization
        
        std::cout << "- CODE OPTIMIZATION : -\n";
        //std::cout << " " << std::string(16, '-') << "\n";
        std::cout << "\n";
        std::cout << "- Intermediate code generator splits expression to many parts.\n";
        std::cout << "  Code optimization then reduces unnecessary lines.\n";
        std::cout << "\n";
        printTACColumnar(optimizedTAC, false);
        std::cout << "\n";

        
        // PHASE 6: Target Code Generation
        
        std::cout << "- TARGET CODE GENERATION : -\n";
        std::cout << "\n";
        {
            std::ifstream f(asmPath.c_str());
            std::string line;
            while (std::getline(f, line)) {
                std::cout << "      " << line << "\n";
            }
            f.close();
        }
        std::cout << "\n";
    }

   
    //  Inspection Flags
   
    if (showTokens) {
        std::cout << "\n";
        printFileToConsole(tokensPath);
    }
    if (showAST) {
        std::cout << "\n";
        printFileToConsole(astPath);
    }
    if (showSymTable) {
        std::cout << "\n";
        printFileToConsole(symTablePath);
    }
    if (showTAC) {
        std::cout << "\n";
        printFileToConsole(tacPath);
    }
    if (showOptTAC) {
        std::cout << "\n";
        printFileToConsole(optTacPath);
    }
    if (showASM) {
        std::cout << "\n";
        printFileToConsole(asmPath);
    }

    
    //  Execution  (Normal Mode only)
    
    if (!debugMode) {
        bool execOK = Executor::execute(optimizedTAC);
        return execOK ? 0 : 1;
    }

    return 0;
}


//  Helper Functions


bool ensureOutputDir() {
    // Create output directory using system call (cross-platform fallback)
#ifdef _WIN32
    system("if not exist output mkdir output");
#else
    system("mkdir -p output");
#endif
    return true;
}

void printUsage(const char* progName) {
    std::cout << "\n";
    std::cout << "  PolyCompiler - Multi-Language Educational Compiler\n";
    std::cout << "  Supports: C (.c), C++ (.cpp), Java (.java)\n\n";
    std::cout << "  Usage:\n";
    std::cout << "    " << progName << " [flags] <source_file>\n\n";
    std::cout << "  Flags:\n";
    std::cout << "    (none)           Compile and execute the program\n";
    std::cout << "    --debug          Verbose 6-phase report + execution\n";
    std::cout << "    --tokens         Display token table\n";
    std::cout << "    --ast            Display Abstract Syntax Tree\n";
    std::cout << "    --symbol-table   Display symbol table\n";
    std::cout << "    --tac            Display Three Address Code\n";
    std::cout << "    --opt            Display optimized TAC\n";
    std::cout << "    --asm            Display target assembly code\n";
    std::cout << "    --help, -h       Show this help message\n\n";
    std::cout << "  Examples:\n";
    std::cout << "    " << progName << " examples/hello.c\n";
    std::cout << "    " << progName << " --debug examples/hello.cpp\n";
    std::cout << "    " << progName << " --tokens --ast examples/Hello.java\n";
    std::cout << "    " << progName << " --tac --opt --asm examples/hello.c\n\n";
    std::cout << "  Output files are generated in the 'output/' directory.\n\n";
}

void printDebugPhase(int phase, const std::string& phaseName, bool success) {
    std::cout << "    Phase " << phase << " [" << (success ? "OK" : "FAILED") << "] - " << phaseName << "\n";
}

void printFileToConsole(const std::string& filepath) {
    std::ifstream file(filepath.c_str());
    if (!file.is_open()) {
        std::cout << "[Could not open " << filepath << "]\n";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
    file.close();
}

void printFileIndented(const std::string& filepath, int indentSpaces) {
    std::ifstream file(filepath.c_str());
    if (!file.is_open()) {
        std::cout << std::string(indentSpaces, ' ') << "[No results generated]\n";
        return;
    }
    std::string line;
    std::string indent(indentSpaces, ' ');
    while (std::getline(file, line)) {
        std::cout << indent << line << "\n";
    }
    file.close();
}


//  Graphical Parse Tree Renderer  (used by --debug)


struct TreeNode {
    std::string            label;
    std::vector<TreeNode*> children;
    int width;   // total horizontal span of this subtree
    int col;     // center column of this node's label
    TreeNode() : width(0), col(0) {}
    ~TreeNode() { for (auto* c : children) delete c; }
};

static TreeNode* buildASTTreeNode(ASTNodePtr node,
                                   const std::map<std::string,std::string>& identMap)
{
    if (!node) return nullptr;
    TreeNode* tn = new TreeNode();

    switch (node->getType()) {

        case ASTNodeType::PROGRAM: {
            tn->label = "<Program>";
            auto* pn = dynamic_cast<ProgramNode*>(node.get());
            if (pn)
                for (auto& d : pn->declarations)
                    if (auto* c = buildASTTreeNode(d, identMap)) tn->children.push_back(c);
            break;
        }
        case ASTNodeType::FUNCTION: {
            auto* fn = dynamic_cast<FunctionNode*>(node.get());
            tn->label = fn ? ("<" + fn->name + ">") : "<func>";
            if (fn && fn->body)
                if (auto* c = buildASTTreeNode(fn->body, identMap)) tn->children.push_back(c);
            break;
        }
        case ASTNodeType::BLOCK: {
            auto* bn = dynamic_cast<BlockNode*>(node.get());
            tn->label = "<Block>";
            if (bn)
                for (auto& s : bn->statements)
                    if (auto* c = buildASTTreeNode(s, identMap)) tn->children.push_back(c);
            break;
        }
        case ASTNodeType::VAR_DECL: {
            auto* vdn = dynamic_cast<VarDeclNode*>(node.get());
            if (vdn) {
                auto it = identMap.find(vdn->varName);
                std::string idLabel = (it != identMap.end()) ? it->second : vdn->varName;
                tn->label = "<decl:" + idLabel + ">";
                if (vdn->initExpr)
                    if (auto* c = buildASTTreeNode(vdn->initExpr, identMap)) tn->children.push_back(c);
            } else {
                tn->label = "<decl>";
            }
            break;
        }
        case ASTNodeType::ASSIGN_STMT: {
            auto* an = dynamic_cast<AssignNode*>(node.get());
            if (an) {
                tn->label = "<" + an->op + ">";
                // left operand: the variable being assigned
                TreeNode* varNode = new TreeNode();
                auto it = identMap.find(an->varName);
                varNode->label = "<" + ((it != identMap.end()) ? it->second : an->varName) + ">";
                tn->children.push_back(varNode);
                if (an->expr)
                    if (auto* c = buildASTTreeNode(an->expr, identMap)) tn->children.push_back(c);
            } else {
                tn->label = "<=>";
            }
            break;
        }
        case ASTNodeType::BINARY_EXPR: {
            auto* bn = dynamic_cast<BinaryExprNode*>(node.get());
            tn->label = bn ? ("<" + bn->op + ">") : "<op>";
            if (bn) {
                if (bn->left)  if (auto* c = buildASTTreeNode(bn->left,  identMap)) tn->children.push_back(c);
                if (bn->right) if (auto* c = buildASTTreeNode(bn->right, identMap)) tn->children.push_back(c);
            }
            break;
        }
        case ASTNodeType::UNARY_EXPR: {
            auto* un = dynamic_cast<UnaryExprNode*>(node.get());
            tn->label = un ? ("<" + un->op + ">") : "<unary>";
            if (un && un->operand)
                if (auto* c = buildASTTreeNode(un->operand, identMap)) tn->children.push_back(c);
            break;
        }
        case ASTNodeType::VAR_EXPR: {
            auto* vn = dynamic_cast<VarExprNode*>(node.get());
            if (vn) {
                auto it = identMap.find(vn->name);
                tn->label = "<" + ((it != identMap.end()) ? it->second : vn->name) + ">";
            } else {
                tn->label = "<var>";
            }
            break;
        }
        case ASTNodeType::LITERAL_EXPR: {
            auto* ln = dynamic_cast<LiteralNode*>(node.get());
            tn->label = ln ? ("<" + ln->value + ">") : "<lit>";
            break;
        }
        case ASTNodeType::CALL_EXPR: {
            auto* cn = dynamic_cast<CallExprNode*>(node.get());
            tn->label = cn ? ("<" + cn->funcName + ">") : "<call>";
            if (cn)
                for (auto& a : cn->args)
                    if (auto* c = buildASTTreeNode(a, identMap)) tn->children.push_back(c);
            break;
        }
        case ASTNodeType::OUTPUT_STMT: {
            tn->label = "<printf>";
            auto* on = dynamic_cast<OutputNode*>(node.get());
            if (on)
                for (auto& a : on->args)
                    if (auto* c = buildASTTreeNode(a, identMap)) tn->children.push_back(c);
            break;
        }
        case ASTNodeType::INPUT_STMT: {
            tn->label = "<scanf>";
            auto* in2 = dynamic_cast<InputNode*>(node.get());
            if (in2) {
                TreeNode* varNode = new TreeNode();
                auto it = identMap.find(in2->targetVar);
                varNode->label = "<" + ((it != identMap.end()) ? it->second : in2->targetVar) + ">";
                tn->children.push_back(varNode);
            }
            break;
        }
        case ASTNodeType::IF_STMT: {
            tn->label = "<if>";
            auto* ifn = dynamic_cast<IfNode*>(node.get());
            if (ifn) {
                if (ifn->condition)  if (auto* c = buildASTTreeNode(ifn->condition,  identMap)) tn->children.push_back(c);
                if (ifn->thenBranch) if (auto* c = buildASTTreeNode(ifn->thenBranch, identMap)) tn->children.push_back(c);
                if (ifn->elseBranch) if (auto* c = buildASTTreeNode(ifn->elseBranch, identMap)) tn->children.push_back(c);
            }
            break;
        }
        case ASTNodeType::WHILE_STMT: {
            tn->label = "<while>";
            auto* wn = dynamic_cast<WhileNode*>(node.get());
            if (wn) {
                if (wn->condition) if (auto* c = buildASTTreeNode(wn->condition, identMap)) tn->children.push_back(c);
                if (wn->body)      if (auto* c = buildASTTreeNode(wn->body,      identMap)) tn->children.push_back(c);
            }
            break;
        }
        case ASTNodeType::DO_WHILE_STMT: {
            tn->label = "<do-while>";
            auto* dwn = dynamic_cast<DoWhileNode*>(node.get());
            if (dwn) {
                if (dwn->body)      if (auto* c = buildASTTreeNode(dwn->body,      identMap)) tn->children.push_back(c);
                if (dwn->condition) if (auto* c = buildASTTreeNode(dwn->condition, identMap)) tn->children.push_back(c);
            }
            break;
        }
        case ASTNodeType::FOR_STMT: {
            tn->label = "<for>";
            auto* forn = dynamic_cast<ForNode*>(node.get());
            if (forn) {
                if (forn->init)      if (auto* c = buildASTTreeNode(forn->init,      identMap)) tn->children.push_back(c);
                if (forn->condition) if (auto* c = buildASTTreeNode(forn->condition, identMap)) tn->children.push_back(c);
                if (forn->update)    if (auto* c = buildASTTreeNode(forn->update,    identMap)) tn->children.push_back(c);
                if (forn->body)      if (auto* c = buildASTTreeNode(forn->body,      identMap)) tn->children.push_back(c);
            }
            break;
        }
        case ASTNodeType::RETURN_STMT: {
            tn->label = "<return>";
            auto* rn = dynamic_cast<ReturnNode*>(node.get());
            if (rn && rn->expr)
                if (auto* c = buildASTTreeNode(rn->expr, identMap)) tn->children.push_back(c);
            break;
        }
        case ASTNodeType::SWITCH_STMT: {
            tn->label = "<switch>";
            auto* sn = dynamic_cast<SwitchNode*>(node.get());
            if (sn && sn->expression)
                if (auto* c = buildASTTreeNode(sn->expression, identMap)) tn->children.push_back(c);
            break;
        }
        case ASTNodeType::BREAK_STMT:    tn->label = "<break>";    break;
        case ASTNodeType::CONTINUE_STMT: tn->label = "<continue>"; break;
        default:                          tn->label = "<node>";     break;
    }
    return tn;
}

// Assigns col (center column) and width to every node.
// Returns the rightmost column consumed.
static int layoutASTTree(TreeNode* node, int startCol, int gap = 2)
{
    int labelW = (int)node->label.size();

    if (node->children.empty()) {
        node->width = std::max(labelW, 3);
        node->col   = startCol + node->width / 2;
        return startCol + node->width;
    }

    // Layout children left-to-right with a gap between siblings
    int cursor = startCol;
    for (size_t i = 0; i < node->children.size(); ++i) {
        cursor = layoutASTTree(node->children[i], cursor, gap);
        if (i + 1 < node->children.size()) cursor += gap;
    }

    int subtreeW = cursor - startCol;
    node->width  = std::max(labelW, subtreeW);

    // Center parent label over the span of its children
    int firstCol = node->children.front()->col;
    int lastCol  = node->children.back()->col;
    node->col    = (firstCol + lastCol) / 2;

    return startCol + node->width;
}

// BFS level-by-level renderer: prints labels then connector row.
static void renderASTTree(TreeNode* root)
{
    if (!root) return;

    std::vector<std::vector<TreeNode*>> levels;
    std::queue<TreeNode*> bfsQ;
    bfsQ.push(root);
    while (!bfsQ.empty()) {
        int sz = (int)bfsQ.size();
        std::vector<TreeNode*> level;
        for (int i = 0; i < sz; ++i) {
            TreeNode* n = bfsQ.front(); bfsQ.pop();
            level.push_back(n);
            for (auto* child : n->children) bfsQ.push(child);
        }
        levels.push_back(level);
    }

    const std::string rowIndent = "      ";

    for (size_t lvl = 0; lvl < levels.size(); ++lvl) {
        const auto& level = levels[lvl];

        // Compute row width
        int rowWidth = 0;
        for (auto* n : level)
            rowWidth = std::max(rowWidth, n->col + (int)n->label.size() / 2 + 4);

        // --- Label row ---
        std::string labelRow(rowWidth, ' ');
        for (auto* n : level) {
            int startPos = n->col - (int)n->label.size() / 2;
            if (startPos < 0) startPos = 0;
            for (int i = 0; i < (int)n->label.size(); ++i) {
                int pos = startPos + i;
                if (pos < (int)labelRow.size())
                    labelRow[pos] = n->label[i];
            }
        }
        std::cout << rowIndent << labelRow << "\n";

        // --- Connector row (only between levels) ---
        if (lvl + 1 < levels.size()) {
            std::string connRow(rowWidth, ' ');
            for (auto* n : level) {
                for (auto* child : n->children) {
                    if (child->col < n->col) {
                        // child is to the LEFT  → draw '/'
                        int pos = (child->col + n->col) / 2;
                        if (pos >= 0 && pos < (int)connRow.size()) connRow[pos] = '/';
                    } else if (child->col > n->col) {
                        // child is to the RIGHT → draw '\'
                        int pos = (child->col + n->col + 1) / 2;
                        if (pos >= 0 && pos < (int)connRow.size()) connRow[pos] = '\\';
                    } else {
                        // child is directly below → draw '|'
                        if (n->col < (int)connRow.size()) connRow[n->col] = '|';
                    }
                }
            }
            std::cout << rowIndent << connRow << "\n";
        }
    }
}

void printASTTree(ASTNodePtr root, const std::map<std::string,std::string>& identMap)
{
    TreeNode* tree = buildASTTreeNode(root, identMap);
    if (!tree) return;
    layoutASTTree(tree, 0, 2);
    renderASTTree(tree);
    delete tree;
}


//  TAC Columnar Display  (used by --debug, phases 4 & 5)


// Returns true if the name looks like a compiler-generated temp (t0, t1, ...)
static bool isTempVar(const std::string& s) {
    if (s.size() < 2 || s[0] != 't') return false;
    for (size_t i = 1; i < s.size(); ++i)
        if (!std::isdigit((unsigned char)s[i])) return false;
    return true;
}

// Returns the infix operator symbol for a binary TAC op
static std::string tacOpSym(TACOp op) {
    switch (op) {
        case TACOp::ADD:         return "+";
        case TACOp::SUB:         return "-";
        case TACOp::MUL:         return "*";
        case TACOp::DIV:         return "/";
        case TACOp::MOD:         return "%";
        case TACOp::CMP_EQ:      return "==";
        case TACOp::CMP_NE:      return "!=";
        case TACOp::CMP_LT:      return "<";
        case TACOp::CMP_GT:      return ">";
        case TACOp::CMP_LE:      return "<=";
        case TACOp::CMP_GE:      return ">=";
        case TACOp::LOGICAL_AND: return "&&";
        case TACOp::LOGICAL_OR:  return "||";
        default:                 return "op";
    }
}

// Determines if an op is binary (takes two operands)
static bool isBinaryOp(TACOp op) {
    return op == TACOp::ADD || op == TACOp::SUB || op == TACOp::MUL ||
           op == TACOp::DIV || op == TACOp::MOD || op == TACOp::CMP_EQ ||
           op == TACOp::CMP_NE || op == TACOp::CMP_LT || op == TACOp::CMP_GT ||
           op == TACOp::CMP_LE || op == TACOp::CMP_GE ||
           op == TACOp::LOGICAL_AND || op == TACOp::LOGICAL_OR;
}

// Reconstruct the human-readable original expression from a group of TAC
// instructions by substituting temporary variables back into their definitions.
static std::string reconstructOrigExpr(const std::vector<TACInstruction>& group)
{
    // tempExpr[name] = the expression string that computed that temp
    std::map<std::string, std::string> tempExpr;

    for (const auto& ins : group) {
        if (!isTempVar(ins.result)) continue;  // skip final assignment here

        std::string exprStr;
        if (ins.op == TACOp::ASSIGN) {
            // Propagate: resolve the rhs
            exprStr = tempExpr.count(ins.arg1) ? tempExpr[ins.arg1] : ins.arg1;
        } else if (ins.op == TACOp::LOGICAL_NOT) {
            std::string operand = tempExpr.count(ins.arg1) ? tempExpr[ins.arg1] : ins.arg1;
            exprStr = "!" + operand;
        } else if (isBinaryOp(ins.op)) {
            std::string L = tempExpr.count(ins.arg1) ? tempExpr[ins.arg1] : ins.arg1;
            std::string R = tempExpr.count(ins.arg2) ? tempExpr[ins.arg2] : ins.arg2;
            // Add parens around sub-expressions that contain lower-priority ops
            bool needPL = (L.find('+') != std::string::npos || L.find('-') != std::string::npos);
            bool needPR = (R.find('+') != std::string::npos || R.find('-') != std::string::npos);
            if ((ins.op == TACOp::MUL || ins.op == TACOp::DIV) && needPL) L = "(" + L + ")";
            if ((ins.op == TACOp::MUL || ins.op == TACOp::DIV ||
                 ins.op == TACOp::SUB) && needPR)                         R = "(" + R + ")";
            exprStr = L + " " + tacOpSym(ins.op) + " " + R;
        } else {
            exprStr = ins.toString();
        }
        tempExpr[ins.result] = exprStr;
    }

    if (group.empty()) return "";
    const auto& last = group.back();

    // Build lhs = rhs string
    std::string lhs  = last.result;
    std::string rhs;
    if (last.op == TACOp::ASSIGN) {
        rhs = tempExpr.count(last.arg1) ? tempExpr[last.arg1] : last.arg1;
    } else if (isBinaryOp(last.op)) {
        std::string L = tempExpr.count(last.arg1) ? tempExpr[last.arg1] : last.arg1;
        std::string R = tempExpr.count(last.arg2) ? tempExpr[last.arg2] : last.arg2;
        rhs = L + " " + tacOpSym(last.op) + " " + R;
    } else {
        return last.toString();
    }
    return lhs + " = " + rhs;
}

// A logical group of TAC instructions forming one statement/expression
struct TACGroup {
    bool        isLabel;   // e.g. "main:"
    bool        isSpecial; // RETURN, PRINT, READ, GOTO, etc.
    std::string header;    // reconstructed original expression (or label / special line)
    std::vector<std::string> lines; // formatted TAC instruction strings
};

// Split a flat TAC vector into logical groups for display
static std::vector<TACGroup> groupTAC(const std::vector<TACInstruction>& tac)
{
    std::vector<TACGroup> groups;
    std::vector<TACInstruction> current; // accumulates temp + final instructions

    auto flushCurrent = [&]() {
        if (current.empty()) return;
        TACGroup g;
        g.isLabel   = false;
        g.isSpecial = false;
        g.header    = reconstructOrigExpr(current);
        for (const auto& ins : current)
            g.lines.push_back(ins.toString());
        groups.push_back(g);
        current.clear();
    };

    for (const auto& ins : tac) {
        switch (ins.op) {
            case TACOp::LABEL: {
                flushCurrent();
                TACGroup g;
                g.isLabel   = true;
                g.isSpecial = false;
                g.header    = ins.result + ":";
                groups.push_back(g);
                break;
            }
            case TACOp::RETURN:
            case TACOp::PRINT:
            case TACOp::READ:
            case TACOp::GOTO:
            case TACOp::IF_FALSE_GOTO:
            case TACOp::IF_TRUE_GOTO:
            case TACOp::CALL:
            case TACOp::PARAM: {
                flushCurrent();
                // Deduplicate consecutive identical RETURN instructions
                std::string line = ins.toString();
                if (!groups.empty() && groups.back().isSpecial &&
                    !groups.back().lines.empty() &&
                    groups.back().lines[0] == line &&
                    ins.op == TACOp::RETURN)
                    break;
                TACGroup g;
                g.isLabel   = false;
                g.isSpecial = true;
                g.lines.push_back(line);
                groups.push_back(g);
                break;
            }
            default: {
                // Silently skip internal param-binding assignments (not educational)
                if (ins.op == TACOp::ASSIGN &&
                    ins.arg1.find("__param_") != std::string::npos)
                    break;
                current.push_back(ins);
                // End of expression group: result is a real (non-temp) variable
                if (!ins.result.empty() && !isTempVar(ins.result)) {
                    flushCurrent();
                }
                break;
            }
        }
    }
    flushCurrent();
    return groups;
}

// Print TAC groups in a 2-column side-by-side layout, matching the image.
// showOrigExpr = true  -> show reconstructed original expression as a group header
// showOrigExpr = false -> just show the TAC lines (for the optimized phase)
void printTACColumnar(const std::vector<TACInstruction>& tac, bool showOrigExpr)
{
    const std::string base    = "      ";  // 6-space left margin
    const int         colW    = 38;        // width per column (chars)
    const int         numCols = 2;         // expression groups per row

    std::vector<TACGroup> groups = groupTAC(tac);

    // Expression groups are batched and displayed numCols at a time.
    // Special groups (RETURN, PRINT, ...) always print solo.
    // Label groups print as section headers spanning the full width.

    std::vector<TACGroup*> exprGroups;

    auto flushExprGroups = [&]() {
        if (exprGroups.empty()) return;

        for (size_t i = 0; i < exprGroups.size(); i += (size_t)numCols) {

            // Build the column slice for this row
            std::vector<TACGroup*> row;
            for (int c = 0; c < numCols && i + (size_t)c < exprGroups.size(); ++c)
                row.push_back(exprGroups[i + c]);

            // -- Header row (original expression, no underline per image) --
            if (showOrigExpr) {
                std::string hdrLine = base;
                for (auto* g : row) {
                    std::string h = g->header;
                    if ((int)h.size() > colW - 2) h = h.substr(0, colW - 5) + "...";
                    hdrLine += h;
                    if ((int)h.size() < colW)
                        hdrLine += std::string(colW - (int)h.size(), ' ');
                }
                // Trim trailing whitespace from header
                size_t hLast = hdrLine.find_last_not_of(' ');
                if (hLast != std::string::npos) hdrLine = hdrLine.substr(0, hLast + 1);
                std::cout << hdrLine << "\n";
                std::cout << "\n";  // blank line between header and TAC steps
            }

            // -- TAC instruction lines ------------------------------------
            size_t maxLines = 0;
            for (auto* g : row) maxLines = std::max(maxLines, g->lines.size());

            for (size_t ln = 0; ln < maxLines; ++ln) {
                std::string outLine = base;
                for (auto* g : row) {
                    std::string cell = (ln < g->lines.size()) ? g->lines[ln] : "";
                    outLine += cell;
                    if ((int)cell.size() < colW)
                        outLine += std::string(colW - (int)cell.size(), ' ');
                }
                // Trim trailing whitespace
                size_t last = outLine.find_last_not_of(' ');
                if (last != std::string::npos) outLine = outLine.substr(0, last + 1);
                std::cout << outLine << "\n";
            }
            std::cout << "\n";
        }
        exprGroups.clear();
    };

    for (auto& g : groups) {
        if (g.isLabel) {
            flushExprGroups();
            std::cout << base << g.header << "\n";
        } else if (g.isSpecial) {
            // Specials break the column rhythm and print on their own line (no extra blank)
            flushExprGroups();
            for (const auto& ln : g.lines)
                std::cout << base << ln << "\n";
        } else {
            exprGroups.push_back(&g);
        }
    }
    flushExprGroups();
}
