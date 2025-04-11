# Project definition
project(Engine)

# Find all source files
file(GLOB SOURCES "Engine.cpp" "Engine.h" "src/**.cpp" "src/**.h")

# Create static library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${BINARY_OUTPUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${BINARY_OUTPUT_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${BINARY_OUTPUT_DIR}"
    OBJECT_OUTPUT_DIRECTORY "${INTERMEDIATE_OUTPUT_DIR}"
)

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor>
)