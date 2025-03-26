cmake_minimum_required(VERSION 3.20)
project(TrinityV)

set(OS x32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OS x64)
endif()

set(OutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${OS}-${CMAKE_BUILD_TYPE}/${PROJECT_NAME}")

add_subdirectory(TrinityEngine)
add_subdirectory(TrinityApp)