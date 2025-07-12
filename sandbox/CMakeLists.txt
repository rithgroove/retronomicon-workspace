message(STATUS "==== Processing ${CMAKE_CURRENT_LIST_FILE} ====")
# Executable target
add_executable(sandbox
    main.cpp
    # add other sandbox .cpp files here
)

# Link against the full retronomicon engine
target_link_libraries(sandbox retronomicon)

# Include the engine's public headers
target_include_directories(sandbox
    PRIVATE
        ${CMAKE_SOURCE_DIR}/retronomicon/include
)