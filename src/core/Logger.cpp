#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

namespace obfuscator {
namespace logger {

static std::ofstream logFile;

void initialize(const std::string &filename = "") {
    if (!filename.empty()) {
        logFile.open(filename, std::ios::app);
    }
}

void log(const std::string &message) {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    
    std::cerr << "[" << std::put_time(&tm, "%H:%M:%S") << "] " << message << "\n";
    
    if (logFile.is_open()) {
        logFile << "[" << std::put_time(&tm, "%H:%M:%S") << "] " << message << "\n";
        logFile.flush();
    }
}

void error(const std::string &message) {
    log("ERROR: " + message);
}

void warning(const std::string &message) {
    log("WARN: " + message);
}

void info(const std::string &message) {
    log("INFO: " + message);
}

} // namespace logger
} // namespace obfuscator
