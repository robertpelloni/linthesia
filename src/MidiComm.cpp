// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#include <string>
#include <sstream>

#include "libmidi/MidiEvent.h"
#include "libmidi/MidiUtil.h"

#include "MidiComm.h"
#include "UserSettings.h"
#include "CompatibleSystem.h"
#include "StringUtil.h"
#include "drivers/AlsaMidiDriver.h"

using namespace std;

MidiDriver* g_midi_driver = nullptr;

void midiInit() {
  if (g_midi_driver == nullptr) {
      g_midi_driver = new AlsaMidiDriver();
  }
}

void midiStop() {
  if (g_midi_driver) {
      delete g_midi_driver;
      g_midi_driver = nullptr;
  }
}

void sendNote(const unsigned char note, bool on) {
    if (g_midi_driver) {
        int velocity = on ? 100 : 0;
        // Channel 0, default
        MidiEvent ev = on ? MidiEvent::NoteOn(0, note, velocity) : MidiEvent::NoteOff(0, note, velocity);
        g_midi_driver->Write(ev);
    }
}

// private use helper
static MidiCommDescription ConvertInfo(const MidiDeviceInfo& info) {
    MidiCommDescription d;
    d.id = info.id;
    d.name = info.name;
    d.client = info.client;
    d.port = info.port;
    return d;
}

// Midi IN Ports

static bool built_input_list = false;
static MidiCommDescriptionList in_list;

MidiCommIn::MidiCommIn(unsigned int device_id) {
  m_should_reconnect = false;

  // Ensure init
  midiInit();

  if (device_id < GetDeviceList().size()) {
      m_description = GetDeviceList()[device_id];
      if (g_midi_driver) {
          g_midi_driver->OpenInput(device_id);
      }
  }
}

MidiCommIn::~MidiCommIn() {
  if (g_midi_driver) {
      g_midi_driver->CloseInput();
  }
}

MidiCommDescriptionList MidiCommIn::GetDeviceList() {
  if (built_input_list) return in_list;

  midiInit();
  in_list.clear();
  if (g_midi_driver) {
      auto devices = g_midi_driver->GetInputDevices();
      for (const auto& dev : devices) {
          in_list.push_back(ConvertInfo(dev));
      }
  }
  built_input_list = true;
  return in_list;
}

void MidiCommIn::UpdateDeviceList() {
    built_input_list = false;
    // Don't call GetDeviceList here, wait for next request
}

MidiEvent MidiCommIn::Read() {
    if (g_midi_driver) {
        return g_midi_driver->Read();
    }
    return MidiEvent::NullEvent();
}

bool MidiCommIn::KeepReading() const {
    if (g_midi_driver) {
        return g_midi_driver->HasInput();
    }
    return false;
}

void MidiCommIn::Reset() {
    // Driver doesn't expose Reset (drop input) directly in interface yet,
    // but Close/Open cycle might work, or we add Reset to interface.
    // For now, AlsaMidiDriver::CloseInput calls snd_seq_drop_input logic inside Shutdown?
    // Actually AlsaMidiDriver has CloseInput.
    // Let's add Reset to MidiDriver interface in a future step if needed.
    // For now, assume reading until empty clears it.
    while(KeepReading()) {
        Read();
    }
}

bool MidiCommIn::ShouldReconnect() const {
  return m_should_reconnect;
}

void MidiCommIn::Reconnect() {
    // Logic handled by driver state
    m_should_reconnect = false;
}


// Midi OUT Ports

static bool built_output_list = false;
static MidiCommDescriptionList out_list;

MidiCommOut::MidiCommOut(unsigned int device_id) {
  midiInit();

  if (device_id < GetDeviceList().size()) {
      m_description = GetDeviceList()[device_id];
      if (g_midi_driver) {
          g_midi_driver->OpenOutput(device_id);
      }
  }
}

MidiCommOut::~MidiCommOut() {
  if (g_midi_driver) {
      g_midi_driver->CloseOutput();
  }
}

void MidiCommOut::UpdateDeviceList() {
    built_output_list = false;
}

MidiCommDescriptionList MidiCommOut::GetDeviceList() {
  if (built_output_list) return out_list;

  midiInit();
  out_list.clear();
  if (g_midi_driver) {
      auto devices = g_midi_driver->GetOutputDevices();
      for (const auto& dev : devices) {
          out_list.push_back(ConvertInfo(dev));
      }
  }
  built_output_list = true;
  return out_list;
}

void MidiCommOut::Write(const MidiEvent &out) {
    if (g_midi_driver) {
        g_midi_driver->Write(out);
    }

    // Track notes for Reset()
    if (out.Type() == MidiEventType_NoteOn) {
        notes_on.push_back(pair<int,int>(out.Channel(), out.NoteNumber()));
    } else if (out.Type() == MidiEventType_NoteOff) {
        pair<int,int> p(out.Channel(), out.NoteNumber());
        for (auto i = notes_on.begin(); i != notes_on.end(); ++i) {
            if (*i == p) {
                notes_on.erase(i);
                break;
            }
        }
    }
}

void MidiCommOut::Reset() {
  // Send Note-Off to every open note
  if (g_midi_driver) {
      for (auto i = notes_on.begin(); i != notes_on.end(); ++i) {
          MidiEvent ev = MidiEvent::NoteOff(i->first, i->second);
          g_midi_driver->Write(ev);
      }
  }
  notes_on.clear();
}

void MidiCommOut::Reconnect() {
    // Driver handles
}
