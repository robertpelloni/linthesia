# Roadmap for Linthesia

This document outlines the planned features, improvements, and known gaps in Linthesia compared to its predecessor (Synthesia 0.6.1a) and modern piano learning software.

## Current Status (v0.8.0)
Linthesia is a fully functional MIDI visualizer and learning tool for Linux. It supports playing MIDI files, configuring tracks (play, mute, learn), and basic customization.

### Recently Completed
*   **Settings Menu**: Configurable Lead-In, Lead-Out, Scroll Speed, Metronome.
*   **Documentation**: Comprehensive User Manual (`README.md`), Developer Guide (`AGENTS.md`), and Vision (`VISION.md`).
*   **UI Polish**: In-Game Help Overlay, Visual Metronome, Volume Control Fix.
*   **Versioning**: Consolidated version management via `VERSION` file.

## Upcoming Features

### Short Term (v0.9.0)
*   **[ ] Metronome Audio**: Add audible "tick" sound synchronized with the visual metronome.
*   **[ ] Keyboard Size Support**: Fully implement rendering logic for 61-key and 76-key keyboards (currently placeholders in `KeyboardDisplay.cpp`).
*   **[ ] Pause Menu**: Enhance the pause overlay with interactive buttons (Resume, Restart, Quit) instead of just text.

### Medium Term (v1.0.0)
*   **[ ] Loop Practice**: Allow users to select a section of the song (A-B repeat) to practice repeatedly.
*   **[ ] Wait Mode Polish**: Improve the "Learning" mode where the song pauses until the correct note is hit. Ensure it handles chords and fast passages gracefully.
*   **[ ] Scoring System**: Implement a scoring algorithm based on timing accuracy (Perfect, Good, Miss) and display results at the end of a song.

### Long Term
*   **[ ] Built-in Synthesizer**: Integrate FluidSynth or a similar library to generate audio directly, removing the dependency on external MIDI synths.
*   **[ ] Cross-Platform Support**: Abstract ALSA dependencies to support Windows and macOS.
*   **[ ] Sheet Music View**: Option to display standard musical notation alongside or instead of falling notes.
*   **[ ] MIDI Recording**: Allow users to record their performance and save it as a MIDI file.

## Submodule Analysis: `pianogame`
The `pianogame` submodule contains the original source code for Synthesia 0.6.1a.

### Missing Features / TODOs from `pianogame`
*   **Unicode Support**: Multiple TODOs in `libmidi` about lack of Unicode support for filenames.
*   **Keyboard Layouts**: Hardcoded TODOs in `KeyboardDisplay.cpp` for 61/76 key start octaves.
*   **Fade Effects**: `State_Playing.cpp` mentions "The fade effect is way cooler" (MACTODO), suggesting graphical polish missing in the Linux port.
*   **Resource Management**: TODOs about deleting textures/fonts at shutdown in `TextWriter.cpp`.

## Contribution
Please refer to `AGENTS.md` for instructions on how to contribute to these tasks.
