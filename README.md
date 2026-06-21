# retronomicon-workspace

Retronomicon workspace repository for the core engine, optional gameplay
modules, and selectable graphics/audio backends.

## Layout

- `retronomicon/`: backend-neutral engine core, public interfaces, and tests.
- `retronomicon-sdl/`: SDL window, renderer, texture, font asset, and raw input backend.
- `retronomicon-opengl/`: OpenGL/GLFW window, renderer, texture, font asset, and raw input backend.
- `retronomicon-vulkan/`: Vulkan backend scaffold using SDL for window/surface creation.
- `retronomicon-directx/`: DirectX backend placeholder target.
- `retronomicon-audio/`: audio backend targets for SDL_mixer, OpenAL, and XAudio2 scaffold.
- `retronomicon-conversation/`: backend-neutral visual-novel conversation data and traversal module.
- `retronomicon-card-battle/`: card battle module.
- `examples/conversation-console/`: backend-neutral conversation data example.
- `sandbox/`: legacy sample app; opt in while it is migrated to backend-neutral APIs.
- `asset/`: shared runtime assets for examples.

## Build

Initialize submodules first:

```sh
git submodule update --init --recursive
```

Default core-only build:

```sh
cmake -S . -B build
cmake --build build
```

Run the conversation data example:

```sh
cmake --build build --target conversation-console
./build/bin/conversation-console
```

Select a graphics backend:

```sh
cmake -S . -B build-sdl -DRETRONOMICON_GRAPHICS_BACKEND=SDL
cmake -S . -B build-opengl -DRETRONOMICON_GRAPHICS_BACKEND=OPENGL
cmake -S . -B build-vulkan -DRETRONOMICON_GRAPHICS_BACKEND=VULKAN
cmake -S . -B build-directx -DRETRONOMICON_GRAPHICS_BACKEND=DIRECTX
```

Select an audio backend:

```sh
cmake -S . -B build-sdl-audio \
  -DRETRONOMICON_GRAPHICS_BACKEND=SDL \
  -DRETRONOMICON_AUDIO_BACKEND=SDL_MIXER

cmake -S . -B build-openal \
  -DRETRONOMICON_GRAPHICS_BACKEND=OPENGL \
  -DRETRONOMICON_AUDIO_BACKEND=OPENAL
```

`SDL_MIXER` currently requires the SDL submodule because SDL2_mixer is vendored
there. `OPENAL` currently requires the OpenGL submodule because OpenAL is
vendored there. `XAUDIO2` is still a target scaffold.

Supported values are:

- `RETRONOMICON_GRAPHICS_BACKEND`: `NONE`, `SDL`, `OPENGL`, `VULKAN`, `DIRECTX`
- `RETRONOMICON_AUDIO_BACKEND`: `NONE`, `SDL_MIXER`, `OPENAL`, `XAUDIO2`

## Optional Modules

Legacy modules and examples are off by default, except the backend-neutral
conversation library and console example:

```sh
cmake -S . -B build \
  -DRETRONOMICON_GRAPHICS_BACKEND=SDL \
  -DRETRONOMICON_BUILD_CARD_BATTLE=ON \
  -DRETRONOMICON_BUILD_SANDBOX=ON
```

The current `sandbox/` code still uses older SDL-specific headers and needs API
migration before it can serve as a backend-neutral example.

The stale graphical conversation scene files are retained in
`retronomicon-conversation/src/lib/conversation/` for reference but are no
longer part of the build. The active public API is
`retronomicon/conversation/...`, with tests in `retronomicon-conversation/tests/`.

## Conversation Reference

`~/Desktop/project-yuzu` is the reference project for the conversation engine.
The useful pieces are:

- `asset/conversation/conversation.json`: node/background schema.
- `asset/conversation/characters.json`: character database entry point.
- `sandbox-opengl/main_conv.cpp`: minimal console traversal reference.
- `retronomicon-conversation/`: active conversation loader, validation, and traversal state.
- `examples/conversation-console/`: active workspace console traversal target using the module API.
- `sandbox/main.cpp` in this workspace: older graphical flow that loads
  characters, registers `ConversationCharacterModuleLoader`, loads conversation
  JSON as a text asset, and registers the scene.

The next code step is to add a graphical `conversation-example` target that
adapts `ConversationDocument` and `ConversationState` to the selected
graphics/audio backends.

## Verification

The core engine uses Catch2 tests in `retronomicon/tests/`. The conversation
module has Catch2 tests in `retronomicon-conversation/tests/`. Both run during
normal CMake builds.

```sh
cmake --build build --target engine_tests
cmake --build build --target retronomicon-conversation-tests
```

## Credits

- Font: Manaspace by Cody Boisclair.
- Sprite: Building2 from City Mega Pack by GrafxKid.
- Sprite: Miho by rithgroove and ceteee21.
- Sound: Funny Swish by Freesound Community.
- Sound: Background Music by DesiFreeMusic.
- UI: 9 Slice menu asset by Kenney.
- Background: Free Visual Novel Background by Potato Master.
