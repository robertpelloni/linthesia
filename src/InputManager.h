#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <gtkmm.h>
#include <set>
#include "GameState.h"

class InputManager {
public:
  InputManager(GameStateManager* state_manager);
  ~InputManager() = default;



public:
  bool on_motion_notify(GdkEventMotion* event);
  bool on_button_press(GdkEventButton* event);
  bool on_key_press(GdkEventKey* event);
  bool on_key_release(GdkEventKey* event);

  int keyToNote(GdkEventKey* event);

  GameStateManager* m_state_manager;
  std::set<int> pressed_notes;
};

#endif // INPUTMANAGER_H
