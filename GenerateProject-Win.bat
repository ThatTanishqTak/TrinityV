@echo off
SETLOCAL ENABLEEXTENSIONS

REM Check if CMake is available
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: CMake is not installed or not in PATH
    exit /b 1
)

REM Create build directory if it doesn't exist
if not exist build mkdir build

REM Navigate to build directory
cd build

REM Generate Visual Studio 2022 solution
cmake -G "Visual Studio 17 2022" ^
      -A Win32 ^
      ..
      
if %errorlevel% neq 0 (
    echo Error: Failed to generate solution
    cd ..
    exit /b 1
)

echo Solution generated successfully!
echo Location: %~dp0build\*.sln
cd ..
pause