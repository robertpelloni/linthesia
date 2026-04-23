#ifndef __WINMM_MIDI_DRIVER_H
#define __WINMM_MIDI_DRIVER_H

#include "MidiDriver.h"
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

class WinMMMidiDriver : public MidiDriver {
public:
  WinMMMidiDriver();
  virtual ~WinMMMidiDriver();

  virtual std::vector<std::string> GetOutputPorts() override;
  virtual std::vector<std::string> GetInputPorts() override;

  virtual void OpenOutput(const std::string& portName) override;
  virtual void OpenInput(const std::string& portName) override;
  virtual void Write(const std::vector<unsigned char>& message) override;

private:
#ifdef _WIN32
  HMIDIOUT m_outHandle;
  HMIDIIN m_inHandle;
#endif
  bool m_is_open;
};

#endif // __WINMM_MIDI_DRIVER_H
