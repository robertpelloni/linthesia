#ifndef WEBMIDI_DRIVER_H
#define WEBMIDI_DRIVER_H

#include "MidiDriver.h"

// Note: This driver is intended for WASM compilation via Emscripten.
// Native builds should conditionally exclude this or provide stubs.

class WebMidiDriver : public MidiDriver {
public:
    WebMidiDriver();
    virtual ~WebMidiDriver();

    std::vector<std::string> GetOutputPorts() override;
    std::vector<std::string> GetInputPorts() override;

    void OpenOutput(const std::string& portName) override;
    void OpenInput(const std::string& portName) override;

    void Write(const std::vector<unsigned char>& message) override;

private:
    bool m_initialized;
    std::string m_currentOutPort;
    std::string m_currentInPort;
};

#endif // WEBMIDI_DRIVER_H
