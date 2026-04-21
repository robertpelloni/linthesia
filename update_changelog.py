import sys
with open('CHANGELOG.md', 'r') as f:
    content = f.read()

new_entry = """## [0.10.4] - 2026-04-20
### Added
- **FluidSynth Integration**: Installed `libfluidsynth-dev` and finalized the `FluidSynthMidiDriver`. Linthesia can now synthesize audio internally without requiring ALSA sequencers or external software like Timidity++.

"""

content = content.replace("## [0.10.3] - 2026-04-20", new_entry + "## [0.10.3] - 2026-04-20")
with open('CHANGELOG.md', 'w') as f:
    f.write(content)
