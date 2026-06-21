# Repository Guidelines

## Project Structure & Module Organization

This repository is a C++17 CMake workspace for Retronomicon modules. The base engine lives in `retronomicon/`. Graphics backends live in `retronomicon-sdl/`, `retronomicon-opengl/`, `retronomicon-vulkan/`, and `retronomicon-directx/`; audio backend targets live in `retronomicon-audio/`. Gameplay modules live in `retronomicon-conversation/`, `retronomicon-card-battle/`, and `retronomicon-platformer/`. Active examples live under `examples/`; legacy experiments live under `sandbox/`. Public headers live under each module's `include/` tree, with implementations under `src/`. Shared runtime data is in `asset/`. Treat `external/` folders as vendored dependency code unless intentionally updating third-party libraries.

## Build, Test, and Development Commands

- `git submodule update --init --recursive`: initializes workspace and backend dependencies.
- `cmake -S . -B build && cmake --build build`: builds the backend-neutral core and runs core tests.
- `cmake -S . -B build-sdl -DRETRONOMICON_GRAPHICS_BACKEND=SDL`: configures with the SDL backend.
- `cmake -S . -B build-opengl -DRETRONOMICON_GRAPHICS_BACKEND=OPENGL`: configures with the OpenGL backend.
- `cmake -S . -B build-vulkan -DRETRONOMICON_GRAPHICS_BACKEND=VULKAN`: configures with the Vulkan backend.
- `cmake -S . -B build-sdl-audio -DRETRONOMICON_GRAPHICS_BACKEND=SDL -DRETRONOMICON_AUDIO_BACKEND=SDL_MIXER`: builds the SDL_mixer audio target.
- `cmake -S . -B build-openal -DRETRONOMICON_GRAPHICS_BACKEND=OPENGL -DRETRONOMICON_AUDIO_BACKEND=OPENAL`: builds the OpenAL audio target.
- `cmake --build build --target conversation-console`: builds the backend-neutral conversation data example.
- `./build/bin/conversation-console`: runs the default `asset/conversation/conversation.json` traversal.

Use `RETRONOMICON_BUILD_CARD_BATTLE=ON` or `RETRONOMICON_BUILD_SANDBOX=ON` only when intentionally building legacy modules/examples. `RETRONOMICON_BUILD_CONVERSATION` now builds the backend-neutral conversation data module and defaults on.

## Coding Style & Naming Conventions

Use C++17 and match the surrounding style. Source and header filenames use lowercase snake case, for example `conversation_loader.cpp` and `battle_state_machine.h`. Types use PascalCase, functions and variables use lower camelCase, and namespaces follow the owning module, such as `retronomicon::conversation`, `retronomicon::sdl`, or `retronomicon::opengl`. Prefer 4-space indentation in C++ files. Keep module APIs in `include/` and implementation details in `src/`.

## Testing Guidelines

The base engine uses Catch2 tests in `retronomicon/tests/`, and conversation tests live in `retronomicon-conversation/tests/`. Test files follow `test_*.cpp`; add focused cases with `TEST_CASE("behavior", "[tag]")`. The `engine_tests` and `retronomicon-conversation-tests` targets run during normal CMake builds. For backend changes, verify at least the touched backend target, for example `cmake --build build-vulkan --target retronomicon-vulkan`.

## Commit & Pull Request Guidelines

Recent commit history uses short, imperative, lowercase messages such as `update readme`, `fix a bit`, and `add retronomicon-card-battle`. Keep commits narrow and describe the changed module when useful. Pull requests should include a concise summary, verification steps or command output, linked issues if applicable, and screenshots or recordings for visible gameplay, UI, or asset changes.

## Assets & Configuration

Keep asset paths stable because examples load paths under `asset/` directly. The conversation reference project is `~/Desktop/project-yuzu`; use its `asset/conversation/conversation.json`, `asset/conversation/characters.json`, and `sandbox-opengl/main_conv.cpp` as references. The active workspace example is `examples/conversation-console`, backed by `retronomicon/conversation/...`. The stale graphical conversation files under `retronomicon-conversation/src/lib/conversation/` are reference-only until a new adapter is built against current backend interfaces. Do not commit generated `build/`, `build-*`, or `build-aarch64/` outputs.

## Current Handoff

Read `docs/status.md` before making broad backend changes. It records the current build matrix, known audio dependency coupling, and the next recommended work.
