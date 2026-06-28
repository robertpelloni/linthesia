#include "WebMidiDriver.h"
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

WebMidiDriver::WebMidiDriver() : m_initialized(false) {
#ifdef __EMSCRIPTEN__
    // Asynchronous request for MIDI access in browser
    EM_ASM(
        if (navigator.requestMIDIAccess) {
            navigator.requestMIDIAccess().then(function(midiAccess) {
                window.midiAccess = midiAccess;
                console.log("Web MIDI API initialized.");
            }, function(msg) {
                console.error("Failed to get MIDI access - " + msg);
            });
        } else {
            console.warn("Web MIDI API not supported in this browser.");
        }
    );
    m_initialized = true;
#endif
}

WebMidiDriver::~WebMidiDriver() {
}

std::vector<std::string> WebMidiDriver::GetOutputPorts() {
    std::vector<std::string> ports;
#ifdef __EMSCRIPTEN__
    // A more complete implementation would bridge Javascript iterators back to C++
    ports.push_back("Web Browser Default MIDI Out");
#else
    ports.push_back("Dummy Web MIDI Out (Native Build)");
#endif
    return ports;
}

std::vector<std::string> WebMidiDriver::GetInputPorts() {
    std::vector<std::string> ports;
#ifdef __EMSCRIPTEN__
    ports.push_back("Web Browser Default MIDI In");
#else
    ports.push_back("Dummy Web MIDI In (Native Build)");
#endif
    return ports;
}

void WebMidiDriver::OpenOutput(const std::string& portName) {
    m_currentOutPort = portName;
    std::cout << "Opened Web MIDI Output Port: " << portName << std::endl;
}

void WebMidiDriver::OpenInput(const std::string& portName) {
    m_currentInPort = portName;
    std::cout << "Opened Web MIDI Input Port: " << portName << std::endl;
}

void WebMidiDriver::Write(const std::vector<unsigned char>& message) {
    if (message.empty()) return;
#ifdef __EMSCRIPTEN__
    // We pass the raw bytes over to Javascript
    // For simplicity we handle up to 3 byte messages here inline
    if (message.size() == 3) {
        EM_ASM_({
            if (window.midiAccess && window.midiAccess.outputs.size > 0) {
                var outputs = window.midiAccess.outputs.values();
                for (var output = outputs.next(); output && !output.done; output = outputs.next()) {
                    output.value.send([$0, $1, $2]);
                }
            }
        }, message[0], message[1], message[2]);
    }
#else
    // Stub
#endif
}
