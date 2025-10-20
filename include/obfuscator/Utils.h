#ifndef OBFUSCATOR_UTILS_H
#define OBFUSCATOR_UTILS_H

#include <string>
#include <vector>

namespace obfuscator {
namespace utils {

// String utilities
std::string trim(const std::string &str);
std::vector<std::string> split(const std::string &str, char delimiter);
std::string join(const std::vector<std::string> &vec, const std::string &delimiter);

// File utilities
std::string readFile(const std::string &filePath);
void writeFile(const std::string &filePath, const std::string &content);
bool fileExists(const std::string &filePath);

// Random utilities
int randomInt(int min, int max);
std::string randomString(int length);

} // namespace utils
} // namespace obfuscator

#endif // OBFUSCATOR_UTILS_H
