# Audio Module Documentation

The Audio module in Linthesia handles all MIDI input and output operations, translating internal `MidiEvent` structures into hardware-specific API calls. It ensures low-latency playback, recording, and visualization synchronization.

## Architecture

The module follows an interface-driven design to allow for cross-platform expansion and flexible driver selection (e.g., ALSA on Linux, CoreMIDI on macOS, Windows Multimedia API).

### Core Components

#### 1. `MidiDriver` Interface (`src/MidiDriver.h`)
The abstract base class defining the contract for all MIDI backend implementations.
*   **Key Responsibilities**:
    *   Initialize and clean up MIDI devices.
    *   Enumerate available input and output ports.
    *   Open and close connections to specific ports.
    *   Send and receive raw MIDI bytes.
*   **API Methods**:
    *   `virtual std::vector<std::string> GetOutputPorts() = 0;`
    *   `virtual std::vector<std::string> GetInputPorts() = 0;`
    *   `virtual void OpenOutput(const std::string& portName) = 0;`
    *   `virtual void OpenInput(const std::string& portName) = 0;`
    *   `virtual void Write(const std::vector<unsigned char>& message) = 0;`

#### 2. `AlsaMidiDriver` (`src/drivers/AlsaMidiDriver.h/cpp`)
The concrete implementation of `MidiDriver` for GNU/Linux systems using the ALSA Sequencer API.
*   **Key Responsibilities**:
    *   Wraps `snd_seq_t` ALSA structures.
    *   Subscribes to ALSA input events and buffers them.
    *   Translates generic `Write` commands into `snd_seq_event_t` messages and flushes them to the ALSA queue.

#### 3. `MidiComm` (`src/MidiComm.h/cpp`)
The high-level manager that acts as the bridge between the game logic (`GameStateManager`, `PlayingState`) and the underlying `MidiDriver`.
*   **Key Responsibilities**:
    *   Manages the global `g_midi_driver` instance.
    *   Translates internal `MidiEvent` objects into byte vectors to be consumed by `MidiDriver::Write()`.
    *   Polls for incoming MIDI data from physical keyboards and translates them into `MidiEvent` objects to be consumed by the game loop.
    *   Handles PC Keyboard audio injection (simulating MIDI input via QWERTY presses).

## Data Flow
1.  **Playback (Output)**:
    `PlayingState` calculates the next `MidiEvent` based on the active song's timestamp -> Calls `MidiComm::WriteEvent(ev)` -> `MidiComm` serializes the event into bytes -> Calls `g_midi_driver->Write(bytes)` -> `AlsaMidiDriver` sends the bytes to the ALSA sequencer.
2.  **Recording (Input)**:
    Hardware MIDI Keyboard pressed -> ALSA receives event -> `AlsaMidiDriver` buffers the event -> `MidiComm::Poll()` retrieves the byte vector and constructs a `MidiEvent` -> `PlayingState` processes the event for scoring or playback.

## Adding a New Driver
To add a new audio backend (e.g., `FluidSynthMidiDriver`):
1.  Create a class inheriting from `MidiDriver`.
2.  Implement all pure virtual methods.
3.  In `MidiComm` (or a dedicated factory class), instantiate the new driver and assign it to `g_midi_driver` based on configuration or compilation flags.
