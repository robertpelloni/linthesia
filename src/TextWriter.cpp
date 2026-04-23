// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#include "TextWriter.h"
#include "Renderer.h"
#include "LinthesiaError.h"
#include "OSGraphics.h"
#include "UserSettings.h"

#include <iostream>
#include <cairomm/cairomm.h>
#include <pangomm.h>
#include <GL/gl.h>

using namespace std;

// Extracting just the font name without path/extension since Pango
// resolves via fontconfig on Linux rather than direct TTF paths.
static std::string ExtractFontFamily(const std::string& fontname) {
    if (fontname == "FreeSans.ttf") return "FreeSans";
    // basic strip
    size_t dot = fontname.find_last_of('.');
    if (dot != std::string::npos) {
        return fontname.substr(0, dot);
    }
    return fontname;
}

TextWriter::TextWriter(int in_x, int in_y, Renderer &in_renderer,
                       bool in_centered, int in_size, string fontname) :
  x(in_x),
  y(in_y),
  size(in_size),
  original_x(0),
  last_line_height(0),
  centered(in_centered),
  renderer(in_renderer) {

  x += renderer.m_xoffset;
  original_x = x;

  y += renderer.m_yoffset;
  point_size = size;

  std::string family = ExtractFontFamily(fontname);
  font_desc.set_family(family);
  font_desc.set_size(in_size * PANGO_SCALE);
}

int TextWriter::get_point_size() {
  return point_size;
}

TextWriter& TextWriter::next_line() {
  y += max(last_line_height, get_point_size());
  x = original_x;

  last_line_height = 0;
  return *this;
}

void Text::DrawText(TextWriter& tw, Color color, int draw_x, int draw_y) const
{
  // 1. Create a minimal surface to get a layout context for measuring
  auto temp_surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 1, 1);
  auto temp_cr = Cairo::Context::create(temp_surface);
  auto layout = Pango::Layout::create(temp_cr);

  layout->set_text(m_text);
  layout->set_font_description(tw.font_desc);

  int width, height;
  layout->get_pixel_size(width, height);

  if (width == 0 || height == 0) return;

  // 2. Create the actual surface for rendering
  auto surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width, height);
  auto cr = Cairo::Context::create(surface);

  // Clear with transparent background
  cr->set_source_rgba(0, 0, 0, 0);
  cr->set_operator(Cairo::OPERATOR_SOURCE);
  cr->paint();

  // Draw text
  cr->set_source_rgba(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
  cr->move_to(0, 0);
  layout->update_from_cairo_context(cr);
  layout->show_in_cairo_context(cr);

  surface->flush();
  unsigned char* pixels = surface->get_data();

  // 3. Upload to OpenGL
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Cairo FORMAT_ARGB32 uses pre-multiplied BGRA pixels on little-endian
  glPixelStorei(GL_UNPACK_ROW_LENGTH, surface->get_stride() / 4);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

  glPushMatrix();
  tw.renderer.SetColor(White); // Texture contains actual color
  glBegin(GL_QUADS);
  {
    glTexCoord2f(0,0); glVertex2f(draw_x, draw_y);
    glTexCoord2f(1,0); glVertex2f(draw_x + width, draw_y);
    glTexCoord2f(1,1); glVertex2f(draw_x + width, draw_y + height);
    glTexCoord2f(0,1); glVertex2f(draw_x, draw_y + height);
  }
  glEnd();

  glPopMatrix();
  glDeleteTextures(1, &texture);
}

TextWriter& Text::operator<<(TextWriter& tw) const {
  int draw_x = 0;
  int draw_y = 0;

  if (m_text.size() == 0)
    return tw;

  calculate_position_and_advance_cursor(tw, &draw_x, &draw_y);

  if (m_attrs.has_shadow)
    DrawText(tw, m_attrs.shadow, draw_x + 2, draw_y + 2);

  DrawText(tw, m_attrs.color, draw_x, draw_y);

  return tw;
}

void Text::calculate_position_and_advance_cursor(TextWriter &tw, int *out_x, int *out_y) const {
  auto temp_surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 1, 1);
  auto temp_cr = Cairo::Context::create(temp_surface);
  auto layout = Pango::Layout::create(temp_cr);

  layout->set_text(m_text);
  layout->set_font_description(tw.font_desc);

  int width, height;
  layout->get_pixel_size(width, height);

  if (tw.centered) {
    *out_x = tw.x - width / 2;
  }
  else {
    *out_x = tw.x;
    tw.x += width;
  }
  *out_y = tw.y;
}

TextWriter& operator<<(TextWriter& tw, const Text& t) {
  return t.operator <<(tw);
}

TextWriter& newline(TextWriter& tw) {
  return tw.next_line();
}

TextWriter& operator<<(TextWriter& tw, const string& s)        { return tw << Text(s, White); }
TextWriter& operator<<(TextWriter& tw, const int& i)           { return tw << Text(i, White); }
TextWriter& operator<<(TextWriter& tw, const unsigned int& i)  { return tw << Text(i, White); }
TextWriter& operator<<(TextWriter& tw, const long& l)          { return tw << Text(l, White); }
TextWriter& operator<<(TextWriter& tw, const unsigned long& l) { return tw << Text(l, White); }
