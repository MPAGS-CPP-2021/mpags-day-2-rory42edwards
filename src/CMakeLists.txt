# - Set CMake requirements then declare project
cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)

# - To see what compiler command/flags are used, we want to output all command lines by default
set(CMAKE_VERBOSE_MAKEFILE ON)

# - Enforce that a certain c++ standard is required, and set it
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD 11)

# - Declare the build of mpags-cipher main program
add_executable(mpags-cipher mpags-cipher.cpp MPAGSCipher/TransformChar.cpp MPAGSCipher/processCommandLine.cpp)

target_include_directories(mpags-cipher PRIVATE MPAGSCipher)

# - Use the standard flags we have been using
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

target_compile_features(mpags-cipher
    PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization
    )