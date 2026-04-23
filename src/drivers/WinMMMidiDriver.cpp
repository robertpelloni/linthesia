#include "WinMMMidiDriver.h"
#include <iostream>

WinMMMidiDriver::WinMMMidiDriver() : m_is_open(false) {
#ifdef _WIN32
  m_outHandle = NULL;
  m_inHandle = NULL;
#endif
}

WinMMMidiDriver::~WinMMMidiDriver() {
#ifdef _WIN32
  if (m_outHandle) {
      midiOutClose(m_outHandle);
  }
  if (m_inHandle) {
      midiInClose(m_inHandle);
  }
#endif
}

std::vector<std::string> WinMMMidiDriver::GetOutputPorts() {
  std::vector<std::string> ports;
#ifdef _WIN32
  UINT numDevs = midiOutGetNumDevs();
  for (UINT i = 0; i < numDevs; ++i) {
      MIDIOUTCAPS caps;
      if (midiOutGetDevCaps(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR) {
          ports.push_back(caps.szPname);
      }
  }
#endif
  return ports;
}

std::vector<std::string> WinMMMidiDriver::GetInputPorts() {
  std::vector<std::string> ports;
#ifdef _WIN32
  UINT numDevs = midiInGetNumDevs();
  for (UINT i = 0; i < numDevs; ++i) {
      MIDIINCAPS caps;
      if (midiInGetDevCaps(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR) {
          ports.push_back(caps.szPname);
      }
  }
#endif
  return ports;
}

void WinMMMidiDriver::OpenOutput(const std::string& portName) {
#ifdef _WIN32
  UINT numDevs = midiOutGetNumDevs();
  for (UINT i = 0; i < numDevs; ++i) {
      MIDIOUTCAPS caps;
      if (midiOutGetDevCaps(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR) {
          if (std::string(caps.szPname) == portName) {
              if (midiOutOpen(&m_outHandle, i, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
                  m_is_open = true;
              }
              break;
          }
      }
  }
#else
  (void)portName;
#endif
}

void WinMMMidiDriver::OpenInput(const std::string& portName) {
#ifdef _WIN32
  UINT numDevs = midiInGetNumDevs();
  for (UINT i = 0; i < numDevs; ++i) {
      MIDIINCAPS caps;
      if (midiInGetDevCaps(i, &caps, sizeof(caps)) == MMSYSERR_NOERROR) {
          if (std::string(caps.szPname) == portName) {
              if (midiInOpen(&m_inHandle, i, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
                  midiInStart(m_inHandle);
              }
              break;
          }
      }
  }
#else
  (void)portName;
#endif
}

void WinMMMidiDriver::Write(const std::vector<unsigned char>& message) {
  if (message.empty() || !m_is_open) return;

#ifdef _WIN32
  if (message.size() <= 3) {
      DWORD msg = 0;
      for (size_t i = 0; i < message.size(); ++i) {
          msg |= (message[i] << (i * 8));
      }
      midiOutShortMsg(m_outHandle, msg);
  }
#endif
}
