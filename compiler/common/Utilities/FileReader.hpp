#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include "DiagnosticEngine.hpp"

class FileReader {
public:
    static std::string read(const std::string& filepath) {
        std::ifstream file(filepath.c_str());
        if (!file.is_open()) {
            DiagnosticEngine::logGeneralError("Cannot open source file: " + filepath);
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
};

#endif // FILE_READER_HPP
