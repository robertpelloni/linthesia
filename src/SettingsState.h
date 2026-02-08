// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#ifndef __SETTINGS_STATE_H
#define __SETTINGS_STATE_H

#include "GameState.h"
#include "MenuLayout.h"
#include "EnumTile.h"
#include "SharedState.h"

class SettingsState : public GameState {
public:
  SettingsState(const SharedState &state);
  ~SettingsState();

protected:
  virtual void Init();
  virtual void Update();
  virtual void Resize();
  virtual void Draw(Renderer &renderer) const;

private:
  SharedState m_state;

  ButtonState m_back_button;
  std::string m_tooltip;

  // EnumValues (need to be pointers because they are abstract classes)
  EnumValue* m_lead_in_val;
  EnumValue* m_lead_out_val;
  EnumValue* m_scroll_speed_val;
  EnumValue* m_metronome_on_val;
  EnumValue* m_metronome_vol_val;

  // Tiles
  EnumTile* m_lead_in_tile;
  EnumTile* m_lead_out_tile;
  EnumTile* m_scroll_speed_tile;
  EnumTile* m_metronome_on_tile;
  EnumTile* m_metronome_vol_tile;
};

#endif // __SETTINGS_STATE_H
