@echo off
echo Compiling Library Management System...
g++ -std=c++11 -Wall -Wextra -g main.cpp Book.cpp Student.cpp Library.cpp -o library_system.exe
if %errorlevel% equ 0 (
    echo Compilation successful!
    echo Run the program with: library_system.exe
) else (
    echo Compilation failed!
    pause
)
