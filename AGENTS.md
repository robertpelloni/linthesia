# AI Agent Instructions for Linthesia

These instructions are intended for AI agents (like Claude, ChatGPT, Google Jules) working on the Linthesia codebase.

## Codebase Overview
Linthesia is a C++14 project using the Meson build system. It relies heavily on SDL2 for graphics and input, and ALSA for MIDI communication.

### Key Directories
*   `src/`: Main source code.
*   `src/libmidi/`: MIDI parsing and handling logic.
*   `graphics/`: TGA textures and font files.
*   `extra/`: Linux desktop integration files (desktop entry, appdata, gschema).

### Coding Conventions
*   **Language**: C++14.
*   **Style**: Use `snake_case` for variables/functions, `CamelCase` for classes.
*   **Headers**: Use `#pragma once` or include guards.
*   **Constants**: Avoid magic numbers. Use `const static` or `#define` in appropriate headers (e.g., `UserSettings.h`).
*   **Error Handling**: Use `try-catch` blocks for file I/O and user input parsing.
*   **Graphics**: Use `Renderer` class wrappers for SDL calls where possible.

### Build System
*   The project uses Meson.
*   Always update `meson.build` when adding new source files.
*   Version number is stored in the `VERSION` file at the root.

### User Settings
*   Use `UserSetting::Get` and `UserSetting::Set` for persistent configuration.
*   Define new keys in `src/UserSettings.h` and `extra/com.github.linthesia.linthesia.gschema.xml`.

### Versioning
*   **Single Source of Truth**: The `VERSION` file in the root directory.
*   **Bump Protocol**: When releasing a new version or significant feature set:
    1.  Update `VERSION`.
    2.  Update `CHANGELOG.md`.
    3.  Commit with message "Bump version to X.Y.Z".

### Roadmap & Tasks
*   Refer to `ROADMAP.md` for planned features.
*   Update `ROADMAP.md` as tasks are completed.
*   Document submodules in `DASHBOARD.md`.

## Workflow
1.  **Analyze**: Understand the requirement and existing code.
2.  **Plan**: Create a step-by-step plan.
3.  **Implement**: Write code, following conventions.
4.  **Verify**: Ensure code compiles and features work as expected.
5.  **Document**: Update relevant markdown files.
