#include "obfuscator/Config.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace obfuscator {

ObfuscationConfig ConfigParser::parseJSON(const std::string &jsonFile) {
    // Simplified JSON parsing - can be improved with proper JSON library
    ObfuscationConfig config;
    
    std::ifstream file(jsonFile);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open config file: " << jsonFile << "\n";
        return config;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("\"enableStringEncryption\"") != std::string::npos) {
            config.enableStringEncryption = line.find("true") != std::string::npos;
        }
        if (line.find("\"enableControlFlowFlattening\"") != std::string::npos) {
            config.enableControlFlowFlattening = line.find("true") != std::string::npos;
        }
        // Add more parsing as needed
    }
    
    file.close();
    return config;
}

ObfuscationConfig ConfigParser::parseCommand(int argc, char **argv) {
    ObfuscationConfig config;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--verbose" || arg == "-v") {
            config.verbose = true;
        } else if (arg == "--input" || arg == "-i") {
            if (i + 1 < argc) {
                config.inputIRFile = argv[++i];
            }
        } else if (arg == "--output" || arg == "-o") {
            if (i + 1 < argc) {
                config.outputIRFile = argv[++i];
            }
        }
        // Add more argument parsing as needed
    }
    
    return config;
}

void ConfigParser::saveJSON(const ObfuscationConfig &config, const std::string &jsonFile) {
    std::ofstream file(jsonFile);
    
    file << "{\n";
    file << "  \"obfuscation\": {\n";
    file << "    \"enableStringEncryption\": " 
         << (config.enableStringEncryption ? "true" : "false") << ",\n";
    file << "    \"enableControlFlowFlattening\": " 
         << (config.enableControlFlowFlattening ? "true" : "false") << ",\n";
    file << "    \"enableInstructionSubstitution\": " 
         << (config.enableInstructionSubstitution ? "true" : "false") << ",\n";
    file << "    \"verbose\": " 
         << (config.verbose ? "true" : "false") << "\n";
    file << "  }\n";
    file << "}\n";
    
    file.close();
}

} // namespace obfuscator
