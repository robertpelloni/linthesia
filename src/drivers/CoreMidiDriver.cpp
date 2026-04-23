#include "CoreMidiDriver.h"
#include <iostream>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>

static std::string CFStringToString(CFStringRef cfString) {
    if (!cfString) return "";
    char buffer[256];
    if (CFStringGetCString(cfString, buffer, sizeof(buffer), kCFStringEncodingUTF8)) {
        return std::string(buffer);
    }
    return "";
}
#endif

CoreMidiDriver::CoreMidiDriver() : m_is_open(false) {
#ifdef __APPLE__
  MIDIClientCreate(CFSTR("Linthesia Client"), NULL, NULL, &m_client);
  MIDIOutputPortCreate(m_client, CFSTR("Linthesia Output Port"), &m_outPort);
#endif
}

CoreMidiDriver::~CoreMidiDriver() {
#ifdef __APPLE__
  if (m_outPort) MIDIPortDispose(m_outPort);
  if (m_inPort) MIDIPortDispose(m_inPort);
  if (m_client) MIDIClientDispose(m_client);
#endif
}

std::vector<std::string> CoreMidiDriver::GetOutputPorts() {
  std::vector<std::string> ports;
#ifdef __APPLE__
  ItemCount destCount = MIDIGetNumberOfDestinations();
  for (ItemCount i = 0; i < destCount; ++i) {
      MIDIEndpointRef dest = MIDIGetDestination(i);
      CFStringRef name;
      MIDIObjectGetStringProperty(dest, kMIDIPropertyName, &name);
      ports.push_back(CFStringToString(name));
      CFRelease(name);
  }
#endif
  return ports;
}

std::vector<std::string> CoreMidiDriver::GetInputPorts() {
  std::vector<std::string> ports;
#ifdef __APPLE__
  ItemCount srcCount = MIDIGetNumberOfSources();
  for (ItemCount i = 0; i < srcCount; ++i) {
      MIDIEndpointRef src = MIDIGetSource(i);
      CFStringRef name;
      MIDIObjectGetStringProperty(src, kMIDIPropertyName, &name);
      ports.push_back(CFStringToString(name));
      CFRelease(name);
  }
#endif
  return ports;
}

void CoreMidiDriver::OpenOutput(const std::string& portName) {
#ifdef __APPLE__
  ItemCount destCount = MIDIGetNumberOfDestinations();
  for (ItemCount i = 0; i < destCount; ++i) {
      MIDIEndpointRef dest = MIDIGetDestination(i);
      CFStringRef name;
      MIDIObjectGetStringProperty(dest, kMIDIPropertyName, &name);
      std::string currentName = CFStringToString(name);
      CFRelease(name);

      if (currentName == portName) {
          m_destEndpoint = dest;
          m_is_open = true;
          break;
      }
  }
#else
  (void)portName;
#endif
}

void CoreMidiDriver::OpenInput(const std::string& portName) {
  (void)portName;
  // TODO: implement MIDIInputPortCreate and hook up callback
}

void CoreMidiDriver::Write(const std::vector<unsigned char>& message) {
  if (message.empty() || !m_is_open) return;

#ifdef __APPLE__
  Byte packetBuffer[256];
  MIDIPacketList* packetList = (MIDIPacketList*)packetBuffer;
  MIDIPacket* packet = MIDIPacketListInit(packetList);

  packet = MIDIPacketListAdd(packetList, sizeof(packetBuffer), packet, 0, message.size(), message.data());

  if (packet) {
      MIDISend(m_outPort, m_destEndpoint, packetList);
  }
#endif
}
