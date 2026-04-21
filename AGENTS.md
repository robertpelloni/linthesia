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
    *   Maintain `docs/ARCHITECTURE.md` as the high-level system mapping.
    *   `Doxyfile` handles auto-generating C++ API docs.
4.  **Versioning**:
    *   **Single Source of Truth**: The `VERSION` file in the root directory.
    *   **Protocol**: Update `VERSION` and `CHANGELOG.md` with every significant feature set or build.
    *   **Commit Message**: "Bump version to X.Y.Z" when updating version.

## Codebase Standards
*   **Language**: C++14.
*   **Build System**: Meson + Ninja.
*   **Style**: Snake_case variables, CamelCase classes.
*   **Settings**: Use `UserSetting` class (GSettings wrapper). Schema in `extra/`.

## Workflow
1.  **Analyze**: Deeply understand requirements and existing code. Use the `scripts/workspace_indexer.py` (via FastMCP search) to rapidly locate dependencies across the 100+ modules.
2.  **Plan**: Create a step-by-step plan.
3.  **Implement**: Write robust, tested code. Ensure `tests/` are updated.
4.  **Verify**: Ensure compilation (`meson setup build`, `ninja -C build`) and functionality (`make test` or `build_all.py`).
5.  **Document**: Update all relevant markdown files. Run `update_docs.sh` to refresh the FTS5 SQLite index.
6.  **Submodules**: Ensure `pianogame` (and others) are synced and documented.

## Submodules
*   `pianogame`: Original Synthesia source. Reference for missing features.
*   **Protocol**: Always update submodules and merge upstream changes.

## Model-Specific Notes
*   **Claude**: Focus on detailed C++ logic, GTKmm rendering targets, and audio architectures.
*   **Gemini**: Broad analysis, documentation synthesis, and ideation (see `IDEAS.md`).
*   **ChatGPT**: Effective for generating boilerplate, tests (`gtest`), and refactoring repetitive code.
*   **Jules**: The primary driver. Execute long-running tasks (FTS5 indexing) and deep integration.
