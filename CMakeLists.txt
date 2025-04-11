# Minimum CMake version requirement
cmake_minimum_required(VERSION 3.20)

# Project definition
project(TrinityV)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable multi-processor compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

# Define output directories
set(BINARY_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SIZEOF_VOID_P}bit/TrinityV")
set(INTERMEDIATE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin-int/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SIZEOF_VOID_P}bit/TrinityV")

# Set output directories for all types of targets
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR})
set(CMAKE_OBJECT_OUTPUT_DIRECTORY ${INTERMEDIATE_OUTPUT_DIR})

# Add subdirectories
add_subdirectory(Engine)
add_subdirectory(App)