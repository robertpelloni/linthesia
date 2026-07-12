#ifndef AICOPILOT_H
#define AICOPILOT_H

#include "libmidi/MidiEvent.h"
#include <vector>

// Forward declaration of an external AI service module interface
class AICoPilot {
public:
    AICoPilot();
    ~AICoPilot();

    // Sends the current user's playing history to the AI for analysis
    void FeedHistory(const std::vector<MidiEvent>& recentEvents);

    // Predicts the next logical accompaniment notes based on history and key signature
    std::vector<MidiEvent> GenerateAccompaniment(unsigned int tempo, int currentKeySignature);

private:
    bool m_aiEnabled;
    std::vector<MidiEvent> m_historyBuffer;
};

#endif // AICOPILOT_H
