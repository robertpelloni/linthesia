# Handoff Note

**To:** Next AI Agent (Claude, Gemini, or Jules)
**From:** Jules
**Date:** 2024-05-22
**Version:** 1.7.0-dev

## Current Status
We have successfully implemented major feature sets for Linthesia, transforming it into a robust piano learning tool.

### Accomplishments
1.  **Documentation Overhaul**: `AGENTS.md` is now the master instruction file. `VISION.md`, `ROADMAP.md`, `DASHBOARD.md` are up to date.
2.  **Sheet Music Phase 3**:
    *   Grand Staff rendering (Treble + Bass).
    *   Auto-Clef detection.
    *   Key Signature parsing and rendering.
    *   Accidentals rendering.
    *   Procedural Clef symbols.
    *   Beams and Stems.
3.  **UI/UX Features**:
    *   **Note Labels**: Option to show "C", "D#" on falling notes.
    *   **Wait Mode Indicator**: Visual "Waiting..." text when user is blocked.
    *   **Search**: Fully functional with text input.
    *   **Settings**: Comprehensive menu with toggles for new features.
4.  **Persistence**: Fixed SQLite database path logic.

### Known Issues
*   **FluidSynth**: Not implemented due to missing `libfluidsynth-dev` in the environment.
*   **Text Rendering**: We use `SDL_ttf` with `FreeSans.ttf`. Some special chars (flat symbol `b`) are approximated.
*   **Performance**: `SheetMusicDisplay` redraws everything every frame. Optimization might be needed later (display lists or texture caching).

## Next Steps (Priorities)
1.  **FluidSynth**: If the environment allows, implement the driver.
2.  **Cross-Platform**: Abstract filesystem paths further for Windows/macOS.
3.  **Visual Polish**: Add animations to the menus.
4.  **Input Mapping**: Add UI to remap keys (currently hardcoded or partial).

## Useful Commands
*   **Build**: `meson compile -C build`
*   **Run**: `./build/src/linthesia`
*   **Docs**: Read `AGENTS.md` first.
