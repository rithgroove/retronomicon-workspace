message(STATUS "==== Processing ${CMAKE_CURRENT_LIST_FILE} ====")
# Executable target
add_executable(sandbox
    main.cpp
    # add other sandbox .cpp files here
)

# Link against the full retronomicon engine
target_link_libraries(sandbox retronomicon retronomicon-conversation retronomicon-card-battle)

# Include the engine's public headers
#target_include_directories(sandbox
#    PRIVATE
#        ${CMAKE_SOURCE_DIR}/retronomicon/include
#)

# Set output directory (if not already set)
#set(BINARY_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

# Copy assets folder to binary output folder
#add_custom_command(
#    TARGET your_game_target POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#            ${CMAKE_SOURCE_DIR}/asset
#            ${BINARY_OUTPUT_DIR}/asset
#)