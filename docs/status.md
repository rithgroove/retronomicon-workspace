# Retronomicon Workspace Status

This workspace is organized around a backend-neutral core plus optional
graphics, audio, and gameplay modules.

## Current Build Matrix

| Area | Target | Status |
| --- | --- | --- |
| Core | `retronomicon` | Builds and runs Catch2 tests. |
| Conversation data | `retronomicon-conversation` | Builds, validates JSON, and has traversal tests. |
| Conversation console | `conversation-console` | Builds and runs without graphics/audio backends. |
| SDL graphics | `retronomicon-sdl` | Builds as a graphics/input/font backend. |
| OpenGL graphics | `retronomicon-opengl` | Builds as a graphics/input/font backend. |
| Vulkan graphics | `retronomicon-vulkan` | Builds as a scaffold using SDL for window/surface creation. |
| DirectX graphics | `retronomicon-directx` | Builds as a placeholder target. |
| SDL_mixer audio | `retronomicon-audio-sdl-mixer` | Builds when `RETRONOMICON_GRAPHICS_BACKEND=SDL`. |
| OpenAL audio | `retronomicon-audio-openal` | Builds when `RETRONOMICON_GRAPHICS_BACKEND=OPENGL`. |
| XAudio2 audio | `retronomicon-audio-xaudio2` | Scaffold only. |

## Important Boundaries

- Core owns interfaces and engine orchestration only.
- Graphics backends own windows, rendering, textures, font assets, and raw input.
- Audio is selected through `retronomicon-audio`, not through graphics aggregate targets.
- Conversation data is backend-neutral under `retronomicon/conversation/...`.
- Old graphical conversation files under `retronomicon-conversation/src/lib/conversation/` are reference-only.

## Known Constraints

- SDL_mixer still depends on SDL2/SDL2_mixer vendored in `retronomicon-sdl`.
- OpenAL still depends on OpenAL vendored in `retronomicon-opengl`.
- Audio can be selected independently in CMake, but dependency vendoring still couples `SDL_MIXER` to SDL and `OPENAL` to OpenGL.
- The graphical conversation example has not been rebuilt on top of the current backend interfaces.

## Recommended Next Work

1. Add a graphical `conversation-example` that consumes `ConversationDocument` and `ConversationState`.
2. Move SDL_mixer/OpenAL source and dependency discovery fully into `retronomicon-audio`.
3. Add a concrete XAudio2 implementation in `retronomicon-audio`.
4. Replace legacy sandbox code with backend-neutral examples.
5. Add adapter tests for input mapping and audio cue dispatch.
