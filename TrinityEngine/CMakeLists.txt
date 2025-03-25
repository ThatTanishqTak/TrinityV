cmake_minimum_required(VERSION 3.15)
project(TrinityEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OutputDir}/${PROJECT_NAME}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OutputDir}/${PROJECT_NAME}")

add_library(${PROJECT_NAME} STATIC 
    "src/Engine.cpp" "src/Engine.h" 
    "src/WindowsWindow/WindowsWindow.h" "src/WindowsWindow/WindowsWindow.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/TrinityEngine/vendor/GLFW/include
    ${CMAKE_SOURCE_DIR}/TrinityEngine/vendor/glm
    $ENV{VULKAN_SDK}/Include)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/TrinityEngine/vendor/GLFW/lib-vc2022/glfw3.lib
    $ENV{VULKAN_SDK}/Lib/vulkan-1.lib
    opengl32.lib)