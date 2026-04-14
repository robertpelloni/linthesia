// -*- mode: c++; coding: utf-8 -*-

#ifndef __SHEETMUSICDISPLAY_H
#define __SHEETMUSICDISPLAY_H

#include <vector>
#include <string>

#include "TrackTile.h"
#include "TrackProperties.h"

#include "libmidi/Note.h"
#include "libmidi/MidiTypes.h"
#include "Renderer.h"

class SheetMusicDisplay {
public:
  SheetMusicDisplay(int pixelWidth, int pixelHeight);

  void Draw(Renderer &renderer, int x, int y, const TranslatedNoteSet &notes, microseconds_t show_duration,
            microseconds_t current_time, const std::vector<Track::Properties> &track_properties,
            const MidiEventMicrosecondList &bar_line_usecs);

private:
  void DrawStaffLines(Renderer &renderer, int x, int y, int width, int height) const;
  void DrawClefs(Renderer &renderer, int x, int y, int width, int height) const;
  void DrawNotes(Renderer &renderer, int x, int y, int width, int height,
                 const TranslatedNoteSet &notes, microseconds_t show_duration,
                 microseconds_t current_time, const std::vector<Track::Properties> &track_properties) const;

  int m_width;
  int m_height;
};

#endif // __SHEETMUSICDISPLAY_H
