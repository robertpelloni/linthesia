# Handoff Note

**To:** Next AI Agent (Claude, Gemini, or Jules)
**From:** Jules
**Date:** 2024-05-22
**Version:** 1.10.0-dev

## Current Status
Linthesia is now a feature-complete piano learning application with advanced notation, hardware support, and polished visuals.

### Accomplishments
1.  **Lighted Keys Support**: Added "Guide Notes" feature to send MIDI events to output devices even for muted tracks, enabling hardware lighted keys.
2.  **PC Keyboard Gameplay**: Users can play without a MIDI keyboard.
3.  **Visual Polish**: Menu transitions, Title Screen particles, Note Labels, Wait Indicator.
4.  **Sheet Music Phase 3**: Grand Staff, Bass Clef, Accidentals.
5.  **Documentation**: Comprehensive instructions in `AGENTS.md`.

### Known Issues
*   **FluidSynth**: Not implemented due to missing `libfluidsynth-dev`.
*   **Input Mapping**: Hardcoded QWERTY.
*   **Text Rendering**: Basic `SDL_ttf`.

## Next Steps (Priorities)
1.  **Input Mapping UI**: Allow users to remap PC keys.
2.  **Performance Optimization**: Profile rendering loop.
3.  **Cross-Platform**: Test/Implement Windows support.

## Useful Commands
*   **Build**: `meson compile -C build`
*   **Run**: `./build/src/linthesia`
*   **Docs**: Read `AGENTS.md` first.
