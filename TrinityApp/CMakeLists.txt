cmake_minimum_required(VERSION 3.20)
project(TrinityApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OutputDir}")

add_executable(TrinityApp)

file(GLOB_RECURSE APP_SRC "src/*.cpp" "src/*.h")
target_sources(TrinityApp PRIVATE ${APP_SRC})

target_link_libraries(TrinityApp PUBLIC TrinityEngine)