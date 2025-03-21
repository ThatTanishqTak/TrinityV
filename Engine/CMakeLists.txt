cmake_minimum_required(VERSION 3.15)
project(Engine LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Add library
add_library(${PROJECT_NAME} STATIC 
    src/Engine.cpp 
    src/Engine.h)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/Engine/vendor/GLFW/include
    ${CMAKE_SOURCE_DIR}/Engine/vendor/glm
    $ENV{VULKAN_SDK}/Include)

# Add dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/Engine/vendor/GLFW/lib-vc2022/glfw3.lib
    $ENV{VULKAN_SDK}/Lib/vulkan-1.lib
    opengl32.lib)