cmake_minimum_required(VERSION 3.13)  # CMake version check
project(zadanie1)                     # Create project "zadanie1"
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/gcc-12")

set(SOURCE_FILES zadanie1.c)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(zadanie1 ${SOURCE_FILES})