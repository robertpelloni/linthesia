# Changelog

## [1.5.0-dev] - 2024-05-22

### Added
- **Sheet Music Phase 2**: Implemented advanced notation features:
    - **Beams**: Short notes (8th notes and smaller) are now visually grouped with beams.
    - **Stems**: Notes now have stems with correct direction (up/down) based on pitch.
    - **Key Signatures**: Key signatures are parsed from the MIDI file and rendered at the start of the staff.
    - **Clef Symbol**: A stylized Treble Clef is drawn at the start of the staff.
- **Persistence Fixes**: Fixed database path resolution to correctly save scores to `~/.local/share/linthesia/scores.db` on Linux.

## [1.4.0-dev] - 2024-05-22

### Added
- **Sheet Music Polish**: Added measure lines (bar lines) and ledger lines to the sheet music view, significantly improving readability.
- **Particle Effects**: Added a particle system that spawns colorful sparks when notes are hit, adding visual "juice" to the gameplay.

## [1.3.0] - 2024-05-22

### Added
- **Sheet Music View**: Press `F7` during gameplay to toggle between the classic "Falling Notes" view and a new "Sheet Music" view (basic treble clef rendering).
- **Scoring Polish**: "Good" and "Ok" hit ratings now indicate whether the hit was (Early) or (Late).

## [1.2.1] - 2024-05-22

### Added
- **Configurable Wait Tolerance**: Added a "Wait Tolerance" setting to the Advanced Settings menu.
- **Audio Test**: Added a "Test Audio" button in Settings.
- **Search UI**: Improved the song library search bar.

### Changed
- **Polish**: Fixed PC keyboard audio regression.
