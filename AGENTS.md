# AI Agent Instructions for Linthesia

**This is the UNIVERSAL INSTRUCTIONS file for all AI models (Claude, ChatGPT, Gemini, Copilot, Jules, etc.) working on this project.**

## Core Directives & Vision
1.  **Ultimate Goal**: Create the "Ultimate Open-Source Piano Learning Software" for Linux, rivaling Synthesia, Melodics, and Miracle Piano.
2.  **Completeness**: Implement features exhaustively. No partial implementations. Every backend feature must have a frontend UI representation (toggle, slider, indicator).
3.  **UI/UX**:
    *   **Representation**: Every feature must be "very well represented in full detail in UI".
    *   **Feedback**: Visual feedback for all states (Waiting, Hit, Miss, Paused).
    *   **Documentation**: Tooltips for every button/setting. Help screens.
    *   **No Hidden Hotkeys**: All hotkeys must have a visible UI button or menu entry.

## Workflow Protocol
1.  **Analysis**:
    *   Deeply analyze project state (`ls -R`, `grep`, etc.) before acting.
    *   Identify unimplemented features from `ROADMAP.md` or code comments (`TODO`).
    *   Research dependencies and submodules.
2.  **Planning**:
    *   Create a detailed plan using `set_plan`.
    *   Prioritize "unhooked" backend features or UI gaps.
3.  **Implementation**:
    *   **Autonomy**: Proceed autonomously as long as possible.
    *   **Commit Frequency**: Commit and push between major steps.
    *   **Testing**: Verify compilation (`meson compile -C build`) after changes.
4.  **Documentation (Crucial)**:
    *   **Source of Truth**: `AGENTS.md` is the master file.
    *   **Versioning**: Update `VERSION` file and `CHANGELOG.md` for *every* build or significant change.
    *   **Structure**: Maintain `DASHBOARD.md` (project structure), `VISION.md` (goals), `ROADMAP.md` (features).
    *   **Handoff**: Write `HANDOFF.md` at the end of sessions.

## Codebase Standards
*   **Language**: C++14 (modern C++ practices where possible).
*   **Build System**: Meson + Ninja.
    *   **Dependencies**: SDL2, ALSA, SQLite, Freetype, Cairo/Pango (if used).
    *   **Protocol**: Update `meson.build` immediately when adding files.
*   **Style**:
    *   Classes: `CamelCase`.
    *   Variables: `snake_case`.
    *   Members: `m_snake_case`.
*   **Settings**: Use `UserSetting` namespace (wraps GSettings). Define keys in `UserSettings.h` and schema in `extra/`.

## Submodule Management
*   **Protocol**:
    *   Always update submodules (`git submodule update --init --recursive`).
    *   Merge upstream changes if applicable.
    *   Document submodule status in `DASHBOARD.md`.
*   **Repositories**:
    *   `pianogame`: Original source (reference).

## Documentation Files
*   `AGENTS.md`: **This File**. Universal instructions.
*   `VISION.md`: Detailed long-term vision and design philosophy.
*   `ROADMAP.md`: High-level feature tracking.
*   `TODO.md`: Granular tasks and bugs.
*   `DASHBOARD.md`: Project structure, file layout, submodule status.
*   `DEPLOY.md`: Build and deployment instructions.
*   `MEMORY.md`: Ongoing observations and design notes.
*   `HANDOFF.md`: Session context for the next agent.
*   `CHANGELOG.md`: User-facing history.
*   `VERSION`: Single source of truth for version string (e.g., `1.6.0-dev`).

## Deployment Instructions (Summary)
See `DEPLOY.md` for details.
```bash
sudo apt-get install -y libasound2-dev libgl1-mesa-dev libglibmm-2.4-dev libsqlite3-dev libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev gettext meson ninja
meson setup build
meson compile -C build
./build/src/linthesia
```

## Git & Versioning
*   **Commit Message**: "vX.Y.Z: Summary of changes".
*   **Tagging**: Bump version in `VERSION` file.
*   **Push**: Push frequently.

## Model-Specific Overrides
*   **Claude**: Focus on C++ architecture and deep logic.
*   **Gemini**: Documentation and broad analysis.
*   **GPT**: Boilerplate and refactoring.
*   **Jules**: Long-running tasks, integration, and execution.
