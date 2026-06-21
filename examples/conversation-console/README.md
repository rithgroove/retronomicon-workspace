# conversation-console

Backend-neutral conversation data example.

This target validates and traverses the workspace conversation JSON without
opening a window or linking a graphics backend. It is the current clean example
for the conversation data contract while the graphical `retronomicon-conversation`
scene is migrated from the old `retronomicon/lib/...` API.

## Build

From the workspace root:

```sh
cmake -S . -B build
cmake --build build --target conversation-console
```

## Run

```sh
./build/bin/conversation-console
./build/bin/conversation-console asset/conversation/conversation_backup.json
```

The default path is compiled from the workspace source directory, so the binary
can be run from any working directory.
