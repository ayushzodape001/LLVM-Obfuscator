add_library(ObfuscatorPasses SHARED
    ControlFlowFlattening.cpp
    StringEncryption.cpp
    InstructionSubstitution.cpp
    BogusControlFlow.cpp
    DeadCodeInsertion.cpp
    FunctionSplitting.cpp
)

target_link_libraries(ObfuscatorPasses
    ObfuscatorCore
    ${LLVM_LIBS}
)

target_include_directories(ObfuscatorPasses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# Set output directory
set_target_properties(ObfuscatorPasses PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
