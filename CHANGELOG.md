# Changelog

## [1.1.0] - 2024-05-22

### Added
- **Score Persistence**: Implemented a local SQLite database to save song scores, grades, and streaks.
- **Library Assessment**: The Song Library now displays your best score and grade for each song directly on the tile.
- **MidiDriver**: Created `AlsaMidiDriver` class as part of the cross-platform refactoring effort.
- **Advanced Scoring**: Added Streak tracking with visual popups (every 10 hits) and "S"/"SS" ranks for high accuracy.

## [1.0.0] - 2024-05-22

### Added
- **Song Search**: Users can now type to search for songs in the library. Added Backspace support for text editing.
- **Wait Mode Tolerance**: "Learning" mode now has a 50ms grace period to handle "rolled" chords or sloppy MIDI files without stuttering.
- **SDL Text Input**: Integrated SDL2 text input event handling into the game engine.

### Changed
- **Version**: Bumped to 1.0.0, marking feature completeness for the core Linux scope.
- **Documentation**: Updated Roadmap to reflect 1.0 status.

## [0.9.0] - 2024-05-22

### Added
- **Loop Practice**: Press `F1` to set start point (A), `F2` to set end point (B). The song will loop between these points. Press `F6` to toggle looping.
- **Interactive Pause Menu**: The pause screen now features clickable buttons to "Resume" or "Quit to Title".
- **Agent Instructions**: Added `AGENTS.md` and related files to guide AI contributors.

### Changed
- **Documentation**: Updated `ROADMAP.md` and `DASHBOARD.md`.
- **Internal**: Verified keyboard size rendering logic.

## [0.8.0] - 2024-05-22

### Added
- **Settings Menu**: New "Advanced Settings" menu in the title screen.
- **In-Game Help**: Pressing 'Space' to pause now displays a help overlay.
- **Visual & Audio Metronome**: A yellow indicator flashes and a MIDI tick plays on every beat.
- **Version Consolidation**: Project version is now read from a single `VERSION` file.

### Changed
- **Volume Controls**: Swapped Keypad `+` and `-` mappings.
- **Documentation**: Rewrote `README.md` as a user manual.
