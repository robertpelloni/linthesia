# Outstanding Issues & Short-Term Goals

- [ ] Complete GTKmm Rendering Transition (Phase 1): Abstrace `TextWriter.cpp` to use Cairo/Pango for text rendering instead of `SDL_ttf`, outputting to OpenGL textures, preparing for the `Gtk::GLArea` swap.
- [ ] Investigate FluidSynth: `libfluidsynth-dev` is missing from the environment. `FluidSynthMidiDriver` exists as a placeholder. We need to install the package or link to a local static build.
- [ ] Investigate AppImage/Flatpak: Provide a native Linux bundle.
- [x] Add Doxygen: Add Doxygen support to `meson.build` and document all C++ headers to automatically generate `docs/api`.
