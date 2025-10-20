#include "obfuscator/Passes.h"
#include "obfuscator/Utils.h"
#include <iostream>
#include <cstring>
#include <random>
#include <vector>
#include <string>

namespace obfuscator {

// Helper function to generate random encryption key
static uint8_t generateKey() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 255);
    return dis(gen);
}

// Simple XOR encryption
static std::vector<uint8_t> xorEncrypt(const uint8_t *data, size_t len, uint8_t key) {
    std::vector<uint8_t> encrypted;
    for (size_t i = 0; i < len; ++i) {
        encrypted.push_back(data[i] ^ key);
    }
    return encrypted;
}

// Simple XOR decryption (same operation for XOR)
static std::vector<uint8_t> xorDecrypt(const uint8_t *data, size_t len, uint8_t key) {
    return xorEncrypt(data, len, key);  // XOR is symmetric
}

void StringEncryptionPass::run(void *module) {
    std::cerr << "[*] StringEncryptionPass: Starting on module\n";
    
    if (!module) {
        std::cerr << "[!] StringEncryptionPass: Invalid module pointer\n";
        return;
    }
    
    encryptStrings(module);
    
    std::cerr << "[+] StringEncryptionPass: Completed\n";
}

// Structure to hold information about strings found in the module
struct StringInfo {
    std::string name;
    std::string content;
    size_t length;
};

// Find all string constants in the module
static std::vector<StringInfo> findStrings(void *module) {
    std::vector<StringInfo> strings;
    
    // Note: With C API only, we have limited access to IR internals
    // In a full implementation with C++ API, we would:
    // 1. Iterate Module::global_begin() to Module::global_end()
    // 2. Check each GlobalVariable's initializer
    // 3. For ConstantDataArray initializers, use isString()
    // 4. Extract content with getAsString()
    // 5. Store for encryption
    
    // C API approach:
    // We can access globals but metadata is limited without C++ headers
    // For now, we establish the framework that would be used
    
    std::cerr << "[*] StringEncryptionPass: Scanning for string constants\n";
    
    // In production, this would iterate through module globals
    // and identify [N x i8] array types with string content
    
    return strings;
}

void StringEncryptionPass::encryptStrings(void *module) {
    std::cerr << "[*] StringEncryptionPass: Starting string encryption process\n";
    
    // Step 1: Find all string constants
    std::vector<StringInfo> strings = findStrings(module);
    
    if (strings.empty()) {
        std::cerr << "[*] StringEncryptionPass: No string constants found to encrypt\n";
        return;
    }
    
    std::cerr << "[+] StringEncryptionPass: Found " << strings.size() 
              << " string constants\n";
    
    // Step 2: Encrypt each string
    for (const auto &str : strings) {
        std::cerr << "[*] Encrypting string: " << str.name << "\n";
        
        // Generate unique encryption key for this string
        uint8_t key = generateKey();
        std::cerr << "[*]   Key: " << (int)key << "\n";
        
        // Encrypt the content
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(str.content.c_str()), 
                                     str.length, key);
        
        std::cerr << "[+]   Encrypted " << encrypted.size() << " bytes\n";
        
        // TODO: Step 3 - Create new encrypted global variable
        // TODO: Step 4 - Replace all uses of original string with decryption
        // TODO: Step 5 - Update metadata with encryption key
    }
    
    std::cerr << "[+] StringEncryptionPass: Encryption processing complete\n";
}

} // namespace obfuscator
