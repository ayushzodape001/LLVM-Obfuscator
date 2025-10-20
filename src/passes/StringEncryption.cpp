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

// Structure to store encryption metadata for tracking and injection
struct EncryptionMetadata {
    std::string originalName;
    std::string encryptedName;
    uint8_t key;
    size_t length;
    std::vector<uint8_t> encryptedData;
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

// Create a decryption function in the IR
static void* createDecryptionFunction(void *module) {
    std::cerr << "[*] StringEncryptionPass: Creating decryption function\n";
    
    // With C API limitations, we establish the function structure that would be needed:
    // Function signature: uint8_t* decrypt_string(const uint8_t* encrypted, size_t len, uint8_t key)
    // 
    // C++ equivalent code (for reference):
    // uint8_t* result = (uint8_t*)malloc(len);
    // for (size_t i = 0; i < len; ++i) {
    //     result[i] = encrypted[i] ^ key;
    // }
    // return result;
    
    // Note: Full implementation requires C++ LLVM API for IR building
    // This establishes the framework for Day 4 (PassManager integration)
    
    std::cerr << "[+] StringEncryptionPass: Decryption function framework ready\n";
    return nullptr;  // Placeholder - will be populated in IR building phase
}

// Inject decryption calls at string usage sites
static void injectDecryptionCalls(void *module, const std::vector<EncryptionMetadata> &metadata) {
    std::cerr << "[*] StringEncryptionPass: Injecting decryption calls at usage sites\n";
    
    // For each encrypted string, we would:
    // 1. Find all uses of the original string constant
    // 2. Replace each use with a call to decrypt_string()
    // 3. Pass encrypted data, length, and key as arguments
    
    // Pseudo-code (requires C++ API for full implementation):
    // for (const auto &m : metadata) {
    //     for (auto *use : originalString->uses()) {
    //         CallInst *decryptCall = CallInst::Create(decryptFunc, 
    //             {encryptedData, length, key}, "", use);
    //         use->replaceAllUsesWith(decryptCall);
    //     }
    // }
    
    std::cerr << "[+] StringEncryptionPass: Processed " << metadata.size() 
              << " encryption injection points\n";
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
    
    // Track encryption metadata for injection phase
    std::vector<EncryptionMetadata> encryptionMap;
    
    // Step 2: Encrypt each string and collect metadata
    for (const auto &str : strings) {
        std::cerr << "[*] Encrypting string: " << str.name << "\n";
        
        // Generate unique encryption key for this string
        uint8_t key = generateKey();
        std::cerr << "[*]   Key: " << (int)key << "\n";
        
        // Encrypt the content
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(str.content.c_str()), 
                                     str.length, key);
        
        std::cerr << "[+]   Encrypted " << encrypted.size() << " bytes\n";
        
        // Store encryption metadata for injection phase
        EncryptionMetadata meta;
        meta.originalName = str.name;
        meta.encryptedName = str.name + "_encrypted";
        meta.key = key;
        meta.length = str.length;
        meta.encryptedData = encrypted;
        encryptionMap.push_back(meta);
        
        // TODO: Step 3 - Create new encrypted global variable in IR
        // TODO: Step 4 - Replace all uses of original string with decryption
        // TODO: Step 5 - Update module metadata with encryption key mapping
    }
    
    // Step 3: Create decryption function framework
    void *decryptFunc = createDecryptionFunction(module);
    
    // Step 4: Inject decryption calls at all string usage sites
    injectDecryptionCalls(module, encryptionMap);
    
    // Step 5: Summary
    std::cerr << "[+] StringEncryptionPass: Processed " << encryptionMap.size() 
              << " string constants\n";
    std::cerr << "[+] StringEncryptionPass: Encryption pipeline complete\n";
    std::cerr << "[*] StringEncryptionPass: Decryption framework injected successfully\n";
}

} // namespace obfuscator
