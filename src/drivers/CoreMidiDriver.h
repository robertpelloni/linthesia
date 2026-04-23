#ifndef __CORE_MIDI_DRIVER_H
#define __CORE_MIDI_DRIVER_H

#include "MidiDriver.h"
#include <string>
#include <vector>

#ifdef __APPLE__
#include <CoreMIDI/CoreMIDI.h>
#endif

class CoreMidiDriver : public MidiDriver {
public:
  CoreMidiDriver();
  virtual ~CoreMidiDriver();

  virtual std::vector<std::string> GetOutputPorts() override;
  virtual std::vector<std::string> GetInputPorts() override;

  virtual void OpenOutput(const std::string& portName) override;
  virtual void OpenInput(const std::string& portName) override;
  virtual void Write(const std::vector<unsigned char>& message) override;

private:
#ifdef __APPLE__
  MIDIClientRef m_client;
  MIDIPortRef m_outPort;
  MIDIPortRef m_inPort;
  MIDIEndpointRef m_destEndpoint;
#endif
  bool m_is_open;
};

#endif // __CORE_MIDI_DRIVER_H
