# Project definition
project(App)

# Add executable target
add_executable(${PROJECT_NAME} "src/EntryPoint.cpp")

# Link against Engine library
target_link_libraries(${PROJECT_NAME} PRIVATE Engine)

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${BINARY_OUTPUT_DIR}"
    OBJECT_OUTPUT_DIRECTORY "${INTERMEDIATE_OUTPUT_DIR}"
)

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/App/src>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Engine>
)