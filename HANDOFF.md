# Handoff Note

**To:** Next AI Agent (Claude, Gemini, or Jules)
**From:** Jules
**Date:** 2024-05-22
**Version:** 1.11.0-dev

## Current Status
Linthesia is polished, secure, and feature-rich.

### Accomplishments
1.  **PC Keyboard Layouts**: Added QWERTY/AZERTY/QWERTZ support via `KeyMapper` class and Settings UI.
2.  **Lighted Keys**: Hardware support via "Guide Notes".
3.  **PC Gameplay**: Direct key injection.
4.  **Security**: Patched `main.cpp`.
5.  **Visuals**: Menu animations, Title particles.
6.  **Sheet Music**: Grand Staff, Accidentals.

### Known Issues
*   **FluidSynth**: Blocked by environment.
*   **Input Mapping**: "Custom" layout not yet implemented (requires UI).

## Next Steps (Priorities)
1.  **Custom Key Mapping**: UI to let users press keys to map notes.
2.  **Performance**: Texture caching for Sheet Music?
3.  **Cross-Platform**: Windows port.

## Useful Commands
*   **Build**: `meson compile -C build`
*   **Run**: `./build/src/linthesia`
*   **Docs**: Read `AGENTS.md` first.
