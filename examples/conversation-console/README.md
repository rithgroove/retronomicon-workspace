# conversation-console

Backend-neutral conversation data example.

This target validates and traverses the workspace conversation JSON without
opening a window or linking a graphics backend. It uses
`retronomicon::conversation::ConversationLoader` and `ConversationState`, so it
is the active example for the conversation data contract.

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

## Notes

The console follows the first choice automatically when it reaches a choice
node. A future graphical example should present choices through the selected
graphics/input backend instead.
