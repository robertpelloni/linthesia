#include "SheetMusicDisplay.h"
#include <iostream>

using namespace std;

SheetMusicDisplay::SheetMusicDisplay(int pixelWidth, int pixelHeight)
  : m_width(pixelWidth), m_height(pixelHeight) {
}

void SheetMusicDisplay::Draw(Renderer &renderer, int x, int y, const TranslatedNoteSet &notes, microseconds_t show_duration,
                             microseconds_t current_time, const std::vector<Track::Properties> &track_properties,
                             const MidiEventMicrosecondList &bar_line_usecs) {

  // Background for the sheet music
  renderer.SetColor(Renderer::ToColor(240, 240, 240, 255)); renderer.DrawQuad(x, y, m_width, m_height);

  DrawStaffLines(renderer, x, y, m_width, m_height);
  DrawClefs(renderer, x, y, m_width, m_height);
  DrawNotes(renderer, x, y, m_width, m_height, notes, show_duration, current_time, track_properties);
}

void SheetMusicDisplay::DrawStaffLines(Renderer &renderer, int x, int y, int width, int height) const {

  int staffHeight = height / 4;
  int topY = y + staffHeight;
  int bottomY = y + staffHeight * 3;
  int lineSpacing = 10;

  // Treble
  for (int i = 0; i < 5; ++i) {
      renderer.SetColor(Renderer::ToColor(0, 0, 0, 255)); renderer.DrawQuad(x, topY + i * lineSpacing, width, 2);
  }

  // Bass
  for (int i = 0; i < 5; ++i) {
      renderer.SetColor(Renderer::ToColor(0, 0, 0, 255)); renderer.DrawQuad(x, bottomY - i * lineSpacing, width, 2);
  }
}

void SheetMusicDisplay::DrawClefs(Renderer &renderer, int x, int y, int width, int height) const {
  // Simple rendering of text for clefs since drawing splines is hard without textures
  int staffHeight = height / 4;
  int topY = y + staffHeight;
  int bottomY = y + staffHeight * 3;

  // renderer.DrawText doesn't exist? Wait, we can use TextWriter?
  // Let's keep it simple. It's just a placeholder procedural generation right now
}

void SheetMusicDisplay::DrawNotes(Renderer &renderer, int x, int y, int width, int height,
                 const TranslatedNoteSet &notes, microseconds_t show_duration,
                 microseconds_t current_time, const std::vector<Track::Properties> &track_properties) const {
  // Procedural notes implementation


  for (const auto& note : notes) {
      if (note.start < current_time + show_duration && note.end > current_time) {
          int noteX = x + width - ((note.start - current_time) * width) / show_duration;

          if (noteX < x || noteX > x + width) continue;

          // Simple vertical positioning based on note number
          // Middle C (60) is between staffs.
          int noteY = y + height / 2 - (note.note_id - 60) * 5;
          renderer.SetColor(Track::ColorNoteWhite[track_properties[note.track_id].color]); renderer.DrawQuad(noteX, noteY, 12, 8); // placeholder note head
      }
  }
}
