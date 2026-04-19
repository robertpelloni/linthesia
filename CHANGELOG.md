# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.9.9] - 2026-04-18
### Added
- **README Standardization**: Re-wrote `README.md` to be an extremely comprehensive user manual and development guide with explicit dependency instructions and feature overviews.
- **Changelog Standardization**: Converted `CHANGELOG.md` to strictly follow the Keep a Changelog standard format.

## [0.9.8] - 2026-04-18
### Added
- **Massive Brainstorming & Analysis**: Conducted extreme in-depth analysis of the project and established `IDEAS.md`, providing innovative structural refactoring (WASM, ImGui), sophisticated game modes (Multiplayer, RPG, Audio routing), and AI integration (MediaPipe hand tracking, Generative accompaniment) concepts for the future roadmap.

## [0.9.7] - 2026-04-16
### Added
- **Omniscient Orchestration**: Implemented Phase 4 capabilities via `workspace_indexer.py` (building an SQLite FTS5 database of all source files, including `.js`, `.ts`, and `.tsx`) and `search_api.py` (FastMCP integration) to quickly search massive codebases.

## [0.9.6] - 2026-04-16
### Added
- **Workspace Verification Script**: Added `build_all.py` to recursively discover and test C++, Node.js, and Python projects to validate stability across the monorepo and its submodules.

## [0.9.5] - 2026-04-16
### Added
- **FluidSynth Integration**: Implemented a placeholder `FluidSynthMidiDriver` guarded by `#ifdef USE_FLUIDSYNTH` to support built-in audio parsing on systems equipped with the library.
- **Cross-Platform Support**: Added `docs/CROSS_PLATFORM.md` containing detailed requirements and architectures for Windows (MSYS2) and macOS (Homebrew) builds.

## [0.9.4] - 2026-04-16
### Added
- **Documentation & Testing**: Extensive README overhauls, `.clang-format`, `.clang-tidy`, a `Makefile`, and `gtest` framework integration with basic core audio tests.
- **Module Docs**: Added architecture references for Graphics and Audio components in the `docs/` folder.

## [0.9.3] - 2026-04-15
### Added
- **UI/UX Polish**: Upgraded tooltip verbosity across Settings and Track Selection screens for improved clarity. Added in-game Pause menu controls legend.
- **Sight Reading**: Implemented `SheetMusicDisplay` for standard Grand Staff notation toggled via F7.
- **Wait Mode Grace Period**: Added a wait tolerance logic to the Learning Mode (Wait Mode) with the `WAIT_TOLERANCE_KEY` to allow grace periods for rolled chords and non-quantized MIDI notes.
- **Scoring System**: Perfect, Good, Miss, and Streak combos and popup indicators.

## [0.9.1] - 2026-04-12
### Added
- **Song Library Search**: Added text-based search functionality to the Song Library screen. Users can now type characters to filter the currently displayed list of MIDI files and directories. Backspace works.

### Fixed
- Fixed critical syntax and logic regressions introduced in the previous mass-replace process across `PlayingState.cpp`, `main.cpp`, and `FileSelector.cpp`.
- Resolved merge conflict markers and successfully migrated the Github Actions CI workflow to use `actions/checkout@v4` with the necessary `libgtkmm-3.0-dev` dependency for Pango rendering contexts.

## [0.9.0] - Prior Work
### Added
- Basic state management transitions.
- Preliminary GTKmm/Pango graphics backend transition setup.
- Custom `Color` structure to replace `SDL_Color` for better cross-compatibility.
