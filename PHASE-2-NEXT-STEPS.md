# Phase 2: Implementation - Next Steps Guide

**Date**: October 20, 2025 (End of Phase 1)  
**Phase 2 Start**: October 21, 2025  
**Duration**: 2 weeks (until October 30)  
**Target**: First working obfuscation pass (String Encryption)

---

## Overview

Phase 2 focuses on implementing real obfuscation logic. We start with String Encryption as the first pass because:
- ✅ Relatively straightforward compared to Control Flow Flattening
- ✅ Good learning experience with IR manipulation
- ✅ Clear success criteria (strings encrypted and decryptable)
- ✅ Foundation for metrics collection

---

## Week 1 (Oct 21-25): String Encryption Implementation

### Day 1 (Monday, Oct 21): Study & Design

**Morning: Read Reference Material**
- Read `BLUEPRINT-FROM-GEMINI.md` Section 2 (String Encryption algorithm)
- Review `04-TECHNICAL-REQUIREMENTS.md` String Encryption section
- Study LLVM IR string representation

**Tasks**:
1. Create `docs/STRING-ENCRYPTION-DESIGN.md` with:
   - Algorithm pseudocode
   - IR transformation examples
   - Decryption function template
   - Edge cases handling

2. Design data structures:
   ```cpp
   struct EncryptedString {
       std::vector<uint8_t> encryptedData;
       uint32_t key;
       size_t length;
       std::string decryptFunctionName;
   };
   ```

3. Identify test cases:
   - Simple ASCII strings
   - Strings with special characters
   - Empty strings
   - Large strings
   - Strings in loops

**Deliverable**: Design document + test plan

---

### Day 2 (Tuesday, Oct 22): First Implementation

**Goal**: Basic string finding and encryption

**Tasks**:

1. **Extend `StringEncryption.cpp`**:
   ```cpp
   void StringEncryptionPass::encryptStrings(void *module) {
       // TODO:
       // 1. Iterate through module globals
       // 2. Find string constants (GlobalVariable with ConstantDataArray)
       // 3. For each string:
       //    a. Generate random key
       //    b. XOR encrypt the bytes
       //    c. Create encrypted data array
       //    d. Replace in global with encrypted data
   }
   ```

2. **Implement XOR Encryption**:
   ```cpp
   std::vector<uint8_t> xorEncrypt(
       const std::string &input,
       uint32_t key
   ) {
       std::vector<uint8_t> result;
       for (char c : input) {
           result.push_back(static_cast<uint8_t>(c ^ (key & 0xFF)));
           key = (key << 8) | (key >> 24);  // Rotate key
       }
       return result;
   }
   ```

3. **Create Decryption Stub Function**:
   - Function template to inject into IR
   - Takes encrypted buffer and key
   - Returns decrypted string
   - Callable from anywhere in program

4. **Write Unit Test**:
   ```cpp
   TEST(StringEncryption, EncryptDecrypt) {
       auto encrypted = xorEncrypt("Hello", 12345);
       auto decrypted = xorDecrypt(encrypted, 12345);
       EXPECT_EQ(decrypted, "Hello");
   }
   ```

**Deliverable**: Compiling code + passing unit test

---

### Day 3 (Wednesday, Oct 23): IR Integration

**Goal**: Actually modify LLVM IR

**Tasks**:

1. **Learn LLVM-C API** for:
   - Iterating module globals
   - Creating new functions
   - Adding basic blocks and instructions
   - Linking functions

2. **Implement Global String Finding**:
   - Traverse all globals in module
   - Identify string constants
   - Extract string value

3. **Create Decryption Function in IR**:
   ```cpp
   // Pseudo-code:
   // LLVMValueRef decryptFunc = LLVMAddFunction(
   //     module, "decrypt_string",
   //     functionType(i8Ptr, (i8Ptr, i32)));
   // 
   // LLVMBasicBlockRef entry = LLVMAppendBasicBlock(
   //     decryptFunc, "entry");
   // Build function body with XOR decryption
   ```

4. **Test on hello.c**:
   - Compile hello.c to IR
   - Run pass on it
   - Verify IR is valid (use `llvm-dis` on output)
   - Check for any crashes

**Deliverable**: Pass runs without crashing on test file

---

### Day 4 (Thursday, Oct 24): Testing & Debugging

**Goal**: Verify obfuscation works correctly

**Tasks**:

1. **Run Tests**:
   - Encrypt hello.c fixture
   - Verify strings are encrypted
   - Verify program still functions
   - Check metrics collected

2. **Test Edge Cases**:
   - Empty strings
   - Long strings
   - Special characters (\n, \0, etc.)
   - Multiple strings

3. **Metrics Collection**:
   - Count strings encrypted
   - Track size changes
   - Measure performance overhead

4. **Documentation**:
   - Document any issues found
   - Update design if needed
   - Add comments to code

**Deliverable**: All tests passing, metrics working

---

### Day 5 (Friday, Oct 25): Python CLI Wrapper

**Goal**: Command-line interface to run passes

**Tasks**:

1. **Create `src/cli/main.py`**:
   ```python
   import argparse
   import subprocess
   import json
   
   def main():
       parser = argparse.ArgumentParser(
           description='LLVM Obfuscator'
       )
       parser.add_argument(
           'input_file',
           help='Input C source file'
       )
       parser.add_argument(
           '-o', '--output',
           help='Output filename',
           default='obfuscated'
       )
       parser.add_argument(
           '--passes',
           help='Passes to apply',
           default='all'
       )
       
       args = parser.parse_args()
       
       # 1. Compile to IR: clang -S -emit-llvm
       # 2. Run passes: call C++ library
       # 3. Compile binary: clang
       # 4. Generate report: JSON
   
   if __name__ == '__main__':
       main()
   ```

2. **Implement Workflow**:
   - Input: C source file
   - Process: clang → IR → passes → binary
   - Output: Binary + JSON report

3. **Test End-to-End**:
   ```bash
   python main.py examples/hello.c -o obfuscated
   ./obfuscated  # Should work
   ```

**Deliverable**: Working CLI tool that obfuscates a program

---

## Checkpoint: Friday Evening Check

**Questions to Answer**:

✅ Can you list all strings in hello.c IR?  
✅ Can you encrypt them and still decrypt them?  
✅ Does the obfuscated hello program still run?  
✅ Are metrics being collected?  
✅ Does CLI tool work end-to-end?  
✅ Are all tests passing?  

If YES to all → **Phase 2 Week 1 Complete** ✅

---

## Week 2 (Oct 28-30): Polish & Next Pass Setup

### Day 1 (Monday, Oct 28): Code Quality

**Tasks**:
1. Run clang-format on all C++ code
2. Add comprehensive comments
3. Create unit tests for each component
4. Fix any warnings
5. Improve error handling

### Day 2 (Tuesday, Oct 29): Control Flow Flattening Prep

**Tasks**:
1. Read CFF algorithm from BLUEPRINT
2. Design CFG traversal strategy
3. Create CFF design document
4. Plan implementation approach

### Day 3 (Wednesday, Oct 30): Integration Testing

**Tasks**:
1. Test String Encryption on multiple files
2. Verify obfuscation effectiveness
3. Benchmark performance
4. Generate comprehensive report

**Deliverable**: Week 2 complete, ready to move to CFF

---

## Success Criteria

**To consider Phase 2 SUCCESSFUL:**

✅ String Encryption pass compiles without errors  
✅ No crashes on any test file  
✅ Strings are actually encrypted in IR  
✅ Obfuscated programs still execute correctly  
✅ Metrics collected and reported  
✅ CLI tool works end-to-end  
✅ At least 5 passing unit tests  
✅ Documentation complete  
✅ Code formatted and commented  

---

## Resources Needed

### Documentation
- `BLUEPRINT-FROM-GEMINI.md` (Section 2: String Encryption)
- `04-TECHNICAL-REQUIREMENTS.md` (String Encryption details)
- LLVM-C API documentation

### Learning Materials
- LLVM IR tutorial
- XOR encryption basics
- IR transformation patterns

### Tools
- Text editor / IDE (VS Code)
- clang (for IR generation)
- Visual Studio 2022 (for building)
- Python 3.8+ (for CLI)

---

## Git Workflow (Optional)

```bash
# Create feature branch
git checkout -b feature/string-encryption

# Daily commits
git add src/passes/StringEncryption.cpp
git commit -m "Day 1: String finding and XOR encryption"

# End of week
git commit -m "Feature: String Encryption pass complete"
git checkout main
git merge feature/string-encryption
```

---

## Troubleshooting Guide

### Build Fails
- Clean build: `cd build; rm -r *; cmake ..; cmake --build . --config Release`
- Check LLVM installation
- Verify paths in CMakeLists.txt

### Pass Crashes
- Add debug output with `std::cerr`
- Test with simple fixture first (hello.c)
- Check IR validity: `llvm-dis output.ll`

### IR Invalid
- Make sure all IR references are valid
- Check for dangling pointers
- Verify function signatures match

### Tests Fail
- Run test with verbose output
- Check assertion message
- Print intermediate values

---

## Daily Progress Template

Copy this for each day:

```markdown
## October 21, 2025 (Day 1)

### What I Did
- Reviewed algorithm
- Created design document
- Identified test cases

### What Works
- Design is clear
- Test plan solid

### Issues Encountered
- None

### Next Steps
- Start implementation Monday

### Time: 3 hours
```

---

## Weekly Summary Template

```markdown
# Week 1 Summary (Oct 21-25)

### Completed
- [x] String Encryption algorithm understood
- [x] Basic implementation working
- [x] Unit tests passing
- [x] CLI wrapper functional

### In Progress
- [ ] Edge case handling
- [ ] Performance optimization

### Blockers
- None

### Metrics
- 200 lines of new code
- 12 passing tests
- 5 hours work

### Next Week
- Control Flow Flattening pass
- Integration testing
```

---

## Key Contacts & Resources

**If You Get Stuck:**

1. Review BLUEPRINT-FROM-GEMINI.md
2. Check 04-TECHNICAL-REQUIREMENTS.md
3. Look at test fixtures in `tests/fixtures/`
4. Review LLVM tutorials online
5. Check GitHub issues for similar problems

**Documentation Files in Project:**
- `README.md` - Quick start
- `PHASE-1-COMPLETION-REPORT.md` - Current status
- `BLUEPRINT-FROM-GEMINI.md` - Technical bible
- Design documents (to be created)

---

## Estimated Timeline

| Milestone | Date | Likelihood |
|-----------|------|------------|
| String Encryption Working | Oct 25 | 🟢 High |
| CLI Tool Complete | Oct 25 | 🟢 High |
| CFF Started | Oct 28 | 🟢 High |
| 3 Passes Working | Nov 6 | 🟡 Medium |
| Full Pipeline | Nov 13 | 🟡 Medium |
| Demo Ready | Nov 27 | 🟡 Medium |

---

## Next Meeting Points

**Daily**: Review build status  
**Weekly**: Check progress against timeline  
**Bi-weekly**: Assess overall project health  
**Monthly**: Plan next phase  

---

**Start Date**: October 21, 2025  
**Target Completion**: October 30, 2025  
**Phase 2 Goal**: First working obfuscation pass + CLI tool  

🚀 **Ready to begin implementation!**
