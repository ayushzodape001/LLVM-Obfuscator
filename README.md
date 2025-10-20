# LLVM Obfuscator

Professional code obfuscation tool built on LLVM 17, implementing string encryption, control flow flattening, and instruction substitution for effective binary protection.

## Features

- **String Encryption** - Compile-time encryption of string literals with automatic decryption injection
- **Control Flow Flattening** - Dispatcher-based control flow transformation to maximize disassembly complexity
- **Instruction Substitution** - Semantic-preserving instruction equivalence using algebraic and bitwise identities
- **Metrics Collection** - Comprehensive obfuscation analysis with JSON/HTML reporting
- **Configurable** - JSON-based configuration for fine-tuned obfuscation control

## Quick Start

### Requirements

- LLVM 17.0.6+
- CMake 3.20+
- C++17 compiler (MSVC 2022, GCC 11+, or Clang 15+)

### Build

```bash
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

### Usage

```bash
# Obfuscate C source to binary
clang-obfuscator input.c -o output.bin

# With specific techniques
clang-obfuscator input.c -o output.bin --string-encryption --cff

# Generate detailed metrics
clang-obfuscator input.c -o output.bin --metrics report.json
```

## Project Structure

```
src/
  ├── passes/          Obfuscation algorithms
  ├── core/           Infrastructure (PassManager, Config, Logger)
  └── analysis/       Analysis utilities
include/obfuscator/   Public API headers
tests/                Unit and integration tests
examples/             Example programs
```

## Build Status

| Module | Status |
|--------|--------|
| Core Infrastructure | ✅ 0 errors, 0 warnings |
| Pass Interfaces | ✅ 6 passes scaffolded |
| Analysis Framework | ✅ Ready |
| Build System | ✅ CMake configured |

## Technologies

- **LLVM 17.0.6** - IR manipulation and pass infrastructure
- **C++17** - Implementation language
- **CMake 3.20+** - Build configuration

## Development

Phase 1 (Setup): ✅ Complete  
Phase 2 (Implementation): In progress

For detailed development information, see `../LOCAL-DOCS/`

## License

MIT

## Contact

Ayush Zodape
