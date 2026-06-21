cmake_minimum_required(VERSION 3.15)
project(retronomicon-workspace LANGUAGES CXX)

message(STATUS "==== Processing ${CMAKE_CURRENT_LIST_FILE} ====")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RETRONOMICON_GRAPHICS_BACKEND "NONE" CACHE STRING "Graphics backend: NONE, SDL, OPENGL, VULKAN, DIRECTX")
set_property(CACHE RETRONOMICON_GRAPHICS_BACKEND PROPERTY STRINGS NONE SDL OPENGL VULKAN DIRECTX)

set(RETRONOMICON_AUDIO_BACKEND "NONE" CACHE STRING "Audio backend: NONE, SDL_MIXER, OPENAL, XAUDIO2")
set_property(CACHE RETRONOMICON_AUDIO_BACKEND PROPERTY STRINGS NONE SDL_MIXER OPENAL XAUDIO2)

option(RETRONOMICON_BUILD_CONVERSATION "Build the legacy conversation module" OFF)
option(RETRONOMICON_BUILD_CARD_BATTLE "Build the legacy card battle module" OFF)
option(RETRONOMICON_BUILD_SANDBOX "Build the legacy sandbox executable" OFF)

# Build retronomicon base engine
add_subdirectory(retronomicon retronomicon_build)

set(RETRONOMICON_GRAPHICS_TARGET "")
set(RETRONOMICON_AUDIO_TARGET "")

if(RETRONOMICON_GRAPHICS_BACKEND STREQUAL "SDL")
    add_subdirectory(retronomicon-sdl retronomicon_sdl_build)
    set(RETRONOMICON_GRAPHICS_TARGET retronomicon-sdl)
elseif(RETRONOMICON_GRAPHICS_BACKEND STREQUAL "OPENGL")
    add_subdirectory(retronomicon-opengl retronomicon_opengl_build)
    set(RETRONOMICON_GRAPHICS_TARGET retronomicon-opengl)
elseif(RETRONOMICON_GRAPHICS_BACKEND STREQUAL "VULKAN")
    add_subdirectory(retronomicon-vulkan retronomicon_vulkan_build)
    set(RETRONOMICON_GRAPHICS_TARGET retronomicon-vulkan)
elseif(RETRONOMICON_GRAPHICS_BACKEND STREQUAL "DIRECTX")
    add_subdirectory(retronomicon-directx retronomicon_directx_build)
    set(RETRONOMICON_GRAPHICS_TARGET retronomicon-directx)
elseif(NOT RETRONOMICON_GRAPHICS_BACKEND STREQUAL "NONE")
    message(FATAL_ERROR "Unknown RETRONOMICON_GRAPHICS_BACKEND: ${RETRONOMICON_GRAPHICS_BACKEND}")
endif()

if(NOT RETRONOMICON_AUDIO_BACKEND STREQUAL "NONE")
    add_subdirectory(retronomicon-audio retronomicon_audio_build)
    if(RETRONOMICON_AUDIO_BACKEND STREQUAL "SDL_MIXER")
        set(RETRONOMICON_AUDIO_TARGET retronomicon-audio-sdl-mixer)
    elseif(RETRONOMICON_AUDIO_BACKEND STREQUAL "OPENAL")
        set(RETRONOMICON_AUDIO_TARGET retronomicon-audio-openal)
    elseif(RETRONOMICON_AUDIO_BACKEND STREQUAL "XAUDIO2")
        set(RETRONOMICON_AUDIO_TARGET retronomicon-audio-xaudio2)
    else()
        message(FATAL_ERROR "Unknown RETRONOMICON_AUDIO_BACKEND: ${RETRONOMICON_AUDIO_BACKEND}")
    endif()
endif()

if(RETRONOMICON_BUILD_CONVERSATION)
    add_subdirectory(retronomicon-conversation retronomicon_conversation_build)
endif()

if(RETRONOMICON_BUILD_CARD_BATTLE)
    add_subdirectory(retronomicon-card-battle retronomicon_card_battle_build)
endif()

if(RETRONOMICON_BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()

message(STATUS "Retronomicon graphics backend: ${RETRONOMICON_GRAPHICS_BACKEND}")
message(STATUS "Retronomicon audio backend: ${RETRONOMICON_AUDIO_BACKEND}")
