#ifndef OBFUSCATOR_PASS_MANAGER_H
#define OBFUSCATOR_PASS_MANAGER_H

#include "Passes.h"
#include "Config.h"
#include "Metrics.h"
#include <memory>
#include <vector>

namespace obfuscator {

// Orchestrates the execution of all obfuscation passes
class PassManager {
public:
    explicit PassManager(const ObfuscationConfig &config);
    
    // Add a pass to the pipeline
    void addPass(std::unique_ptr<ObfuscationPass> pass);
    
    // Run all passes in sequence (module is void* for LLVMModuleRef)
    void runPasses(void *module);
    
    // Get collected metrics
    const MetricsCollector &getMetricsCollector() const { return metricsCollector; }
    MetricsCollector &getMetricsCollector() { return metricsCollector; }
    
private:
    ObfuscationConfig config;
    std::vector<std::unique_ptr<ObfuscationPass>> passes;
    MetricsCollector metricsCollector;
    
    void initializePasses();
};

} // namespace obfuscator

#endif // OBFUSCATOR_PASS_MANAGER_H
