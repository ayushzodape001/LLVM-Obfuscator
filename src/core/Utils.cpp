#include "obfuscator/Utils.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>

namespace obfuscator {
namespace utils {

std::string trim(const std::string &str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        start++;
    }
    
    auto end = str.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));
    
    return std::string(start, end + 1);
}

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string join(const std::vector<std::string> &vec, const std::string &delimiter) {
    std::string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) result += delimiter;
        result += vec[i];
    }
    return result;
}

std::string readFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return "";
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void writeFile(const std::string &filePath, const std::string &content) {
    std::ofstream file(filePath);
    file << content;
    file.close();
}

bool fileExists(const std::string &filePath) {
    std::ifstream file(filePath);
    return file.good();
}

int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

std::string randomString(int length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += alphanum[randomInt(0, sizeof(alphanum) - 2)];
    }
    return result;
}

} // namespace utils
} // namespace obfuscator
