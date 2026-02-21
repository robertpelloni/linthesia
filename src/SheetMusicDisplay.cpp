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
                             const std::vector<Track::Properties> &track_properties,
                             const MidiEventMicrosecondList &bar_lines,
                             int key_sf, int key_mi) {

    // Draw Background
    renderer.SetColor(240, 240, 230); // Paper color
    renderer.DrawQuad(x, y, m_width, m_height);

    int staff_top_y = y + 60;
    int staff_width = m_width - 40;

    // Draw Bar Lines first (behind notes)
    DrawBarLines(renderer, x + 50, staff_top_y, staff_width, 4 * LineSpacing, show_duration, current_time, bar_lines);

    // Draw Staff Lines
    // Treble Clef Staff
    // 5 lines. E4, G4, B4, D5, F5
    DrawStaff(renderer, x + 20, staff_top_y, staff_width);

    // Draw Clef
    DrawClef(renderer, x + 30, staff_top_y);

    // Draw Key Signature
    DrawKeySignature(renderer, x + 60, staff_top_y, key_sf);

    // Draw Notes
    // Horizontal mapping: Time -> X
    // Vertical mapping: Pitch -> Y

    // Time scaling: width / duration
    double time_scale = (double)(m_width - 100) / show_duration;
    int start_x = x + 100; // Padding for clef + key sig

    std::vector<NoteCoord> beam_group;
    // Heuristic for "short" note (8th note or less).
    // Assuming 120bpm, quarter note is 500ms. 8th is 250ms.
    const long long ShortNoteThreshold = 300000;

    for (const auto& note : notes) {
        if (note.start < current_time) continue;
        if (note.start > current_time + show_duration) break;

        const Track::Mode mode = track_properties[note.track_id].mode;
        if (mode == Track::ModeNotPlayed || mode == Track::ModePlayedButHidden)
            continue;

        long long dt = note.start - current_time;
        int note_x = start_x + (int)(dt * time_scale);
        int note_y = staff_top_y + GetStaffY(note.note_id);

        long long duration = note.end - note.start;
        bool is_short = (duration < ShortNoteThreshold);

        bool stem_up = (note.note_id < 71); // B4

        // Check if we should break the beam
        if (!beam_group.empty()) {
            bool break_beam = !is_short;
            if (!break_beam) {
                // Check distance
                if (note_x - beam_group.back().x > 40) break_beam = true;
                // Check stem direction consistency? Usually forced, but let's break if mixed for now.
                // Actually, beams usually force stem direction based on majority.
                // For now, break if different to avoid complex logic.
                if (stem_up != beam_group.back().stem_up) break_beam = true;
            }

            if (break_beam) {
                if (beam_group.size() > 1) {
                    DrawBeam(renderer, beam_group);
                    // Draw notes without stems? No, DrawBeam just draws the beam.
                    // Stems should connect to the beam.
                    // DrawNote draws the stem to default length.
                    // If beamed, stem length should adjust.
                    // For Phase 2, let's just draw the beam on top of the stems.
                }
                beam_group.clear();
            }
        }

        if (is_short) {
            beam_group.push_back({note_x, note_y, stem_up, (int)note.note_id});
        }

        // Draw the note (with stem)
        // If part of beam, maybe we should suppress the flag?
        // DrawNote currently just draws stem (quarter note style).
        // 8th notes need flags if not beamed.
        // For now, just draw standard note.
        DrawNote(renderer, note_x, note_y, note.note_id, track_properties[note.track_id].color, true);
    }

    // Flush remaining beam
    if (beam_group.size() > 1) {
        DrawBeam(renderer, beam_group);
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

void SheetMusicDisplay::DrawStem(Renderer &renderer, int x, int y, bool stem_up) {
    renderer.SetColor(0, 0, 0);
    int h = 35; // 3.5 spaces
    int w = 1;  // thin stem

    if (stem_up) {
        // Stem goes up from the right side of the note head
        // Note head is 12 wide.
        // Start x at x + 10 (near right edge)
        // Start y at y + 5 (middle of note) go up to y - h + 5
        renderer.DrawQuad(x + 10, y - h + 5, w, h);
    } else {
        // Stem goes down from the left side of the note head
        // Start x at x + 1 (near left edge)
        // Start y at y + 5 go down to y + h + 5
        renderer.DrawQuad(x + 1, y + 5, w, h);
    }
}

void SheetMusicDisplay::DrawBeam(Renderer &renderer, const std::vector<NoteCoord> &notes) {
    if (notes.size() < 2) return;

    renderer.SetColor(0, 0, 0);
    int beam_thick = 5;

    // Simple horizontal beam (or slanted)
    // Connect tips of stems.
    // Stem length is 35.
    // If stem up: tip is at y - 35 + 5 = y - 30.
    // If stem down: tip is at y + 35 + 5 = y + 40.

    // We should calculate slope.
    // Start point
    int x1 = notes.front().x + (notes.front().stem_up ? 10 : 1);
    int y1 = notes.front().y + (notes.front().stem_up ? -30 : 40);

    // End point
    int x2 = notes.back().x + (notes.back().stem_up ? 10 : 1);
    int y2 = notes.back().y + (notes.back().stem_up ? -30 : 40);

    // Draw quad connecting (x1, y1) to (x2, y2) with thickness
    // Since we only have axis-aligned quads (DrawQuad), we can approximate with steps
    // or just draw a thick horizontal/slanted line if we have Line logic.
    // Renderer has DrawQuad. Does it have DrawLine? No.
    // We can simulate a line with many small quads.

    float slope = (float)(y2 - y1) / (float)(x2 - x1);

    for (int i = 0; i <= (x2 - x1); ++i) {
        int cx = x1 + i;
        int cy = y1 + (int)(slope * i);
        renderer.DrawQuad(cx, cy, 1, beam_thick);
    }
}

void SheetMusicDisplay::DrawNote(Renderer &renderer, int x, int y, int note_id, Track::TrackColor color, bool draw_stem) {
    // Determine stem direction
    // B4 (71) is the middle line.
    // If note >= 71, stem down. Else up.
    bool stem_up = (note_id < 71);

    // Draw Stem first (so note head covers connection point if needed)
    if (draw_stem) {
        DrawStem(renderer, x, y, stem_up);
    }

    // Simple oval
    SDL_Color c = Track::ColorNoteWhite[color];
    renderer.SetColor(c);

    // Draw "Oval" (Octagon approximation for now since we lack texture)
    // 12x10 size
    int w = 12;
    int h = 10;

    // Main body
    renderer.DrawQuad(x+2, y, w-4, h);
    renderer.DrawQuad(x, y+2, w, h-4);

    // Ledger lines
    // y is relative to staff top. Staff is 40px tall (4 gaps * 10).
    // Center of note is y + h/2.
    // Top line is 0. Bottom line is 40.
    // If center < 0 or > 40, draw ledgers.
    // Each line is 10px apart.

    // Note: y is calculated for the *top* of the note?
    // GetStaffY returns "step * 5".
    // 0 is F5 (top line). 40 is E4 (bottom line).
    // Ledger lines are at 0, -20 (A5), etc?
    // Actually, lines are at 0, 10, 20, 30, 40.
    // C6 is above staff -> y approx -20?
    // C4 is below staff -> y approx 60?

    int center_y = y + 5;

    // Below staff ledgers (C4 is 60)
    // E4 is 40. C4 is 60 (Line).
    if (center_y >= 50) {
        // Draw line at 50, 60...
        for (int ly = 50; ly <= center_y; ly += 10) {
             renderer.SetColor(0, 0, 0);
             renderer.DrawQuad(x - 4, ly, w + 8, 1);
        }
    }

    // Above staff ledgers (A5 is -10)
    // F5 is 0. A5 is -10.
    if (center_y <= -10) {
        for (int ly = -10; ly >= center_y; ly -= 10) {
             renderer.SetColor(0, 0, 0);
             renderer.DrawQuad(x - 4, ly, w + 8, 1);
        }
    }
}

void SheetMusicDisplay::DrawClef(Renderer &renderer, int x, int y) {
    renderer.SetColor(0, 0, 0);
    // Approximate Treble Clef
    // Vertical line
    renderer.DrawQuad(x + 10, y - 10, 2, 55);
    // Bottom hook
    renderer.DrawQuad(x + 5, y + 45, 5, 2);
    // Top loop
    renderer.DrawQuad(x + 12, y - 10, 5, 2);
    renderer.DrawQuad(x + 17, y - 8, 2, 10);
    renderer.DrawQuad(x + 10, y + 2, 9, 2);
    // G-clef spiral center (G line is y+30)
    renderer.DrawQuad(x + 5, y + 25, 12, 2); // Top of spiral
    renderer.DrawQuad(x + 5, y + 35, 12, 2); // Bottom of spiral
    renderer.DrawQuad(x + 5, y + 25, 2, 12); // Left
    renderer.DrawQuad(x + 17, y + 25, 2, 12); // Right
}

void SheetMusicDisplay::DrawKeySignature(Renderer &renderer, int x, int y, int key_sf) {
    if (key_sf == 0) return;

    renderer.SetColor(0, 0, 0);
    int current_x = x;

    // Draw Sharps
    if (key_sf > 0) {
        // Order: F C G D A E B
        // MIDI notes for treble clef placement:
        // F5(77), C5(72), G5(79), D5(74), A4(69), E5(76), B4(71)
        static const int SharpNotes[] = { 77, 72, 79, 74, 69, 76, 71 };

        for (int i = 0; i < key_sf && i < 7; ++i) {
            int note_y = y + GetStaffY(SharpNotes[i]);
            // Draw Sharp (#) - Approximate
            // Two vertical lines, two slanted horizontal
            int sx = current_x;
            int sy = note_y;

            renderer.DrawQuad(sx, sy, 1, 14);
            renderer.DrawQuad(sx+3, sy, 1, 14);
            renderer.DrawQuad(sx-2, sy+4, 8, 1);
            renderer.DrawQuad(sx-2, sy+8, 8, 1);

            current_x += 10;
        }
    }
    // Draw Flats
    else if (key_sf < 0) {
        // Order: B E A D G C F
        // MIDI notes:
        // B4(71), E5(76), A4(69), D5(74), G4(67), C5(72), F4(65)
        static const int FlatNotes[] = { 71, 76, 69, 74, 67, 72, 65 };

        for (int i = 0; i < -key_sf && i < 7; ++i) {
             int note_y = y + GetStaffY(FlatNotes[i]);
             // Draw Flat (b) - Approximate
             // Vertical line + curve
             int sx = current_x;
             int sy = note_y;

             renderer.DrawQuad(sx, sy-4, 1, 14);
             // Curve? approximated by a small box for now or "b" shape
             renderer.DrawQuad(sx, sy+5, 4, 1);
             renderer.DrawQuad(sx+4, sy+5, 1, 4);
             renderer.DrawQuad(sx, sy+9, 4, 1);

             current_x += 10;
        }
    }
}

void SheetMusicDisplay::DrawBarLines(Renderer &renderer, int x, int y, int width, int height,
                                     microseconds_t show_duration, microseconds_t current_time,
                                     const MidiEventMicrosecondList &bar_lines) {
    renderer.SetColor(180, 180, 180); // Gray lines
    double time_scale = (double)(width - 50) / show_duration;

    for (microseconds_t t : bar_lines) {
        if (t < current_time) continue;
        if (t > current_time + show_duration) break;

        long long dt = t - current_time;
        int bx = x + (int)(dt * time_scale);

        renderer.DrawQuad(bx, y, 2, height);
    }
}
