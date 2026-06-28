# WebAssembly Compatibility Analysis

To achieve a seamless WASM port of Linthesia, the following structural dependencies must be addressed:

1. **ALSA / CoreMIDI Removal:**
   - The engine relies on `MidiComm.cpp` which utilizes `alsa/asoundlib.h`. Emscripten does not support ALSA natively.
   - We need to implement a Web MIDI API backend using `EM_ASM` macros within a new `WebMidiDriver.cpp` inside `src/drivers/`.

2. **SDL2 and GL Context:**
   - The main loop uses `SDL2`. Emscripten provides built-in SDL2 ports via `-s USE_SDL=2`.
   - The GL Context initialization must ensure WebGL compatibility (GLES2), which typically means avoiding deprecated immediate mode OpenGL calls. We are currently migrating to GTKmm/Pango, which uses Cairo -> OpenGL textures.

3. **Multithreading:**
   - Linthesia uses `std::thread` and `DpmsThread.cpp` for power management and asynchronous operations.
   - Emscripten supports pthreads, but it requires `SharedArrayBuffer` headers (`COOP`/`COEP`), complicating standard HTTP deployment. We may need a single-threaded fallback for the web build.

4. **File System (`music/` library):**
   - Emscripten's virtual file system (`FS`) will be required to preload MIDI files or read them dynamically from user uploads (using HTML5 `<input type="file">`).

5. **Build System (Meson):**
   - Meson requires a cross-compilation file to use `emcc` and `em++`. `dependency('alsa')` and `dependency('gtkmm-3.0')` must be conditionally excluded when building for `host_machine.system() == 'emscripten'`.
