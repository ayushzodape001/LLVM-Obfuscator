#ifndef OBFUSCATOR_CONFIG_H
#define OBFUSCATOR_CONFIG_H

#include <string>
#include <map>
#include <vector>

namespace obfuscator {

// Configuration for obfuscation passes
struct ObfuscationConfig {
    // Pass enablement flags
    bool enableStringEncryption = true;
    bool enableControlFlowFlattening = true;
    bool enableInstructionSubstitution = true;
    bool enableBogusControlFlow = false;
    bool enableDeadCodeInsertion = false;
    bool enableFunctionSplitting = false;

    // Pass parameters
    int stringEncryptionLevel = 1;  // 1-3
    int controlFlowFlatteningLevel = 1;  // 1-3
    int instructionSubstitutionLevel = 1;  // 1-3
    
    // Metrics collection
    bool collectMetrics = true;
    std::string metricsOutputFile;

    // Logging
    bool verbose = false;
    std::string logFile;

    // Input/Output
    std::string inputIRFile;
    std::string outputIRFile;
    std::string outputBinaryFile;
};

// Configuration parser
class ConfigParser {
public:
    static ObfuscationConfig parseJSON(const std::string &jsonFile);
    static ObfuscationConfig parseCommand(int argc, char **argv);
    static void saveJSON(const ObfuscationConfig &config, const std::string &jsonFile);
};

} // namespace obfuscator

#endif // OBFUSCATOR_CONFIG_H
