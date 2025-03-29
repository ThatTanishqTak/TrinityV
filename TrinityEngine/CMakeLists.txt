cmake_minimum_required(VERSION 3.20)
project(TrinityEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OutputDir}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OutputDir}")

add_library(${PROJECT_NAME} STATIC 
    "src/Engine.cpp" "src/Engine.h" 
    "src/WindowsWindow/WindowsWindow.h" "src/WindowsWindow/WindowsWindow.cpp"
    "src/Renderer/Pipeline.h" "src/Renderer/Pipeline.cpp"
    "src/Device/Device.h" "src/Device/Device.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/TrinityEngine/vendor/GLFW/include
    ${CMAKE_SOURCE_DIR}/TrinityEngine/vendor/glm
    $ENV{VULKAN_SDK}/Include)

target_link_libraries(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/TrinityEngine/vendor/GLFW/lib-vc2022/glfw3.lib
    $ENV{VULKAN_SDK}/Lib/vulkan-1.lib
    opengl32.lib)

function(add_shaders TARGET_NAME)
    set(SHADER_SOURCE_FILES ${ARGN})
    
    list(LENGTH SHADER_SOURCE_FILES FILE_COUNT)
    if(FILE_COUNT EQUAL 0)
        message(FATAL_ERROR "Cannot create a shaders target without any source files")
    endif()

    set(SHADER_COMMANDS)
    set(SHADER_PRODUCTS)

    foreach(SHADER_SOURCE IN LISTS SHADER_SOURCE_FILES)
        cmake_path(ABSOLUTE_PATH SHADER_SOURCE NORMALIZE)
        cmake_path(GET SHADER_SOURCE FILENAME SHADER_NAME)
        
        list(APPEND SHADER_COMMANDS COMMAND)
        list(APPEND SHADER_COMMANDS ${Vulkan_GLSLC_EXECUTABLE})
        list(APPEND SHADER_COMMANDS "${SHADER_SOURCE}")
        list(APPEND SHADER_COMMANDS "-o")
        list(APPEND SHADER_COMMANDS "${OutputDir}/Shaders/${SHADER_NAME}.spv")

        list(APPEND SHADER_PRODUCTS "${OutputDir}/Shaders/${SHADER_NAME}.spv")
    endforeach()

    add_custom_target(${TARGET_NAME} ALL
        ${SHADER_COMMANDS}
        COMMENT "Compiling Shaders [${TARGET_NAME}]"
        SOURCES ${SHADER_SOURCE_FILES}
        BYPRODUCTS ${SHADER_PRODUCTS}
    )
endfunction()

find_package(Vulkan REQUIRED)

set(SHADER_SOURCES 
    "src/Shader/Shader.vert"
    "src/Shader/Shader.frag"
)

add_shaders(COMPILE_SHADER ${SHADER_SOURCES})