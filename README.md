# LLVM Obfuscator

A comprehensive LLVM-based code obfuscation tool implementing multiple obfuscation techniques to increase code complexity and hinder reverse engineering.

## Features

- **String Encryption**: Encrypt string constants in the binary
- **Control Flow Flattening**: Flatten control flow structures
- **Instruction Substitution**: Replace instructions with equivalent but obfuscated forms
- **Bogus Control Flow**: Insert unreachable code with dead branches
- **Dead Code Insertion**: Add dead code to increase complexity
- **Function Splitting**: Split functions into smaller parts

## Quick Start

### Prerequisites

- **LLVM 17.0.6** (or compatible version) - for IR manipulation
- **CMake 3.20+** (we installed 4.2.0) - for building
- **C++17 compatible compiler**
  - Windows: Visual Studio 2022 or MinGW
  - Linux: GCC 7+ or Clang 5+

### Installation

1. **Build the project**:
   ```bash
   cd LLVM-Obfuscator
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```

2. **Output**:
   - Library: `build/lib/ObfuscatorPasses.dll` (Windows) or `.so` (Linux)
   - Core: `build/lib/ObfuscatorCore.lib`

### Usage

Compile a C program to LLVM IR:
```bash
clang -S -emit-llvm -O0 example.c -o example.ll
```

Run obfuscation passes on IR (coming in next implementation phase):
```bash
# CLI tool coming soon
python src/cli/main.py --input example.ll --output obfuscated.ll
```

## Project Structure

```
LLVM-Obfuscator/
├── src/
│   ├── passes/           # Obfuscation pass implementations
│   ├── core/             # Infrastructure (PassManager, Config, Metrics)
│   ├── analysis/         # Analysis utilities
│   └── cli/              # Command-line interface (Python)
├── include/obfuscator/   # Header files
├── tests/                # Test files and fixtures
├── examples/             # Usage examples
├── configs/              # Configuration presets
├── CMakeLists.txt        # Build configuration
└── build/                # Build output directory
```

## Development

### Current Status

✅ **Phase 1 Complete:**
- LLVM 17.0.6 installed
- CMake 4.2.0 installed
- Project structure created
- Headers and stub implementations ready

⏳ **Phase 2 (This Week):**
- Implement core obfuscation passes
- Build and test each pass
- Create CLI tool
- Develop testing framework

### Building

From the project root:
```powershell
# Windows (PowerShell)
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

### Testing

(Tests to be implemented in Phase 2)

## Technical Details

### LLVM Pass Architecture

Each obfuscation technique is implemented as a separate pass:
- Inherits from `ObfuscationPass` base class
- Implements `run(llvm::Module &M)` method
- Manipulates LLVM Intermediate Representation (IR)

### Configuration

Configuration can be provided via:
- JSON configuration files: `configs/*.json`
- Command-line arguments
- Programmatic API

Example config:
```json
{
  "obfuscation": {
    "enableStringEncryption": true,
    "enableControlFlowFlattening": true,
    "enableInstructionSubstitution": true,
    "verbose": true
  }
}
```

### Metrics Collection

The tool collects various metrics:
- Code size increase
- Instruction count increase
- Complexity increase
- Per-pass metrics

Output formats:
- JSON: `metrics.json`
- HTML: `metrics.html` (with visualizations)

## Documentation

- **BLUEPRINT-FROM-GEMINI.md** - Comprehensive technical reference
- **04-TECHNICAL-REQUIREMENTS.md** - Detailed specifications
- **07-DEVELOPMENT-TIMELINE.md** - 8-week development plan
- **06-TESTING-GUIDE.md** - Testing strategy and framework
- **08-BEST-PRACTICES.md** - Coding standards and patterns

## References

- [LLVM Documentation](https://llvm.org/docs/)
- [Writing an LLVM Pass](https://llvm.org/docs/WritingAnLLVMPass/)
- [LLVM IR Reference](https://llvm.org/docs/LangRef/)
- [LLVM Passes](https://llvm.org/docs/Passes/)

## License

MIT License (see LICENSE file)

## Contributors

- Ayush (Creator)
- GitHub Copilot (Development Assistant)

## Next Steps

1. Implement core `PassManager` execution logic
2. Build and test first pass (String Encryption)
3. Create Python CLI wrapper
4. Develop comprehensive test suite
5. Integrate all passes into single pipeline

---

**Status**: Phase 1 Complete ✅ | Phase 2 In Progress 🚀
