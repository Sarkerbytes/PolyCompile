#ifndef DIAGNOSTIC_ENGINE_HPP
#define DIAGNOSTIC_ENGINE_HPP

#include <string>
#include <vector>
#include <iostream>

struct DiagnosticError {
    std::string phase;
    std::string filename;
    int line;
    int column;
    std::string message;
};

class DiagnosticEngine {
private:
    static std::vector<DiagnosticError> errors;
    static bool quietMode;

public:
    static void setQuiet(bool quiet) { quietMode = quiet; }

    static void logLexicalError(const std::string& file, int line, int col, const std::string& msg) {
        errors.push_back({"Lexical Error", file, line, col, msg});
        if (!quietMode) {
            std::cerr << "[Lexical Error] " << file << ":" << line << ":" << col << " - " << msg << std::endl;
        }
    }

    static void logSyntaxError(const std::string& file, int line, int col, const std::string& msg) {
        errors.push_back({"Syntax Error", file, line, col, msg});
        if (!quietMode) {
            std::cerr << "[Syntax Error] " << file << ":" << line << ":" << col << " - " << msg << std::endl;
        }
    }

    static void logSemanticError(const std::string& file, int line, int col, const std::string& msg) {
        errors.push_back({"Semantic Error", file, line, col, msg});
        if (!quietMode) {
            std::cerr << "[Semantic Error] " << file << ":" << line << ":" << col << " - " << msg << std::endl;
        }
    }

    static void logRuntimeError(const std::string& msg) {
        errors.push_back({"Runtime Error", "", 0, 0, msg});
        if (!quietMode) {
            std::cerr << "[Runtime Error] " << msg << std::endl;
        }
    }

    static void logGeneralError(const std::string& msg) {
        errors.push_back({"General Error", "", 0, 0, msg});
        if (!quietMode) {
            std::cerr << "[Error] " << msg << std::endl;
        }
    }

    static bool hasErrors() { return !errors.empty(); }
    static const std::vector<DiagnosticError>& getErrors() { return errors; }
    static void clear() { errors.clear(); }
};

#endif // DIAGNOSTIC_ENGINE_HPP
