message(STATUS "==== Processing ${CMAKE_CURRENT_LIST_FILE} ====")

if(NOT RETRONOMICON_GRAPHICS_TARGET)
    message(FATAL_ERROR "sandbox requires RETRONOMICON_GRAPHICS_BACKEND to select a graphics backend")
endif()

# Executable target
add_executable(sandbox
    main.cpp
    # add other sandbox .cpp files here
)

# Link against the full retronomicon engine
target_link_libraries(sandbox
    PRIVATE
        retronomicon
        ${RETRONOMICON_GRAPHICS_TARGET}
        ${RETRONOMICON_AUDIO_TARGET}
)

if(TARGET retronomicon-conversation)
    target_link_libraries(sandbox PRIVATE retronomicon-conversation)
endif()

if(TARGET retronomicon-card-battle)
    target_link_libraries(sandbox PRIVATE retronomicon-card-battle)
endif()

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
