// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#ifndef __MIDI_DRIVER_H
#define __MIDI_DRIVER_H

#include <vector>
#include <string>
#include "libmidi/MidiEvent.h"

struct MidiDeviceInfo {
  unsigned int id;
  std::string name;
  int client; // ALSA specific
  int port;   // ALSA specific
};

class MidiDriver {
public:
  virtual ~MidiDriver() {}

  virtual std::vector<MidiDeviceInfo> GetInputDevices() = 0;
  virtual std::vector<MidiDeviceInfo> GetOutputDevices() = 0;

  virtual void OpenInput(unsigned int device_id) = 0;
  virtual void CloseInput() = 0;
  virtual MidiEvent Read() = 0;
  virtual bool HasInput() = 0;

  virtual void OpenOutput(unsigned int device_id) = 0;
  virtual void CloseOutput() = 0;
  virtual void Write(const MidiEvent &ev) = 0;
};

#endif // __MIDI_DRIVER_H
