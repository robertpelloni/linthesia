// -*- mode: c++; coding: utf-8 -*-

// Linthesia

#include "SheetMusicDisplay.h"
#include "Textures.h"

using namespace std;

SheetMusicDisplay::SheetMusicDisplay(int width, int height) :
    m_width(width), m_height(height) {
}

// Basic Treble Clef mapping
// Middle C (60) is below the staff.
// Treble Clef bottom line is E4 (64).
// Line spacing is usually ~10px.
const int LineSpacing = 10;
const int MiddleC_Y = 120; // Relative to staff top? No, let's fix staff top.

void SheetMusicDisplay::Draw(Renderer &renderer, int x, int y,
                             const TranslatedNoteSet &notes,
                             microseconds_t show_duration,
                             microseconds_t current_time,
                             const std::vector<Track::Properties> &track_properties) {

    // Draw Background
    renderer.SetColor(240, 240, 230); // Paper color
    renderer.DrawQuad(x, y, m_width, m_height);

    // Draw Staff Lines
    // Treble Clef Staff
    // 5 lines. E4, G4, B4, D5, F5
    int staff_top_y = y + 60;
    DrawStaff(renderer, x + 20, staff_top_y, m_width - 40);

    // Draw Notes
    // Horizontal mapping: Time -> X
    // Vertical mapping: Pitch -> Y

    // Time scaling: width / duration
    double time_scale = (double)(m_width - 100) / show_duration;
    int start_x = x + 50; // Padding for clef

    for (const auto& note : notes) {
        if (note.start < current_time) continue;
        if (note.start > current_time + show_duration) break;

        const Track::Mode mode = track_properties[note.track_id].mode;
        if (mode == Track::ModeNotPlayed || mode == Track::ModePlayedButHidden)
            continue;

        long long dt = note.start - current_time;
        int note_x = start_x + (int)(dt * time_scale);
        int note_y = staff_top_y + GetStaffY(note.note_id);

        DrawNote(renderer, note_x, note_y, note.note_id, track_properties[note.track_id].color);
    }
}

void SheetMusicDisplay::DrawStaff(Renderer &renderer, int x, int y, int width) {
    renderer.SetColor(0, 0, 0);
    for (int i = 0; i < 5; ++i) {
        renderer.DrawQuad(x, y + i * LineSpacing, width, 1); // 1px line
    }
}

int SheetMusicDisplay::GetStaffY(int note_id) {
    // F5 (top line) is 77.
    // E4 (bottom line) is 64.
    // We render lines at y, y+10, y+20, y+30, y+40.
    // So y is F5. y+40 is E4.
    // Each semitone is not linear visual step (sharps/flats share lines).
    // Simple diatonic mapping for C Major:
    // C(60), D(62), E(64), F(65), G(67), A(69), B(71)

    // Offset from F5 (77)
    // F5 -> 0
    // E5 -> 5 (half space)
    // D5 -> 10 (line)

    // Map: Note -> Scale Degree relative to F5
    // Need a proper theory helper for key signatures, but let's assume C Major visual for now.
    // White keys only logic?

    // F5 (77) is index 0.
    // Each white key down adds 5 pixels (half line spacing).

    // Ref: F5(77), E5(76), D5(74), C5(72), B4(71), A4(69), G4(67), F4(65), E4(64)
    // Indexes: 0, 1, 2, 3, 4, 5, 6, 7, 8

    // Simple lookup for octave 0-11
    static const int OctaveOffsets[] = {
        0, 0, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6
        // C, C#, D, D#, E, F, F#, G, G#, A, A#, B
        // C is bottom? No, C is below D.
    };

    // Relative to C:
    // C=0, D=1, E=2, F=3, G=4, A=5, B=6

    int octave = (note_id / 12) - 1; // MIDI octaves
    int note_in_octave = note_id % 12;

    // Scale step from C0
    int scale_step = octave * 7 + OctaveOffsets[note_in_octave];

    // F5 (77) is C5 (72) + 3 steps (D,E,F).
    // F5 is step: (5*7 + 3) = 38.

    int f5_step = 38 + 7; // Adjust for octave

    // Inverted Y: Higher pitch = Lower Y value (0 is top)
    // Each step is 5 pixels (half line)

    return (f5_step - scale_step) * (LineSpacing / 2);
}

void SheetMusicDisplay::DrawNote(Renderer &renderer, int x, int y, int note_id, Track::TrackColor color) {
    // Simple oval
    SDL_Color c = Track::ColorNoteWhite[color];
    renderer.SetColor(c);
    renderer.DrawQuad(x, y, 12, 10); // Placeholder oval

    // Ledger lines if needed
    // If y is outside 0 to 40 relative to staff top?
    // Implementation for later polish.
}
