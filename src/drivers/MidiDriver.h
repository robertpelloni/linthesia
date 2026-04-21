#ifndef __MIDI_DRIVER_H
#define __MIDI_DRIVER_H

#include <vector>
#include <string>

class MidiDriver {
public:
    virtual ~MidiDriver() {}
    virtual std::vector<std::string> GetOutputPorts() = 0;
    virtual std::vector<std::string> GetInputPorts() = 0;
    virtual void OpenOutput(const std::string& portName) = 0;
    virtual void OpenInput(const std::string& portName) = 0;
    virtual void Write(const std::vector<unsigned char>& message) = 0;
};

#endif
