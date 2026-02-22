# Changelog

## [1.7.0-dev] - 2024-05-22

### Added
- **Note Labels**: Added a setting to display note names (C, D#, etc.) on falling notes to assist learning.
- **Wait Mode Indicator**: Visual "Waiting..." overlay when the game pauses for input in Learning Mode.
- **Documentation**: Comprehensive overhaul of `AGENTS.md`, `VISION.md`, and project documentation structure.

## [1.6.0-dev] - 2024-05-22

### Added
- **Sheet Music Phase 3**: Complete notation overhaul:
    - **Grand Staff**: Now renders both Treble and Bass staves.
    - **Auto-Clef**: Tracks are automatically assigned to Treble or Bass clef based on pitch range.
    - **Accidentals**: Sharp (#), Flat (b), and Natural (n) symbols are drawn for notes deviating from the key signature.
    - **Bass Clef**: Added procedural rendering for the F-Clef.
- **Sheet Music Phase 2**:
    - **Beams**: Rhythm grouping for 8th notes.
    - **Stems**: Directional stems.
    - **Key Signatures**: Full parsing and rendering.
- **Persistence**: Fixed score saving on Linux.

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
