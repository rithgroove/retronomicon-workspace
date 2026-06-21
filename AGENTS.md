# Repository Guidelines

## Project Structure & Module Organization

This repository is a C++17 CMake workspace for Retronomicon modules. The root `CMakeLists.txt` builds the base engine in `retronomicon/`, feature modules in `retronomicon-conversation/` and `retronomicon-card-battle/`, and the runnable `sandbox/` target. Public headers live under each module's `include/` tree, with implementations under `src/`. Shared runtime data is in `asset/`, including cards, decks, conversations, fonts, and audio. Cross-build toolchains are in `ToolChain/`. Treat `retronomicon/external/` as vendored dependency code unless intentionally updating third-party libraries.

## Build, Test, and Development Commands

- `./init.sh`: initializes submodules and installs Linux SDL/font/audio dependencies with `apt`.
- `./build-sandbox.sh`: configures `build/`, builds the workspace, and copies `asset/` into `build/sandbox/`.
- `./play.sh`: runs `./build/sandbox/sandbox`.
- `./clean.sh`: removes generated build directories.
- `./build-arkos.sh`: cross-builds with `ToolChain/TC-arkos.cmake` into `build-aarch64/`.

For manual builds, use `cmake -S . -B build` and `cmake --build build`.

## Coding Style & Naming Conventions

Use C++17 and match the surrounding style. Source and header filenames use lowercase snake case, for example `conversation_loader.cpp` and `battle_state_machine.h`. Types use PascalCase, functions and variables use lower camelCase, and namespaces follow the existing nested pattern such as `retronomicon::lib::conversation`. Prefer 4-space indentation in C++ files. Keep module APIs in `include/` and implementation details in `src/`.

## Testing Guidelines

The base engine uses Catch2 tests in `retronomicon/tests/`. Test files follow `test_*.cpp`; add focused cases with `TEST_CASE("behavior", "[tag]")`. The `engine_tests` target is built from these files and runs after build through CMake. Run `./build-sandbox.sh` for the normal verification path, or run `./build/bin/engine_tests` after configuring manually.

## Commit & Pull Request Guidelines

Recent commit history uses short, imperative, lowercase messages such as `update readme`, `fix a bit`, and `add retronomicon-card-battle`. Keep commits narrow and describe the changed module when useful. Pull requests should include a concise summary, verification steps or command output, linked issues if applicable, and screenshots or recordings for visible gameplay, UI, or asset changes.

## Assets & Configuration

Keep asset paths stable because runtime code expects copied `asset/` content beside the sandbox binary. Do not commit generated `build/` or `build-aarch64/` outputs.
