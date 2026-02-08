// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#include "SettingsState.h"
#include "TitleState.h"
#include "SharedState.h"
#include "UserSettings.h"
#include "CompatibleSystem.h"
#include "Renderer.h"
#include "Textures.h"
#include "MenuLayout.h"

#include <iomanip>
#include <sstream>

using namespace std;

// --- Helper Classes ---

class NumericValue : public EnumValue {
public:
  NumericValue(std::string key, long long min, long long max, long long step, long long def)
    : m_key(key), m_min(min), m_max(max), m_step(step) {
    std::string s = UserSetting::Get(key, std::to_string(def));
    try {
      m_val = std::stoll(s);
    } catch (...) { m_val = def; }
  }

  void next() override {
    m_val += m_step;
    if (m_val > m_max) m_val = m_max;
    save();
  }
  void previous() override {
    m_val -= m_step;
    if (m_val < m_min) m_val = m_min;
    save();
  }
  std::string AsText() const override {
    // microseconds -> seconds with 1 decimal
    double seconds = m_val / 1000000.0;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << seconds << " s";
    return ss.str();
  }

protected:
  void save() { UserSetting::Set(m_key, std::to_string(m_val)); }
  std::string m_key;
  long long m_val;
  long long m_min, m_max, m_step;
};

class FloatValue : public EnumValue {
public:
  FloatValue(std::string key, double min, double max, double step, double def)
    : m_key(key), m_min(min), m_max(max), m_step(step) {
    std::string s = UserSetting::Get(key, std::to_string(def));
    try {
      m_val = std::stod(s);
    } catch (...) { m_val = def; }
  }

  void next() override {
    m_val += m_step;
    if (m_val > m_max) m_val = m_max;
    save();
  }
  void previous() override {
    m_val -= m_step;
    if (m_val < m_min) m_val = m_min;
    save();
  }
  std::string AsText() const override {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << (m_val * 100) << "%";
    return ss.str();
  }

protected:
  void save() { UserSetting::Set(m_key, std::to_string(m_val)); }
  std::string m_key;
  double m_val;
  double m_min, m_max, m_step;
};

class BoolValue : public EnumValue {
public:
  BoolValue(std::string key, bool def) : m_key(key) {
    std::string s = UserSetting::Get(key, def ? "true" : "false");
    m_val = (s == "true" || s == "1");
  }

  void next() override {
    m_val = !m_val;
    save();
  }
  void previous() override {
    m_val = !m_val;
    save();
  }
  std::string AsText() const override { return m_val ? "On" : "Off"; }

protected:
  void save() { UserSetting::Set(m_key, m_val ? "true" : "false"); }
  std::string m_key;
  bool m_val;
};

// --- SettingsState Implementation ---

SettingsState::SettingsState(const SharedState &state) :
  m_state(state),
  m_lead_in_val(nullptr), m_lead_out_val(nullptr),
  m_scroll_speed_val(nullptr), m_metronome_on_val(nullptr),
  m_metronome_vol_val(nullptr),
  m_lead_in_tile(nullptr), m_lead_out_tile(nullptr),
  m_scroll_speed_tile(nullptr), m_metronome_on_tile(nullptr),
  m_metronome_vol_tile(nullptr)
{
}

SettingsState::~SettingsState() {
  delete m_lead_in_tile;
  delete m_lead_out_tile;
  delete m_scroll_speed_tile;
  delete m_metronome_on_tile;
  delete m_metronome_vol_tile;

  delete m_lead_in_val;
  delete m_lead_out_val;
  delete m_scroll_speed_val;
  delete m_metronome_on_val;
  delete m_metronome_vol_val;
}

void SettingsState::Init() {
  m_back_button = ButtonState(
     Layout::ScreenMarginX,
     GetStateHeight() - Layout::ScreenMarginY/2 - Layout::ButtonHeight/2,
     Layout::ButtonWidth, Layout::ButtonHeight);

  // Initialize Values
  // Defaults based on PlayingState.cpp constants
  m_lead_in_val = new NumericValue(LEAD_IN_TIME_KEY, 0, 10000000, 500000, 5500000); // 0-10s, 0.5s step
  m_lead_out_val = new NumericValue(LEAD_OUT_TIME_KEY, 0, 5000000, 500000, 1000000); // 0-5s
  m_scroll_speed_val = new NumericValue(SCROLL_SPEED_KEY, 1000000, 10000000, 250000, 3250000); // 1-10s visible
  m_metronome_on_val = new BoolValue(METRONOME_ON_KEY, false);
  m_metronome_vol_val = new FloatValue(METRONOME_VOLUME_KEY, 0.0, 2.0, 0.1, 1.0); // 0-200%

  // Create Tiles
  int y = 80;
  int gap = 90;

  m_lead_in_tile = new EnumTile((GetStateWidth() - EnumTileWidth)/2, y, *m_lead_in_val, "Lead-In Time:", GetTexture(InterfaceButtons), GetTexture(EmptyBox));
  y += gap;
  m_lead_out_tile = new EnumTile((GetStateWidth() - EnumTileWidth)/2, y, *m_lead_out_val, "Lead-Out Time:", GetTexture(InterfaceButtons), GetTexture(EmptyBox));
  y += gap;
  m_scroll_speed_tile = new EnumTile((GetStateWidth() - EnumTileWidth)/2, y, *m_scroll_speed_val, "Visible Duration:", GetTexture(InterfaceButtons), GetTexture(EmptyBox));
  y += gap;
  m_metronome_on_tile = new EnumTile((GetStateWidth() - EnumTileWidth)/2, y, *m_metronome_on_val, "Metronome:", GetTexture(InterfaceButtons), GetTexture(EmptyBox));
  y += gap;
  m_metronome_vol_tile = new EnumTile((GetStateWidth() - EnumTileWidth)/2, y, *m_metronome_vol_val, "Metronome Vol:", GetTexture(InterfaceButtons), GetTexture(EmptyBox));
}

void SettingsState::Resize() {
  m_back_button.SetX(Layout::ScreenMarginX);
  m_back_button.SetY(GetStateHeight() - Layout::ScreenMarginY/2 - Layout::ButtonHeight/2);

  int x = (GetStateWidth() - EnumTileWidth)/2;
  int y = 80;
  int gap = 90;

  if (m_lead_in_tile) { m_lead_in_tile->SetX(x); m_lead_in_tile->SetY(y); } y+=gap;
  if (m_lead_out_tile) { m_lead_out_tile->SetX(x); m_lead_out_tile->SetY(y); } y+=gap;
  if (m_scroll_speed_tile) { m_scroll_speed_tile->SetX(x); m_scroll_speed_tile->SetY(y); } y+=gap;
  if (m_metronome_on_tile) { m_metronome_on_tile->SetX(x); m_metronome_on_tile->SetY(y); } y+=gap;
  if (m_metronome_vol_tile) { m_metronome_vol_tile->SetX(x); m_metronome_vol_tile->SetY(y); }
}

void SettingsState::Update() {
  MouseInfo mouse = Mouse();

  m_back_button.Update(mouse);

  if (m_lead_in_tile) {
      MouseInfo local(mouse); local.x -= m_lead_in_tile->GetX(); local.y -= m_lead_in_tile->GetY();
      m_lead_in_tile->Update(local);
  }
  if (m_lead_out_tile) {
      MouseInfo local(mouse); local.x -= m_lead_out_tile->GetX(); local.y -= m_lead_out_tile->GetY();
      m_lead_out_tile->Update(local);
  }
  if (m_scroll_speed_tile) {
      MouseInfo local(mouse); local.x -= m_scroll_speed_tile->GetX(); local.y -= m_scroll_speed_tile->GetY();
      m_scroll_speed_tile->Update(local);
  }
  if (m_metronome_on_tile) {
      MouseInfo local(mouse); local.x -= m_metronome_on_tile->GetX(); local.y -= m_metronome_on_tile->GetY();
      m_metronome_on_tile->Update(local);
  }
  if (m_metronome_vol_tile) {
      MouseInfo local(mouse); local.x -= m_metronome_vol_tile->GetX(); local.y -= m_metronome_vol_tile->GetY();
      m_metronome_vol_tile->Update(local);
  }

  if (IsKeyPressed(KeyEscape) || m_back_button.hit) {
    ChangeState(new TitleState(m_state));
    return;
  }

  m_tooltip = "";
  if (m_back_button.hovering) m_tooltip = "Return to Title Screen.";
  // Add tooltips for tiles if desired
  if (m_lead_in_tile && m_lead_in_tile->WholeTile().hovering) m_tooltip = "Time before song starts (Lead-In).";
  if (m_lead_out_tile && m_lead_out_tile->WholeTile().hovering) m_tooltip = "Time after song ends (Lead-Out).";
  if (m_scroll_speed_tile && m_scroll_speed_tile->WholeTile().hovering) m_tooltip = "Amount of time visible on screen (Scroll Speed).";
  if (m_metronome_on_tile && m_metronome_on_tile->WholeTile().hovering) m_tooltip = "Enable visual metronome.";
  if (m_metronome_vol_tile && m_metronome_vol_tile->WholeTile().hovering) m_tooltip = "Adjust metronome volume.";
}

void SettingsState::Draw(Renderer &renderer) const {
  Layout::DrawTitle(renderer, "Settings");
  Layout::DrawHorizontalRule(renderer, GetStateWidth(), 60);

  Layout::DrawButton(renderer, m_back_button, GetTexture(ButtonBackToTitle));

  if (m_lead_in_tile) m_lead_in_tile->Draw(renderer);
  if (m_lead_out_tile) m_lead_out_tile->Draw(renderer);
  if (m_scroll_speed_tile) m_scroll_speed_tile->Draw(renderer);
  if (m_metronome_on_tile) m_metronome_on_tile->Draw(renderer);
  if (m_metronome_vol_tile) m_metronome_vol_tile->Draw(renderer);

  Layout::DrawHorizontalRule(renderer, GetStateWidth(), GetStateHeight() - Layout::ScreenMarginY);

  TextWriter tooltip(GetStateWidth() / 2,
                     GetStateHeight() - Layout::ScreenMarginY/2 - Layout::TitleFontSize/2,
                     renderer, true, Layout::TitleFontSize);
  tooltip << m_tooltip;
}
