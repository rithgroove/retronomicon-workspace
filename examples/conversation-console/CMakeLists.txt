add_executable(conversation-console
    main.cpp
)

target_link_libraries(conversation-console
    PRIVATE
        nlohmann_json::nlohmann_json
)

target_compile_definitions(conversation-console
    PRIVATE
        RETRONOMICON_DEFAULT_CONVERSATION_PATH="${CMAKE_SOURCE_DIR}/asset/conversation/conversation.json"
)
