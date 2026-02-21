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

    // Layout: Two staves (Grand Staff)
    // Top: Treble
    // Bottom: Bass (offset by ~120px)

    int treble_y = y + 60;
    int bass_y = treble_y + 120;
    int staff_width = m_width - 40;

    // Draw Bar Lines (spanning both staves usually, but let's draw separate for now or connected)
    // Connecting bar line looks better. Height = 120 + 40 = 160.
    DrawBarLines(renderer, x + 50, treble_y, staff_width, 160, show_duration, current_time, bar_lines);

    // Draw Staves
    DrawStaff(renderer, x + 20, treble_y, staff_width);
    DrawStaff(renderer, x + 20, bass_y, staff_width);

    // Draw Clefs
    DrawClef(renderer, x + 30, treble_y, Track::Treble);
    DrawClef(renderer, x + 30, bass_y, Track::Bass);

    // Draw Key Signatures
    DrawKeySignature(renderer, x + 60, treble_y, key_sf, Track::Treble);
    DrawKeySignature(renderer, x + 60, bass_y, key_sf, Track::Bass);

    // Draw Notes
    double time_scale = (double)(m_width - 100) / show_duration;
    int start_x = x + 120; // Increased padding

    // Separate beam groups for each staff
    std::vector<NoteCoord> treble_beam;
    std::vector<NoteCoord> bass_beam;

    const long long ShortNoteThreshold = 300000;

    for (const auto& note : notes) {
        if (note.start < current_time) continue;
        if (note.start > current_time + show_duration) break;

        const Track::Properties& props = track_properties[note.track_id];
        const Track::Mode mode = props.mode;
        if (mode == Track::ModeNotPlayed || mode == Track::ModePlayedButHidden)
            continue;

        long long dt = note.start - current_time;
        int note_x = start_x + (int)(dt * time_scale);

        Track::Clef clef = props.clef;
        int staff_base_y = (clef == Track::Bass) ? bass_y : treble_y;
        int note_y = staff_base_y + GetStaffY(note.note_id, clef, key_sf);

        // Draw Accidental
        Accidental acc = GetAccidental(note.note_id, key_sf);
        if (acc != None) {
            DrawAccidental(renderer, note_x - 12, note_y, acc);
        }

        // Determine stem direction based on clef center line
        // Treble Center: B4 (71)
        // Bass Center: D3 (50)
        int center_pitch = (clef == Track::Bass) ? 50 : 71;
        bool stem_up = (note.note_id < center_pitch);

        long long duration = note.end - note.start;
        bool is_short = (duration < ShortNoteThreshold);

        std::vector<NoteCoord>& beam_group = (clef == Track::Bass) ? bass_beam : treble_beam;

        // Beam Logic
        if (!beam_group.empty()) {
            bool break_beam = !is_short;
            if (!break_beam) {
                if (note_x - beam_group.back().x > 40) break_beam = true;
                // Strict stem direction matching for simple beaming
                if (stem_up != beam_group.back().stem_up) break_beam = true;
            }

            if (break_beam) {
                if (beam_group.size() > 1) {
                    DrawBeam(renderer, beam_group);
                }
                beam_group.clear();
            }
        }

        if (is_short) {
            beam_group.push_back({note_x, note_y, stem_up, (int)note.note_id});
        }

        DrawNote(renderer, note_x, note_y, note.note_id, props.color, true);
    }

    // Flush
    if (treble_beam.size() > 1) DrawBeam(renderer, treble_beam);
    if (bass_beam.size() > 1) DrawBeam(renderer, bass_beam);
}

void SheetMusicDisplay::DrawStaff(Renderer &renderer, int x, int y, int width) {
    renderer.SetColor(0, 0, 0);
    for (int i = 0; i < 5; ++i) {
        renderer.DrawQuad(x, y + i * LineSpacing, width, 1); // 1px line
    }
}

int SheetMusicDisplay::GetStaffY(int note_id, Track::Clef clef, int key_sf) {
    // Reference Note (Top line of staff)
    // Treble: F5 (77)
    // Bass: A3 (57)
    int ref_note_id = (clef == Track::Bass) ? 57 : 77;

    // Sharps: C, C#, D, D#, E, F, F#, G, G#, A, A#, B
    static const int OffsetsSharp[] = { 0, 0, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6 };
    // Flats:  C, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B
    static const int OffsetsFlat[]  = { 0, 1, 1, 2, 2, 3, 4, 4, 5, 5, 6, 6 };

    bool flat_key = (key_sf < 0);
    const int* offsets = flat_key ? OffsetsFlat : OffsetsSharp;

    auto get_scale_step = [offsets](int id) {
        int oct = (id / 12) - 1;
        int n = id % 12;
        return oct * 7 + offsets[n];
    };

    int current_step = get_scale_step(note_id);
    int ref_step = get_scale_step(ref_note_id);

    // 5 pixels per step (half line spacing)
    return (ref_step - current_step) * (LineSpacing / 2);
}

SheetMusicDisplay::Accidental SheetMusicDisplay::GetAccidental(int note_id, int key_sf) {
    // 1. Determine Scale Step
    static const int PitchToStep[] = { 0, 0, 1, 1, 2, 3, 3, 4, 4, 5, 5, 6 };
    int pitch_class = note_id % 12;
    int step = PitchToStep[pitch_class];

    // Flats key mapping: 1->1, 3->2, 6->4, 8->5, 10->6
    if (key_sf < 0) {
        static const int PitchToStepFlat[] = { 0, 1, 1, 2, 2, 3, 4, 4, 5, 5, 6, 6 };
        step = PitchToStepFlat[pitch_class];
    }

    // 2. Determine Expected Pitch for this Step in Key
    static const int BasePitch[] = { 0, 2, 4, 5, 7, 9, 11 };
    int expected_pitch = BasePitch[step];

    // Apply Key Signature adjustments
    static const int SharpSteps[] = { 3, 0, 4, 1, 5, 2, 6 }; // F C G D A E B
    static const int FlatSteps[] = { 6, 2, 5, 1, 4, 0, 3 };  // B E A D G C F

    int key_adjustment = 0;
    if (key_sf > 0) {
        for (int i = 0; i < key_sf; ++i) {
            if (step == SharpSteps[i]) {
                key_adjustment = 1;
                break;
            }
        }
    } else if (key_sf < 0) {
        for (int i = 0; i < -key_sf; ++i) {
            if (step == FlatSteps[i]) {
                key_adjustment = -1;
                break;
            }
        }
    }

    expected_pitch = (expected_pitch + key_adjustment + 12) % 12;

    if (pitch_class == expected_pitch) return None;

    int delta = (pitch_class - expected_pitch + 12) % 12;
    if (delta > 6) delta -= 12;

    if (delta == 1) return Sharp;
    if (delta == -1) return Flat;

    // If we are natural but expected sharp/flat -> Natural
    int base_p = BasePitch[step];
    if (pitch_class == base_p) return Natural;

    return None;
}

void SheetMusicDisplay::DrawAccidental(Renderer &renderer, int x, int y, Accidental acc) {
    renderer.SetColor(0, 0, 0);
    // Draw centered around y (middle of note)
    int sy = y + 5;
    int sx = x;

    if (acc == Sharp) {
        renderer.DrawQuad(sx+2, sy-7, 1, 14);
        renderer.DrawQuad(sx+5, sy-7, 1, 14);
        renderer.DrawQuad(sx, sy-3, 8, 1);
        renderer.DrawQuad(sx, sy+1, 8, 1);
    } else if (acc == Flat) {
        renderer.DrawQuad(sx, sy-10, 1, 14);
        // "b" curve
        renderer.DrawQuad(sx, sy, 4, 1);
        renderer.DrawQuad(sx+4, sy, 1, 4);
        renderer.DrawQuad(sx, sy+4, 4, 1);
    } else if (acc == Natural) {
        // L shape left, 7 shape right
        renderer.DrawQuad(sx, sy-7, 1, 10);
        renderer.DrawQuad(sx, sy+3, 4, 1);
        renderer.DrawQuad(sx+4, sy-3, 1, 10);
        renderer.DrawQuad(sx+1, sy-3, 4, 1);
    }
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

void SheetMusicDisplay::DrawClef(Renderer &renderer, int x, int y, Track::Clef clef) {
    renderer.SetColor(0, 0, 0);

    if (clef == Track::Treble) {
        // Approximate Treble Clef (G-Clef)
        // Vertical line
        renderer.DrawQuad(x + 10, y - 10, 2, 55);
        // Bottom hook
        renderer.DrawQuad(x + 5, y + 45, 5, 2);
        // Top loop
        renderer.DrawQuad(x + 12, y - 10, 5, 2);
        renderer.DrawQuad(x + 17, y - 8, 2, 10);
        renderer.DrawQuad(x + 10, y + 2, 9, 2);
        // G-clef spiral center (G line is y+30)
        renderer.DrawQuad(x + 5, y + 25, 12, 2); // Top
        renderer.DrawQuad(x + 5, y + 35, 12, 2); // Bottom
        renderer.DrawQuad(x + 5, y + 25, 2, 12); // Left
        renderer.DrawQuad(x + 17, y + 25, 2, 12); // Right
    } else {
        // Bass Clef (F-Clef)
        // F-Line is 2nd from top (y+10)
        // Dot on F-Line
        int f_line_y = y + 10;
        renderer.DrawQuad(x + 5, f_line_y - 3, 6, 6);
        // Curve (Ear)
        renderer.DrawQuad(x + 5, f_line_y - 8, 10, 2); // Top curve
        renderer.DrawQuad(x + 15, f_line_y - 8, 2, 15); // Right side
        renderer.DrawQuad(x + 5, f_line_y + 7, 12, 2); // Bottom
        // Two dots to the right (surrounding F-line)
        renderer.DrawQuad(x + 20, f_line_y - 5, 3, 3);
        renderer.DrawQuad(x + 20, f_line_y + 5, 3, 3);
    }
}

void SheetMusicDisplay::DrawKeySignature(Renderer &renderer, int x, int y, int key_sf, Track::Clef clef) {
    if (key_sf == 0) return;

    renderer.SetColor(0, 0, 0);
    int current_x = x;

    if (key_sf > 0) {
        // Sharps: F C G D A E B
        static const int SharpNotesTreble[] = { 77, 72, 79, 74, 69, 76, 71 }; // F5, C5, G5, D5, A4, E5, B4
        static const int SharpNotesBass[] =   { 53, 48, 55, 50, 45, 52, 47 }; // F3, C3, G3, D3, A2, E3, B2

        const int* notes = (clef == Track::Bass) ? SharpNotesBass : SharpNotesTreble;

        for (int i = 0; i < key_sf && i < 7; ++i) {
            int note_y = y + GetStaffY(notes[i], clef, key_sf);
            int sx = current_x;
            int sy = note_y;

            renderer.DrawQuad(sx, sy, 1, 14);
            renderer.DrawQuad(sx+3, sy, 1, 14);
            renderer.DrawQuad(sx-2, sy+4, 8, 1);
            renderer.DrawQuad(sx-2, sy+8, 8, 1);

            current_x += 10;
        }
    } else {
        // Flats: B E A D G C F
        static const int FlatNotesTreble[] = { 71, 76, 69, 74, 67, 72, 65 }; // B4, E5, A4, D5, G4, C5, F4
        static const int FlatNotesBass[] =   { 47, 52, 45, 50, 43, 48, 41 }; // B2, E3, A2, D3, G2, C3, F2

        const int* notes = (clef == Track::Bass) ? FlatNotesBass : FlatNotesTreble;

        for (int i = 0; i < -key_sf && i < 7; ++i) {
             int note_y = y + GetStaffY(notes[i], clef, key_sf);
             int sx = current_x;
             int sy = note_y;

             renderer.DrawQuad(sx, sy-4, 1, 14);
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
