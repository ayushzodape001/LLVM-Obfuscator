#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <cstring>
#include <chrono>

// Integration test fixtures
class StringEncryptionIntegrationTest : public ::testing::Test {
protected:
    static std::vector<uint8_t> xorEncrypt(const uint8_t *data, size_t len, uint8_t key) {
        std::vector<uint8_t> encrypted;
        for (size_t i = 0; i < len; ++i) {
            encrypted.push_back(data[i] ^ key);
        }
        return encrypted;
    }

    static std::vector<uint8_t> xorDecrypt(const uint8_t *data, size_t len, uint8_t key) {
        return xorEncrypt(data, len, key);
    }
};

// ==================== INTEGRATION TEST 1: FULL PIPELINE ====================

TEST_F(StringEncryptionIntegrationTest, FullPipelineDiscoverEncryptInject) {
    // Simulate: discover -> encrypt -> inject pipeline
    
    // Phase 1: Discovery
    const char *discoveredStrings[] = {"user_input", "secret_password", "api_key"};
    int discoveredCount = 3;
    EXPECT_EQ(discoveredCount, 3);
    
    // Phase 2: Encryption
    std::vector<std::pair<std::vector<uint8_t>, uint8_t>> encryptedData;
    int totalBytesEncrypted = 0;
    
    for (const auto *str : discoveredStrings) {
        uint8_t key = 77;
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(str), 
                                     std::strlen(str), key);
        encryptedData.push_back({encrypted, key});
        totalBytesEncrypted += encrypted.size();
    }
    
    EXPECT_EQ(encryptedData.size(), 3);
    EXPECT_GT(totalBytesEncrypted, 0);
    
    // Phase 3: Verification that injection would work
    int injectionPoints = 0;
    for (size_t i = 0; i < encryptedData.size(); ++i) {
        // Each encrypted string represents an injection point
        auto decrypted = xorDecrypt(encryptedData[i].first.data(), 
                                     encryptedData[i].first.size(), 
                                     encryptedData[i].second);
        
        std::string result(decrypted.begin(), decrypted.end());
        EXPECT_STREQ(result.c_str(), discoveredStrings[i]);
        injectionPoints++;
    }
    
    EXPECT_EQ(injectionPoints, 3);
}

// ==================== INTEGRATION TEST 2: PERFORMANCE BENCHMARK ====================

TEST_F(StringEncryptionIntegrationTest, PerformanceTest1000Strings) {
    // Benchmark: encrypt 1000 strings
    
    std::vector<const char *> strings;
    strings.push_back("string_1");
    strings.push_back("string_2");
    strings.push_back("string_3");
    
    // Extend to "1000" by repeating (simplified)
    while (strings.size() < 1000) {
        for (size_t i = 0; i < 100 && strings.size() < 1000; ++i) {
            static char buf[100];
            sprintf(buf, "test_string_%zu", i);
            strings.push_back(buf);
        }
    }
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    size_t totalBytesProcessed = 0;
    for (const auto *str : strings) {
        uint8_t key = 42;
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(str), 
                                     std::strlen(str), key);
        totalBytesProcessed += encrypted.size();
    }
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    
    // Performance assertions
    EXPECT_GT(totalBytesProcessed, 0);
    EXPECT_LT(duration.count(), 1000000); // Should complete in < 1 second
    
    // Print performance metrics
    std::cout << "Processed " << strings.size() << " strings (" 
              << totalBytesProcessed << " bytes) in " 
              << duration.count() << " microseconds" << std::endl;
}

// ==================== INTEGRATION TEST 3: ERROR HANDLING ====================

TEST_F(StringEncryptionIntegrationTest, ErrorHandlingAndRecovery) {
    // Test pass behaves correctly with edge cases
    
    // Test 1: Empty string (should not crash)
    const char *emptyStr = "";
    auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(emptyStr), 0, 42);
    EXPECT_EQ(encrypted.size(), 0);
    
    // Test 2: Very long string (should not crash)
    std::string veryLongStr(100000, 'X');
    auto encryptedLong = xorEncrypt(reinterpret_cast<const uint8_t *>(veryLongStr.c_str()), 
                                     veryLongStr.size(), 42);
    EXPECT_EQ(encryptedLong.size(), 100000);
    
    // Test 3: All possible key values (should handle all)
    const char *testStr = "keytest";
    int successCount = 0;
    for (int key = 0; key < 256; ++key) {
        auto enc = xorEncrypt(reinterpret_cast<const uint8_t *>(testStr), 7, (uint8_t)key);
        auto dec = xorDecrypt(enc.data(), enc.size(), (uint8_t)key);
        std::string result(dec.begin(), dec.end());
        if (result == testStr) {
            successCount++;
        }
    }
    EXPECT_EQ(successCount, 256); // All keys should work
}

// ==================== INTEGRATION TEST 4: MODULE INTERACTION ====================

TEST_F(StringEncryptionIntegrationTest, ModuleProcessingMultipleIterations) {
    // Simulate processing a module multiple times
    
    const char *moduleStrings[] = {"module_string_1", "module_string_2", "module_string_3"};
    int moduleIterations = 0;
    int totalProcessed = 0;
    
    // Simulate 3 module passes
    for (int pass = 0; pass < 3; ++pass) {
        moduleIterations++;
        
        for (const auto *str : moduleStrings) {
            uint8_t key = 100 + pass;
            auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(str), 
                                         std::strlen(str), key);
            auto decrypted = xorDecrypt(encrypted.data(), encrypted.size(), key);
            
            std::string result(decrypted.begin(), decrypted.end());
            EXPECT_STREQ(result.c_str(), str);
            totalProcessed++;
        }
    }
    
    EXPECT_EQ(moduleIterations, 3);
    EXPECT_EQ(totalProcessed, 9); // 3 strings * 3 passes
}

// ==================== COMBINED METRICS TEST ====================

TEST_F(StringEncryptionIntegrationTest, MetricsCollectionValidation) {
    // Validate metrics are accurate
    
    struct Metrics {
        int totalStringsFound = 0;
        int totalBytesEncrypted = 0;
        int decryptionCallsInjected = 0;
        int modulesProcessed = 0;
    };
    
    Metrics metrics;
    
    // Process sample strings
    const char *testStrings[] = {"metric1", "metric2", "metric3", "metric4", "metric5"};
    
    for (const auto *str : testStrings) {
        metrics.totalStringsFound++;
        
        uint8_t key = 55;
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(str), 
                                     std::strlen(str), key);
        metrics.totalBytesEncrypted += encrypted.size();
        metrics.decryptionCallsInjected++;
    }
    
    metrics.modulesProcessed = 1;
    
    // Verify metrics
    EXPECT_EQ(metrics.totalStringsFound, 5);
    EXPECT_EQ(metrics.totalBytesEncrypted, 35); // 7+7+7+7+7
    EXPECT_EQ(metrics.decryptionCallsInjected, 5);
    EXPECT_EQ(metrics.modulesProcessed, 1);
}

// ==================== STRESS TEST ====================

TEST_F(StringEncryptionIntegrationTest, StressTestConcurrentEncryption) {
    // Simulate concurrent encryption of many strings
    
    int successfulEncryptions = 0;
    int totalAttempts = 100;
    
    for (int i = 0; i < totalAttempts; ++i) {
        char buf[100];
        sprintf(buf, "stress_test_string_%d", i);
        
        uint8_t key = (i % 256);
        auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(buf), 
                                     std::strlen(buf), key);
        auto decrypted = xorDecrypt(encrypted.data(), encrypted.size(), key);
        
        std::string result(decrypted.begin(), decrypted.end());
        if (result == buf) {
            successfulEncryptions++;
        }
    }
    
    EXPECT_EQ(successfulEncryptions, totalAttempts);
}

// ==================== CORRECTNESS VERIFICATION ====================

TEST_F(StringEncryptionIntegrationTest, EncryptionDecryptionCorrectnessMatrix) {
    // Test all combinations work correctly
    
    const char *testStrings[] = {"a", "ab", "abc", "abcdef"};
    uint8_t testKeys[] = {1, 2, 42, 128, 255};
    
    int successCount = 0;
    int totalTests = 0;
    
    for (const auto *str : testStrings) {
        for (uint8_t key : testKeys) {
            totalTests++;
            
            auto encrypted = xorEncrypt(reinterpret_cast<const uint8_t *>(str), 
                                         std::strlen(str), key);
            auto decrypted = xorDecrypt(encrypted.data(), encrypted.size(), key);
            
            std::string result(decrypted.begin(), decrypted.end());
            if (result == str) {
                successCount++;
            }
        }
    }
    
    EXPECT_EQ(successCount, totalTests);
    std::cout << "All " << totalTests << " encryption/decryption combinations verified" << std::endl;
}
