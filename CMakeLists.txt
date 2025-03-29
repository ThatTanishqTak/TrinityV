cmake_minimum_required(VERSION 3.20)
project(TrinityV)

set(OS "")
set(ARCH "")

# Get system name
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(OS "Windows")
        set(ARCH x86)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCH x64)
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(OS "Macos")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(OS "Linux")
endif()

# Combine into a single variable
set(PLATFORM "${OS}-${ARCH}")
set(OutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/${PROJECT_NAME}")

add_subdirectory(TrinityEngine)
add_subdirectory(TrinityApp)