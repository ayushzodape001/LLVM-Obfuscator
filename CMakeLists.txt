cmake_minimum_required(VERSION 3.20)
project(LLVM-Obfuscator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# LLVM installation prefix
set(LLVM_PREFIX "C:/Program Files/LLVM" CACHE PATH "LLVM installation prefix")

# Include directories
include_directories(${LLVM_PREFIX}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link directories
link_directories(${LLVM_PREFIX}/lib)

# Get LLVM libraries (use C API for now since C++ libs not available in this build)
set(LLVM_LIBS
    LLVM-C
)

# Print configuration
message(STATUS "LLVM Prefix: ${LLVM_PREFIX}")
message(STATUS "LLVM Include: ${LLVM_PREFIX}/include")
message(STATUS "LLVM Lib: ${LLVM_PREFIX}/lib")
message(STATUS "LLVM Libraries: ${LLVM_LIBS}")

# Add subdirectories
add_subdirectory(src/core)
add_subdirectory(src/passes)
add_subdirectory(src/analysis)
