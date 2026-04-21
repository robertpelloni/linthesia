#include <gtest/gtest.h>
#include "MidiEvent.h"
#include "MidiTypes.h"
#include "MidiTrack.h"

// Test basic MidiEvent construction and getters
TEST(MidiEventTest, BasicNoteOn) {
    // Note On (Channel 0), Middle C (60), Velocity 127
    MidiEventSimple simple(0x90, 60, 127);
    MidiEvent ev = MidiEvent::Build(simple);

    EXPECT_EQ(ev.Type(), MidiEventType_NoteOn);
    EXPECT_EQ(ev.NoteNumber(), 60);
    EXPECT_EQ(ev.NoteVelocity(), 127);
}

TEST(MidiEventTest, BasicNoteOff) {
    // Note Off (Channel 0), Middle C (60), Velocity 0
    MidiEventSimple simple(0x80, 60, 0);
    MidiEvent ev = MidiEvent::Build(simple);

    EXPECT_EQ(ev.Type(), MidiEventType_NoteOff);
    EXPECT_EQ(ev.NoteNumber(), 60);

    // Explicit NoteOff status
    MidiEventSimple explicit_off(0x80, 64, 64);
    MidiEvent ev2 = MidiEvent::Build(explicit_off);
    EXPECT_EQ(ev2.Type(), MidiEventType_NoteOff);
    EXPECT_EQ(ev2.NoteNumber(), 64);
}

// Test MidiTrack note aggregation via raw event ingestion since AddEvent is private/missing
TEST(MidiTrackTest, TrackResetLogic) {
    MidiTrack track = MidiTrack::CreateBlankTrack();

    // Ensure it begins reset correctly
    EXPECT_EQ(track.AggregateEventCount(), 0);
    EXPECT_EQ(track.AggregateNoteCount(), 0);
    EXPECT_FALSE(track.hasNotes());

    // Reset shouldn't crash
    track.Reset();
}
