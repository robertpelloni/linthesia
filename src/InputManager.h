#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <gdk/gdk.h>
#include <set>
#include <string>
#include "GameState.h"

class InputManager {
public:
  InputManager(GameStateManager* state_manager);
  ~InputManager();

  bool OnKeyPress(const GdkEventKey* event);
  bool OnKeyRelease(const GdkEventKey* event);
  bool OnMotionNotify(const GdkEventMotion* event);
  bool OnButtonPress(const GdkEventButton* event);
  bool OnButtonRelease(const GdkEventButton* event);
  void OnTextInput(const std::string& text);
  void ResetAllNotes();

private:
  bool SendNoteOff(int note);

  GameStateManager* m_state_manager;
  std::set<int> m_pressed_notes;
};

#endif // INPUTMANAGER_H
