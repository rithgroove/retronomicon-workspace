cmake_minimum_required(VERSION 3.10)
project(retronomicon-workspace LANGUAGES CXX)

message(STATUS "==== Processing ${CMAKE_CURRENT_LIST_FILE} ====")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build retronomicon base engine
add_subdirectory(retronomicon retronomicon_build)

# Build conversation module (depends on retronomicon)
add_subdirectory(retronomicon-conversation retronomicon_conversation_build)

# Build sandbox test project
add_subdirectory(sandbox)
