#include "obfuscator/Metrics.h"
#include <fstream>
#include <sstream>
#include <ctime>

namespace obfuscator {

void MetricsCollector::recordMetric(const std::string &key, double value) {
    metrics.passMetrics[key] = value;
}

void MetricsCollector::recordMetric(const std::string &key, int value) {
    metrics.passMetrics[key] = static_cast<double>(value);
}

void MetricsCollector::recordMetric(const std::string &key, const std::string &value) {
    // For string metrics, store as map entry (simplified)
    metrics.passMetrics[key] = 0.0;  // Placeholder
}

void MetricsCollector::addPassMetric(const std::string &passName, double value) {
    if (metrics.passCount.find(passName) == metrics.passCount.end()) {
        metrics.passCount[passName] = 0;
    }
    metrics.passCount[passName]++;
    metrics.passMetrics[passName + "_metric"] = value;
}

void MetricsCollector::saveToJSON(const std::string &outputFile) const {
    std::ofstream file(outputFile);
    file << "{\n";
    file << "  \"metrics\": {\n";
    
    bool first = true;
    for (const auto &metric : metrics.passMetrics) {
        if (!first) file << ",\n";
        file << "    \"" << metric.first << "\": " << metric.second;
        first = false;
    }
    
    file << "\n  }\n";
    file << "}\n";
    file.close();
}

void MetricsCollector::saveToHTML(const std::string &outputFile) const {
    std::ofstream file(outputFile);
    file << "<html>\n<head><title>Obfuscation Metrics</title></head>\n";
    file << "<body>\n<h1>Obfuscation Metrics</h1>\n";
    file << "<table border='1'>\n";
    file << "<tr><th>Metric</th><th>Value</th></tr>\n";
    
    for (const auto &metric : metrics.passMetrics) {
        file << "<tr><td>" << metric.first << "</td><td>" 
             << metric.second << "</td></tr>\n";
    }
    
    file << "</table>\n</body>\n</html>\n";
    file.close();
}

} // namespace obfuscator
