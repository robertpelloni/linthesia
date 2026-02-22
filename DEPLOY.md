# Deployment Instructions

## Build Dependencies (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    libasound2-dev \
    libgl1-mesa-dev \
    libglibmm-2.4-dev \
    libsqlite3-dev \
    libsdl2-dev \
    libsdl2-ttf-dev \
    libsdl2-image-dev \
    gettext \
    meson \
    ninja-build
```

## Build Process

1.  **Configure**:
    ```bash
    meson setup build
    ```

2.  **Compile**:
    ```bash
    meson compile -C build
    ```

3.  **Run**:
    ```bash
    ./build/src/linthesia
    ```

4.  **Install (Optional)**:
    ```bash
    sudo meson install -C build
    ```

## Runtime Requirements
*   A MIDI Synthesizer (e.g., QSynth, Timidity++, or Hardware Synth) is required for sound output unless the built-in FluidSynth driver is enabled (Future).
*   Connect MIDI keyboard via USB/MIDI.
*   Use `aconnect` or `qjackctl` to route MIDI if necessary, though Linthesia attempts to auto-connect.
