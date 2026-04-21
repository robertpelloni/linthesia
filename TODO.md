# Outstanding Issues & Short-Term Goals

- [ ] Complete GTKmm Rendering Transition: The transition from SDL2 to GTKmm/Pango is incomplete. `Renderer` objects currently rely on dummy `GLContext()` and `PGContext()` structs. Integrate native event loops.
- [ ] Investigate FluidSynth: `libfluidsynth-dev` is missing from the environment. `FluidSynthMidiDriver` exists as a placeholder. We need to install the package or link to a local static build.
- [ ] Investigate AppImage/Flatpak: Provide a native Linux bundle.
- [x] Add Doxygen: Add Doxygen support to `meson.build` and document all C++ headers to automatically generate `docs/api`.
- [ ] Cross-Platform Audio Backends: Implement WinMM (Windows) and CoreMIDI (macOS) wrappers within `src/drivers/`.
- [ ] Comprehensive Unit Testing: Expand `tests/` coverage past basic placeholder audio tests to cover `libmidi` parsing logic.
