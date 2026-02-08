# AI Agent Instructions for Linthesia

**This is the UNIVERSAL INSTRUCTIONS file for all AI models (Claude, ChatGPT, Gemini, Copilot, Jules, etc.) working on this project.**

## Core Directives
1.  **Project Goal**: Create the ultimate open-source piano learning software for Linux, mirroring and exceeding the features of Synthesia/Melodics.
2.  **UI/UX**: Every feature must be "very well represented in full detail in UI". No hidden hotkeys without UI equivalents. Extensive tooltips, labels, and help screens.
3.  **Documentation**:
    *   Maintain `README.md` as a user manual.
    *   Maintain `ROADMAP.md` for planning.
    *   Maintain `DASHBOARD.md` for project structure/status.
    *   Maintain `CHANGELOG.md` detailed history.
4.  **Versioning**:
    *   **Single Source of Truth**: The `VERSION` file in the root directory.
    *   **Protocol**: Update `VERSION` and `CHANGELOG.md` with every significant feature set or build.
    *   **Commit Message**: "Bump version to X.Y.Z" when updating version.

## Codebase Standards
*   **Language**: C++14.
*   **Build System**: Meson. Update `meson.build` when adding files.
*   **Style**: Snake_case variables, CamelCase classes.
*   **Settings**: Use `UserSetting` class (GSettings wrapper). Schema in `extra/`.

## Workflow
1.  **Analyze**: Deeply understand requirements and existing code.
2.  **Plan**: Create a step-by-step plan.
3.  **Implement**: Write robust, tested code.
4.  **Verify**: Ensure compilation and functionality.
5.  **Document**: Update all relevant markdown files.
6.  **Submodules**: Ensure `pianogame` (and others) are synced and documented.

## Submodules
*   `pianogame`: Original Synthesia source. Reference for missing features.
*   **Protocol**: Always update submodules and merge upstream changes.

## Model-Specific Notes
*   **Claude**: Focus on detailed C++ logic and architecture.
*   **Gemini**: Good for broad analysis and documentation.
*   **ChatGPT**: effective for generating boilerplate and refactoring.
*   **Jules**: The primary driver. Execute long-running tasks and deep integration.
