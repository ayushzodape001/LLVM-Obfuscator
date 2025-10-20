#include "obfuscator/PassManager.h"
#include "obfuscator/Passes.h"
#include "obfuscator/Utils.h"
#include <iostream>

namespace obfuscator {

PassManager::PassManager(const ObfuscationConfig &config) 
    : config(config) {
    initializePasses();
}

void PassManager::initializePasses() {
    if (config.enableStringEncryption) {
        addPass(std::make_unique<StringEncryptionPass>());
    }
    if (config.enableControlFlowFlattening) {
        addPass(std::make_unique<ControlFlowFlatteningPass>());
    }
    if (config.enableInstructionSubstitution) {
        addPass(std::make_unique<InstructionSubstitutionPass>());
    }
    if (config.enableBogusControlFlow) {
        addPass(std::make_unique<BogusControlFlowPass>());
    }
    if (config.enableDeadCodeInsertion) {
        addPass(std::make_unique<DeadCodeInsertionPass>());
    }
    if (config.enableFunctionSplitting) {
        addPass(std::make_unique<FunctionSplittingPass>());
    }
}

void PassManager::addPass(std::unique_ptr<ObfuscationPass> pass) {
    passes.push_back(std::move(pass));
}

void PassManager::runPasses(void *module) {
    if (config.verbose) {
        std::cerr << "[*] Starting obfuscation passes...\n";
        std::cerr << "[*] Number of passes: " << passes.size() << "\n";
    }
    
    for (auto &pass : passes) {
        if (config.verbose) {
            std::cerr << "[*] Running pass: " << pass->getName() << "\n";
        }
        pass->run(module);
        metricsCollector.recordMetric(pass->getName() + "_applied", 1);
    }
    
    if (config.verbose) {
        std::cerr << "[+] All passes completed successfully!\n";
    }
}

} // namespace obfuscator
