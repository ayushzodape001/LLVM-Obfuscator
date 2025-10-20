#ifndef OBFUSCATOR_METRICS_H
#define OBFUSCATOR_METRICS_H

#include <string>
#include <map>
#include <vector>
#include <ctime>

namespace obfuscator {

// Metrics collected during obfuscation
struct ObfuscationMetrics {
    // Basic file metrics
    std::string inputFile;
    std::string outputFile;
    
    // Size metrics
    long long originalSize = 0;
    long long obfuscatedSize = 0;
    double sizeIncrease = 0.0;  // percentage
    
    // Instruction metrics
    long long originalInstructions = 0;
    long long obfuscatedInstructions = 0;
    double instructionIncrease = 0.0;
    
    // Complexity metrics
    double originalComplexity = 0.0;
    double obfuscatedComplexity = 0.0;
    double complexityIncrease = 0.0;
    
    // Pass-specific metrics
    std::map<std::string, int> passCount;  // Passes applied and count
    std::map<std::string, double> passMetrics;
    
    // Timing
    std::time_t startTime;
    std::time_t endTime;
    double totalTime = 0.0;  // in seconds
    
    // Report
    std::string reportFile;
};

// Metrics collector
class MetricsCollector {
public:
    MetricsCollector() = default;
    
    void recordMetric(const std::string &key, double value);
    void recordMetric(const std::string &key, int value);
    void recordMetric(const std::string &key, const std::string &value);
    
    void addPassMetric(const std::string &passName, double value);
    
    ObfuscationMetrics getMetrics() const { return metrics; }
    void saveToJSON(const std::string &outputFile) const;
    void saveToHTML(const std::string &outputFile) const;
    
private:
    ObfuscationMetrics metrics;
};

} // namespace obfuscator

#endif // OBFUSCATOR_METRICS_H
