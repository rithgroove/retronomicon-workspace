add_executable(retronomicon-sandbox
    sandbox/main.cpp
    sandbox/test_scene.cpp
)

target_link_libraries(retronomicon-sandbox PRIVATE retronomicon)

target_include_directories(retronomicon-sandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
