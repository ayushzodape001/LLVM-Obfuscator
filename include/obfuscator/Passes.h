#ifndef OBFUSCATOR_PASSES_H
#define OBFUSCATOR_PASSES_H

#include <string>
#include <memory>

// Forward declarations (using opaque pointers to avoid LLVM C++ headers)
typedef void LLVMModuleRef;
typedef void LLVMFunctionRef;

namespace obfuscator {

// Forward declarations
class MetricsCollector;
class PassManager;

// Base class for all obfuscation passes
class ObfuscationPass {
public:
    virtual ~ObfuscationPass() = default;
    virtual void run(void *module) = 0;  // void* is LLVMModuleRef
    virtual std::string getName() const = 0;
};

// String Encryption Pass
class StringEncryptionPass : public ObfuscationPass {
public:
    void run(void *module) override;
    std::string getName() const override { return "StringEncryption"; }
private:
    void encryptStrings(void *module);
};

// Control Flow Flattening Pass
class ControlFlowFlatteningPass : public ObfuscationPass {
public:
    void run(void *module) override;
    std::string getName() const override { return "ControlFlowFlattening"; }
private:
    void flattenControlFlow(void *function);
};

// Instruction Substitution Pass
class InstructionSubstitutionPass : public ObfuscationPass {
public:
    void run(void *module) override;
    std::string getName() const override { return "InstructionSubstitution"; }
private:
    void substituteInstructions(void *function);
};

// Bogus Control Flow Pass
class BogusControlFlowPass : public ObfuscationPass {
public:
    void run(void *module) override;
    std::string getName() const override { return "BogusControlFlow"; }
private:
    void insertBogusFlow(void *function);
};

// Dead Code Insertion Pass
class DeadCodeInsertionPass : public ObfuscationPass {
public:
    void run(void *module) override;
    std::string getName() const override { return "DeadCodeInsertion"; }
private:
    void insertDeadCode(void *function);
};

// Function Splitting Pass
class FunctionSplittingPass : public ObfuscationPass {
public:
    void run(void *module) override;
    std::string getName() const override { return "FunctionSplitting"; }
private:
    void splitFunction(void *function);
};

} // namespace obfuscator

#endif // OBFUSCATOR_PASSES_H
