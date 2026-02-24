# Project Dashboard

## Structure
*   **Root**: Configuration and Documentation.
*   `src/`: Source Code (C++).
    *   `libmidi/`: MIDI file parsing library.
    *   `drivers/`: MIDI hardware abstraction implementations.
*   `graphics/`: Image assets and Fonts.
*   `music/`: Example MIDI files.
*   `extra/`: GSettings schema and desktop files.
*   `po/`: Localization.

## Submodules
*   `pianogame`:
    *   **Location**: `pianogame/`
    *   **Description**: Original Synthesia 0.6.1a source code. Used as a reference.
    *   **Status**: Frozen (Reference only).

## Current Status (v1.9.0-dev)
*   **Build System**: Meson.
*   **Core**: Functional.
*   **Features**:
    *   Falling Notes: [x] (with Note Labels)
    *   Sheet Music: [x] (Phase 3: Grand Staff, Bass Clef)
    *   Persistence: [x] (SQLite)
    *   Search: [x]
    *   Particles: [x]
    *   Wait Mode: [x] (with Indicator)
    *   Visuals: [x] (Menu Animations)
    *   Input: [x] (PC Keyboard Gameplay)
*   **Missing**:
    *   FluidSynth Integration.
    *   Windows/macOS Drivers.

## Recent Activity
*   **v1.9.0-dev**: PC Keyboard Gameplay Injection.
*   **v1.8.0-dev**: Security Patch, Menu Animations.
*   **v1.7.0-dev**: Note Labels, Wait Mode Indicator, Documentation Overhaul.
*   **v1.6.0-dev**: Implemented Grand Staff, Bass Clef, Accidentals.
*   **v1.5.0-dev**: Implemented Beams, Stems, Key Signatures.
*   **v1.4.0-dev**: Particles, Polish.
