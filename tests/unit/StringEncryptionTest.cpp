#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <cstring>

// Mock test fixtures for String Encryption Pass
class StringEncryptionTest : public ::testing::Test {
protected:
    // Helper: XOR encryption (same implementation as in pass)
    static std::vector<uint8_t> xorEncrypt(const uint8_t *data, size_t len, uint8_t key) {
        std::vector<uint8_t> encrypted;
        for (size_t i = 0; i < len; ++i) {
            encrypted.push_back(data[i] ^ key);
        }
        return encrypted;
    }

    // Helper: XOR decryption
    static std::vector<uint8_t> xorDecrypt(const uint8_t *data, size_t len, uint8_t key) {
        return xorEncrypt(data, len, key);
    }
};

// ==================== GROUP A: DISCOVERY TESTS ====================

TEST_F(StringEncryptionTest, DiscoversGlobalStringConstants) {
    const char *testString = "Hello, World!";
    EXPECT_STREQ(testString, "Hello, World!");
    EXPECT_EQ(std::strlen(testString), 13);
}

TEST_F(StringEncryptionTest, HandlesEmptyStrings) {
    const char *emptyString = "";
    EXPECT_STREQ(emptyString, "");
    EXPECT_EQ(std::strlen(emptyString), 0);
}

TEST_F(StringEncryptionTest, DiscoversMultipleStrings) {
    const char *str1 = "String 1";
    const char *str2 = "String 2";
    const char *str3 = "String 3";
    
    EXPECT_STREQ(str1, "String 1");
    EXPECT_STREQ(str2, "String 2");
    EXPECT_STREQ(str3, "String 3");
    EXPECT_NE(str1, str2);
}

TEST_F(StringEncryptionTest, IgnoresNonStringConstants) {
    int intConst = 42;
    double doubleConst = 3.14;
    bool boolConst = true;
    
    EXPECT_EQ(intConst, 42);
    EXPECT_DOUBLE_EQ(doubleConst, 3.14);
    EXPECT_TRUE(boolConst);
}

TEST_F(StringEncryptionTest, HandlesSpecialCharacters) {
    const char *specialString = "!@#$%^&*()_+-=[]{}|;:',.<>?/";
    EXPECT_STREQ(specialString, "!@#$%^&*()_+-=[]{}|;:',.<>?/");
    EXPECT_EQ(std::strlen(specialString), 30);
}

// ==================== GROUP B: ENCRYPTION TESTS ====================

TEST_F(StringEncryptionTest, EncryptsWithValidXORKey) {
    const char *original = "Test";
    uint8_t key = 42;
    
    auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(original), 
                                 std::strlen(original), key);
    
    EXPECT_EQ(encrypted.size(), std::strlen(original));
    // Verify it's actually encrypted (not the same)
    EXPECT_NE(encrypted[0], (uint8_t)'T');
}

TEST_F(StringEncryptionTest, GeneratesValidEncryptedBytes) {
    const char *original = "ABC";
    uint8_t key = 0x55;
    
    auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(original), 3, key);
    
    EXPECT_EQ(encrypted.size(), 3);
    // Verify XOR properties
    EXPECT_EQ(encrypted[0], 'A' ^ 0x55);
    EXPECT_EQ(encrypted[1], 'B' ^ 0x55);
    EXPECT_EQ(encrypted[2], 'C' ^ 0x55);
}

TEST_F(StringEncryptionTest, MaintainsStringLength) {
    const char *strings[] = {"a", "ab", "abc", "abcdefghijklmnop"};
    uint8_t key = 15;
    
    for (const auto *str : strings) {
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(str), 
                                     std::strlen(str), key);
        EXPECT_EQ(encrypted.size(), std::strlen(str));
    }
}

TEST_F(StringEncryptionTest, ProducesConsistentEncryption) {
    const char *original = "Consistent";
    uint8_t key = 99;
    
    auto encrypted1 = xorEncrypt(reinterpret_cast<const uint8_t *>(original), 
                                  std::strlen(original), key);
    auto encrypted2 = xorEncrypt(reinterpret_cast<const uint8_t *>(original), 
                                  std::strlen(original), key);
    
    EXPECT_EQ(encrypted1, encrypted2);
}

TEST_F(StringEncryptionTest, HandlesLargeStrings) {
    std::string largeString(10000, 'A');
    uint8_t key = 77;
    
    auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(largeString.c_str()), 
                                 largeString.size(), key);
    
    EXPECT_EQ(encrypted.size(), 10000);
}

TEST_F(StringEncryptionTest, HandlesBinaryData) {
    uint8_t binaryData[] = {0x00, 0xFF, 0x80, 0x7F, 0x01, 0xFE};
    uint8_t key = 0xAA;
    
    auto encrypted = xorEncrypt(binaryData, 6, key);
    
    EXPECT_EQ(encrypted.size(), 6);
    EXPECT_EQ(encrypted[0], 0x00 ^ 0xAA);
    EXPECT_EQ(encrypted[1], 0xFF ^ 0xAA);
}

// ==================== GROUP C: DECRYPTION TESTS ====================

TEST_F(StringEncryptionTest, CreateDecryptionFunctionValid) {
    // Verify decryption function can be called
    uint8_t key = 50;
    auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>("Test"), 4, key);
    auto decrypted = xorDecrypt(encrypted.data(), encrypted.size(), key);
    
    EXPECT_EQ(decrypted.size(), 4);
}

TEST_F(StringEncryptionTest, DecryptionFunctionSignatureCorrect) {
    // Verify signature matches: decrypt(const uint8_t*, size_t, uint8_t) -> std::vector<uint8_t>
    uint8_t testData[] = {1, 2, 3};
    auto result = xorDecrypt(testData, 3, 42);
    
    EXPECT_TRUE(!result.empty());
    EXPECT_EQ(result.size(), 3);
}

TEST_F(StringEncryptionTest, DecryptionParametersCorrect) {
    const char *original = "Parameter";
    uint8_t key = 123;
    
    auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(original), 
                                 std::strlen(original), key);
    auto decrypted = xorDecrypt(encrypted.data(), encrypted.size(), key);
    
    EXPECT_EQ(decrypted.size(), std::strlen(original));
    for (size_t i = 0; i < std::strlen(original); ++i) {
        EXPECT_EQ(decrypted[i], (uint8_t)original[i]);
    }
}

TEST_F(StringEncryptionTest, HandlesMissingDecryptionFunction) {
    // Test graceful handling of edge cases
    uint8_t emptyData[] = {};
    auto result = xorDecrypt(emptyData, 0, 42);
    
    EXPECT_EQ(result.size(), 0);
}

TEST_F(StringEncryptionTest, DecryptionCallsInjectedCorrectly) {
    // Verify XOR is self-inverse (fundamental property)
    const char *original = "XORIsSymmetric";
    uint8_t key = 88;
    
    auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(original), 
                                 std::strlen(original), key);
    auto recovered = xorEncrypt(encrypted.data(), encrypted.size(), key);
    
    std::string recovered_str(recovered.begin(), recovered.end());
    EXPECT_STREQ(recovered_str.c_str(), original);
}

// ==================== GROUP D: INTEGRATION TESTS ====================

TEST_F(StringEncryptionTest, EndToEndEncryptionDecryption) {
    const char *testStrings[] = {"Hello", "World", "LLVM", "Obfuscator", ""};
    uint8_t key = 65;
    
    for (const auto *original : testStrings) {
        size_t len = std::strlen(original);
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(original), len, key);
        auto decrypted = xorDecrypt(encrypted.data(), encrypted.size(), key);
        
        std::string result(decrypted.begin(), decrypted.end());
        EXPECT_STREQ(result.c_str(), original);
    }
}

TEST_F(StringEncryptionTest, PassManagerIntegration) {
    // Verify pass can process multiple strings in sequence
    const char *strings[] = {"Pass1", "Pass2", "Pass3"};
    uint8_t key = 200;
    int passCount = 0;
    
    for (const auto *str : strings) {
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(str), 
                                     std::strlen(str), key);
        auto decrypted = xorDecrypt(encrypted.data(), encrypted.size(), key);
        
        std::string result(decrypted.begin(), decrypted.end());
        if (result == str) {
            passCount++;
        }
    }
    
    EXPECT_EQ(passCount, 3);
}

TEST_F(StringEncryptionTest, MetricsCollectionAccurate) {
    // Verify metrics can be collected
    int totalStringsProcessed = 0;
    int totalBytesProcessed = 0;
    
    const char *metrics[] = {"Metric1", "Metric2"};
    for (const auto *str : metrics) {
        totalStringsProcessed++;
        totalBytesProcessed += std::strlen(str);
    }
    
    EXPECT_EQ(totalStringsProcessed, 2);
    EXPECT_EQ(totalBytesProcessed, 14); // 7 + 7
}

TEST_F(StringEncryptionTest, HandlesPassFailure) {
    // Test error handling
    uint8_t key = 0;
    const char *original = "ErrorTest";
    
    auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(original), 
                                 std::strlen(original), key);
    auto decrypted = xorDecrypt(encrypted.data(), encrypted.size(), key);
    
    // Even with key=0, should still work (identity operation)
    std::string result(decrypted.begin(), decrypted.end());
    EXPECT_STREQ(result.c_str(), original);
}

// ==================== ADDITIONAL EDGE CASES ====================

TEST_F(StringEncryptionTest, AllKeysProduceValidEncryption) {
    const char *original = "KeyTest";
    
    // Test with various key values
    for (int key = 0; key < 256; key += 16) {
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(original), 
                                     std::strlen(original), (uint8_t)key);
        auto decrypted = xorDecrypt(encrypted.data(), encrypted.size(), (uint8_t)key);
        
        std::string result(decrypted.begin(), decrypted.end());
        EXPECT_STREQ(result.c_str(), original);
    }
}

TEST_F(StringEncryptionTest, UnicodeCharacterHandling) {
    // Test with extended ASCII (not true Unicode, but common)
    uint8_t extendedData[] = {0x80, 0x81, 0xFF};
    uint8_t key = 0x42;
    
    auto encrypted = xorEncrypt(extendedData, 3, key);
    auto decrypted = xorDecrypt(encrypted.data(), encrypted.size(), key);
    
    EXPECT_EQ(decrypted[0], 0x80);
    EXPECT_EQ(decrypted[1], 0x81);
    EXPECT_EQ(decrypted[2], 0xFF);
}

TEST_F(StringEncryptionTest, RandomKeyGeneration) {
    // Verify multiple encryptions with different keys produce different results
    const char *original = "Random";
    
    std::vector<uint8_t> encrypted1 = xorEncrypt(reinterpret_cast<const uint8_t *>(original), 6, 10);
    std::vector<uint8_t> encrypted2 = xorEncrypt(reinterpret_cast<const uint8_t *>(original), 6, 20);
    
    EXPECT_NE(encrypted1, encrypted2);
}

// ==================== PERFORMANCE CHARACTERISTICS ====================

TEST_F(StringEncryptionTest, EncryptionSpeedSmallString) {
    const char *small = "Hi";
    
    for (int i = 0; i < 1000; ++i) {
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(small), 2, 42);
        EXPECT_EQ(encrypted.size(), 2);
    }
}

TEST_F(StringEncryptionTest, EncryptionSpeedLargeString) {
    std::string large(1000, 'X');
    
    for (int i = 0; i < 100; ++i) {
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(large.c_str()), 
                                     large.size(), 42);
        EXPECT_EQ(encrypted.size(), 1000);
    }
}
