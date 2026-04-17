// -*- mode: c++; coding: utf-8 -*-
// Linthesia

#ifndef __FLUIDSYNTH_MIDI_DRIVER_H
#define __FLUIDSYNTH_MIDI_DRIVER_H

#include "MidiDriver.h"
#include <string>
#include <vector>
#include <stdexcept>

// Since libfluidsynth-dev is not available in the current CI/CD or build environment,
// this driver serves as a placeholder interface that can be conditionally
// compiled and swapped out at runtime.

#ifdef USE_FLUIDSYNTH
#include <fluidsynth.h>
#endif

class FluidSynthMidiDriver : public MidiDriver {
public:
  FluidSynthMidiDriver();
  virtual ~FluidSynthMidiDriver();

  virtual std::vector<std::string> GetOutputPorts() override;
  virtual std::vector<std::string> GetInputPorts() override;

  virtual void OpenOutput(const std::string& portName) override;
  virtual void OpenInput(const std::string& portName) override;
  virtual void Write(const std::vector<unsigned char>& message) override;

private:
#ifdef USE_FLUIDSYNTH
  fluid_settings_t* m_settings;
  fluid_synth_t* m_synth;
  fluid_audio_driver_t* m_adriver;
#endif
  bool m_is_open;
  std::string m_soundfont_path;
};

#endif // __FLUIDSYNTH_MIDI_DRIVER_H
