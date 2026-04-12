# Linthesia

![Build Status](https://github.com/linthesia/linthesia/actions/workflows/c-cpp.yml/badge.svg)

Linthesia is a fork of the game called Synthesia. It is a game of playing music using a MIDI keyboard (or your PC keyboard), following a MIDI file. It provides a "Piano Hero" style interface where notes fall from the top of the screen to the keys.

This project uses the latest source from sourceforge (Synthesia 0.6.1a) and modernizes it for Linux systems.

## Installation

### Dependencies
To compile, you need a basic C++ toolchain and the following dependencies:
*   alsa-lib
*   gtkmm-3.0 (for glib-compile-schemas)
*   sdl2
*   sdl2-image
*   sdl2-ttf
*   sqlite3
*   meson & ninja

### Build
    $ meson --prefix /usr build
    $ ninja -C build
    $ sudo ninja -C build install

## Getting Started

1.  Run `linthesia` from your terminal or application menu.
2.  **First Run**: The game will look for MIDI files. You can place your `.mid` files in your home directory or select a folder in the game.
3.  **Main Menu**:
    *   **Song Title**: Click to choose a MIDI file.
    *   **Output Device**: Select your MIDI synthesizer (e.g., Fluidsynth, Timidity, or a hardware synth). Click the button to cycle through devices. Click the small "Play" icon to test sound.
    *   **Input Device**: Select your MIDI keyboard. If you don't have one, you can just watch the song play.
    *   **Keyboard Size**: Choose between 88, 76, 61, 49, or 37 keys to match your instrument.
    *   **Advanced Settings**: Configure gameplay preferences (Lead-in time, Scroll speed, Metronome).

## Features & Configuration

### Advanced Settings
Click "Advanced Settings" on the title screen to configure:
*   **Lead-In Time**: How long to wait before the song starts (default 5.5s).
*   **Lead-Out Time**: How long to wait after the song ends.
*   **Visible Duration**: Controls the scroll speed (how much of the song is visible at once). Lower values mean faster scrolling.
*   **Metronome**: Enable a visual metronome that flashes on the beat.
*   **Metronome Volume**: (Planned) Adjust volume of metronome tick.

### Track Selection
After choosing a song, you will see the Track Selection screen.
*   **Mode**: Click the icon next to a track to change its mode:
    *   **Played Automatically**: The game plays this track.
    *   **You Play**: You are expected to play this track. Notes will wait for you in "Learning" mode.
    *   **Learning**: The game pauses until you hit the correct note.
    *   **Not Played**: The track is muted and hidden.
*   **Color**: Click the color square to change the track color.
*   **Preview**: Click the speaker icon to hear the track.

## Controls

### In-Game Keys
| Key | Action |
| :--- | :--- |
| **Space** | Pause / Resume Game |
| **Esc** | Return to Menu |
| **Left / Right** | Adjust Playback Speed (-/+ 10%) |
| **Up / Down** | Adjust Zoom (Visible Duration) |
| **Keypad +** | Volume Up |
| **Keypad -** | Volume Down |
| **< / >** | Octave Shift Down / Up |
| **Page Up** | Jump Backward 5s |
| **Page Down** | Jump Forward 5s |
| **F6** | Toggle FPS Display |

### Help Overlay
When the game is paused, a help overlay will appear listing these controls.

## Troubleshooting

### No Sound?
Linthesia produces MIDI events, not audio. You need a MIDI synthesizer software running to hear sound.
*   **Fluidsynth**: `fluidsynth -a alsa -m alsa_seq /usr/share/sounds/sf2/FluidR3_GM.sf2`
*   **Timidity++**: Run as a daemon `timidity -iA`.

Once the synth is running, select it as the **Output Device** in Linthesia.

## Credits
Based on Synthesia by Nicholas Piegdon.
Linux port and improvements by the Linthesia team.
