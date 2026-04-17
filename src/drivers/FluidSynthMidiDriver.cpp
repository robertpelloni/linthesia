// -*- mode: c++; coding: utf-8 -*-
// Linthesia

#include "FluidSynthMidiDriver.h"
#include <iostream>

using namespace std;

FluidSynthMidiDriver::FluidSynthMidiDriver() : m_is_open(false) {
#ifdef USE_FLUIDSYNTH
  m_settings = new_fluid_settings();
  m_synth = new_fluid_synth(m_settings);
  // Example soundfont path, should be configurable via UserSettings
  m_soundfont_path = "/usr/share/sounds/sf2/FluidR3_GM.sf2";
  fluid_synth_sfload(m_synth, m_soundfont_path.c_str(), 1);
  m_adriver = new_fluid_audio_driver(m_settings, m_synth);
#endif
}

FluidSynthMidiDriver::~FluidSynthMidiDriver() {
#ifdef USE_FLUIDSYNTH
  if (m_adriver) delete_fluid_audio_driver(m_adriver);
  if (m_synth) delete_fluid_synth(m_synth);
  if (m_settings) delete_fluid_settings(m_settings);
#endif
}

std::vector<std::string> FluidSynthMidiDriver::GetOutputPorts() {
  std::vector<std::string> ports;
#ifdef USE_FLUIDSYNTH
  ports.push_back("Built-in FluidSynth Synthesizer");
#endif
  return ports;
}

std::vector<std::string> FluidSynthMidiDriver::GetInputPorts() {
  // Software synths typically don't have inputs
  return std::vector<std::string>();
}

void FluidSynthMidiDriver::OpenOutput(const std::string& portName) {
  (void)portName;
#ifdef USE_FLUIDSYNTH
  m_is_open = true;
  cout << "FluidSynth Output Opened." << endl;
#else
  cerr << "FluidSynth support not compiled." << endl;
#endif
}

void FluidSynthMidiDriver::OpenInput(const std::string& portName) {
  (void)portName;
}

void FluidSynthMidiDriver::Write(const std::vector<unsigned char>& message) {
  if (message.empty() || !m_is_open) return;

#ifdef USE_FLUIDSYNTH
  unsigned char status = message[0] & 0xF0;
  unsigned char channel = message[0] & 0x0F;

  if (status == 0x90 && message.size() >= 3) {
      if (message[2] == 0) {
          fluid_synth_noteoff(m_synth, channel, message[1]);
      } else {
          fluid_synth_noteon(m_synth, channel, message[1], message[2]);
      }
  } else if (status == 0x80 && message.size() >= 3) {
      fluid_synth_noteoff(m_synth, channel, message[1]);
  } else if (status == 0xB0 && message.size() >= 3) {
      fluid_synth_cc(m_synth, channel, message[1], message[2]);
  } else if (status == 0xC0 && message.size() >= 2) {
      fluid_synth_program_change(m_synth, channel, message[1]);
  } else if (status == 0xE0 && message.size() >= 3) {
      int pitch = (message[1] & 0x7F) | ((message[2] & 0x7F) << 7);
      fluid_synth_pitch_bend(m_synth, channel, pitch);
  }
#endif
}
