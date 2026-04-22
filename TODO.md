# Outstanding Issues & Short-Term Goals

- [ ] Complete GTKmm Rendering Transition (Phase 1): Abstract `TextWriter.cpp` to use Cairo/Pango for text rendering instead of `SDL_ttf`, outputting to OpenGL textures, preparing for the `Gtk::GLArea` swap.
- [ ] Cross-Platform Audio Backends: Implement WinMM (Windows) and CoreMIDI (macOS) wrappers within `src/drivers/`.
- [ ] Investigate AppImage/Flatpak: Provide a native Linux bundle.
