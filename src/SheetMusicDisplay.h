// -*- mode: c++; coding: utf-8 -*-

// Linthesia

#ifndef __SHEET_MUSIC_DISPLAY_H
#define __SHEET_MUSIC_DISPLAY_H

#include "libmidi/Midi.h"
#include "Renderer.h"
#include "TrackProperties.h"
#include <vector>

class SheetMusicDisplay {
public:
    SheetMusicDisplay(int width, int height);

    void Draw(Renderer &renderer, int x, int y,
              const TranslatedNoteSet &notes,
              microseconds_t show_duration,
              microseconds_t current_time,
              const std::vector<Track::Properties> &track_properties,
              const MidiEventMicrosecondList &bar_lines,
              int key_sf, int key_mi);

private:
    void DrawClef(Renderer &renderer, int x, int y);
    void DrawKeySignature(Renderer &renderer, int x, int y, int key_sf);
    int m_width;
    int m_height;

    void DrawStaff(Renderer &renderer, int x, int y, int width);
    void DrawNote(Renderer &renderer, int x, int y, int note_id, Track::TrackColor color, bool draw_stem = true);
    void DrawStem(Renderer &renderer, int x, int y, bool stem_up);

    // Convert MIDI note number to vertical offset from F5
    int GetStaffY(int note_id);

    struct NoteCoord {
        int x;
        int y;
        bool stem_up;
        int note_id;
    };

    void DrawBeam(Renderer &renderer, const std::vector<NoteCoord> &notes);

    void DrawBarLines(Renderer &renderer, int x, int y, int width, int height,
                      microseconds_t show_duration, microseconds_t current_time,
                      const MidiEventMicrosecondList &bar_lines);
};

#endif // __SHEET_MUSIC_DISPLAY_H
