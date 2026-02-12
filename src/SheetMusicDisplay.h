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
              const std::vector<Track::Properties> &track_properties);

private:
    int m_width;
    int m_height;

    void DrawStaff(Renderer &renderer, int x, int y, int width);
    void DrawNote(Renderer &renderer, int x, int y, int note_id, Track::TrackColor color);

    // Convert MIDI note number to vertical offset from Middle C (60)
    int GetStaffY(int note_id);
};

#endif // __SHEET_MUSIC_DISPLAY_H
