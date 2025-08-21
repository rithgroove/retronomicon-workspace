message(STATUS "==== Processing ${CMAKE_CURRENT_LIST_FILE} ====")

add_executable(sandbox
    main.cpp
    # Add other sandbox .cpp files here
)

# Link against engine and conversation lib
target_link_libraries(sandbox
    PRIVATE
        retronomicon
        retronomicon-conversation
)

# Engine include dirs (public ones will be inherited anyway if retronomicon sets them)
target_include_directories(sandbox
    PRIVATE
        ${CMAKE_SOURCE_DIR}/retronomicon/include
        ${CMAKE_SOURCE_DIR}/retronomicon-conversation/include
)

# Set output dir for executables (optional)
set_target_properties(sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Example: Copy assets folder into build/bin/assets after build
add_custom_command(
    TARGET sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/asset
            $<TARGET_FILE_DIR:sandbox>/asset
)
