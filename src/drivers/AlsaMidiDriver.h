// -*- mode: c++; coding: utf-8 -*-

// Linthesia

#ifndef __ALSA_MIDI_DRIVER_H
#define __ALSA_MIDI_DRIVER_H

#include "../MidiDriver.h"
#include <alsa/asoundlib.h>
#include <vector>

class AlsaMidiDriver : public MidiDriver {
public:
  AlsaMidiDriver();
  virtual ~AlsaMidiDriver();

  virtual std::vector<MidiDeviceInfo> GetInputDevices() override;
  virtual std::vector<MidiDeviceInfo> GetOutputDevices() override;

  virtual void OpenInput(unsigned int device_id) override;
  virtual void CloseInput() override;
  virtual MidiEvent Read() override;
  virtual bool HasInput() override;

  virtual void OpenOutput(unsigned int device_id) override;
  virtual void CloseOutput() override;
  virtual void Write(const MidiEvent &ev) override;

private:
  void Init();
  void Shutdown();
  void RetrieveDevices(unsigned int perms, std::vector<MidiDeviceInfo>& devices);

  bool m_midi_initiated;
  bool m_emulate_kb;
  snd_seq_t* m_alsa_seq;
  int m_local_out, m_local_in, m_anon_in, m_keybd_out;

  // Connection state
  int m_connected_in_client;
  int m_connected_in_port;
  int m_connected_out_client;
  int m_connected_out_port;
};

#endif // __ALSA_MIDI_DRIVER_H
