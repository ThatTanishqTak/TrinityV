cmake_minimum_required(VERSION 3.20)
project(TrinityV)

set(OS x32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OS x64)
endif()

set(OS "")
set(ARCH "")

# Get system name
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(OS "windows")
    # Get architecture
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCH "x64")
    else()
        set(ARCH "x32")
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(OS "macos")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(OS "linux")
endif()

# Combine into a single variable
set(PLATFORM "${OS}-${ARCH}")
set(OutputDir "${CMAKE_SOURCE_DIR}/bin/${PLATFORM}-${CMAKE_BUILD_TYPE}/${PROJECT_NAME}")

add_subdirectory(TrinityEngine)
add_subdirectory(TrinityApp)