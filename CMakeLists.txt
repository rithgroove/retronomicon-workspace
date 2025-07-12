cmake_minimum_required(VERSION 3.10)
project(retronomicon-workspace)

# Enable C++17 or later
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optionally enable debug flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# External library: retronomicon engine
# Assumes retronomicon is a submodule or sibling directory
add_subdirectory(retronomicon retronomicon_build)

# Add sandbox project
add_subdirectory(sandbox)
