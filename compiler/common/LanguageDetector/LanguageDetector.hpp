#ifndef LANGUAGE_DETECTOR_HPP
#define LANGUAGE_DETECTOR_HPP

#include <string>
#include <algorithm>

enum class Language {
    C,
    CPP,
    JAVA,
    UNKNOWN
};

class LanguageDetector {
public:
    static Language detect(const std::string& filename) {
        size_t dotPos = filename.find_last_of('.');
        if (dotPos == std::string::npos) return Language::UNKNOWN;

        std::string ext = filename.substr(dotPos);
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        if (ext == ".c") return Language::C;
        if (ext == ".cpp" || ext == ".cc" || ext == ".cxx" || ext == ".hpp" || ext == ".h") return Language::CPP;
        if (ext == ".java") return Language::JAVA;

        return Language::UNKNOWN;
    }

    static std::string languageToString(Language lang) {
        switch (lang) {
            case Language::C: return "C";
            case Language::CPP: return "C++";
            case Language::JAVA: return "Java";
            default: return "Unknown";
        }
    }
};

#endif // LANGUAGE_DETECTOR_HPP
