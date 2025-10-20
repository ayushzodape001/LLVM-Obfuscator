add_library(ObfuscatorAnalysis STATIC
    ComplexityAnalyzer.cpp
    CFGAnalyzer.cpp
)

target_link_libraries(ObfuscatorAnalysis
    ObfuscatorCore
    ${LLVM_LIBS}
)

target_include_directories(ObfuscatorAnalysis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
