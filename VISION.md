# Vision for Linthesia

Linthesia aims to be the premier open-source piano learning and MIDI visualization tool for Linux and beyond. It is built on the legacy of Synthesia (version 0.6.1a) but modernized with features, stability, and extensibility in mind.

## Core Philosophy

1.  **Accessibility**: Easy to install, configure, and use. No complex setup or proprietary drivers required.
2.  **Openness**: Fully open-source (GPLv2/MIT), encouraging community contributions and modifications.
3.  **Visual Learning**: Leveraging the intuitive "falling notes" interface (Piano Hero style) to make music theory and practice accessible to beginners.
4.  **Hardware Agnostic**: Compatible with any MIDI keyboard (via ALSA) and any standard MIDI file.
5.  **Configurability**: Exposing granular control over gameplay (speed, lead-in/out, metronome) to suit learners at different stages.

## Long-Term Goals

*   **Platform Independence**: While currently Linux-focused (ALSA), future versions should abstract MIDI and Audio layers to support Windows (WinMM/WASAPI) and macOS (CoreMIDI/CoreAudio) natively.
*   **Enhanced Learning Modes**: Implementing "Wait Mode" (already partially supported), "Loop Practice" (looping sections), and "Sight Reading" (standard notation view).
*   **Audio Synthesis**: Integrating a built-in synthesizer (e.g., FluidSynth) so users don't need external software to hear sound.
*   **Community Library**: Integration with online repositories of public domain MIDI files or user-generated content.
*   **Gamification**: Scoring, streaks, and progress tracking to motivate practice.

## Design Principles

*   **Modular Codebase**: Separation of MIDI handling (`libmidi`), Game Logic (`GameState`), and Rendering (`Renderer`).
*   **Resource Efficiency**: Minimal CPU/GPU usage to run on low-end hardware (Raspberry Pi, old laptops).
*   **Clean UI**: Focus on the music. Minimal distractions during gameplay. informative menus and tooltips.

## Current Focus
*   Polishing the UI/UX (Settings, Help, Navigation).
*   Completing missing features from the original Synthesia codebase.
*   Documenting the codebase for future contributors.
