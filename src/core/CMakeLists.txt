add_library(ObfuscatorCore STATIC
    PassManager.cpp
    MetricsCollector.cpp
    ConfigParser.cpp
    Logger.cpp
    Utils.cpp
)

target_link_libraries(ObfuscatorCore ${LLVM_LIBS})
target_include_directories(ObfuscatorCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
