#include "InputManager.h"
#include "MidiComm.h"

InputManager::InputManager(GameStateManager* state_manager)
    : m_state_manager(state_manager) {}

bool InputManager::on_motion_notify(GdkEventMotion* event) {
  m_state_manager->MouseMove(event->x, event->y);
  return true;
}

bool InputManager::on_button_press(GdkEventButton* event) {
  MouseButton b;

  if (event->button == 1)
    b = MouseLeft;
  else if (event->button == 3)
    b = MouseRight;
  else
    return false;

  if (event->type == GDK_BUTTON_PRESS)
    m_state_manager->MousePress(b);
  else if (event->type == GDK_BUTTON_RELEASE)
    m_state_manager->MouseRelease(b);
  else
    return false;

  return true;
}

// FIXME: use user settings to do this mapping
int InputManager::keyToNote(GdkEventKey* event) {
  const unsigned short oct = 4;

  switch (event->keyval) {
    case GDK_KEY_grave:        return 12 * oct + 1;      /* C# */
    case GDK_KEY_Tab:          return 12 * oct + 2;      /* D  */
    case GDK_KEY_1:            return 12 * oct + 3;      /* D# */
    case GDK_KEY_q:            return 12 * oct + 4;      /* E  */
    case GDK_KEY_w:            return 12 * oct + 5;      /* F  */
    case GDK_KEY_3:            return 12 * oct + 6;      /* F# */
    case GDK_KEY_e:            return 12 * oct + 7;      /* G  */
    case GDK_KEY_4:            return 12 * oct + 8;      /* G# */
    case GDK_KEY_r:            return 12 * oct + 9;      /* A  */
    case GDK_KEY_5:            return 12 * oct + 10;     /* A# */
    case GDK_KEY_t:            return 12 * oct + 11;     /* B  */

    case GDK_KEY_y:            return 12 * (oct + 1) + 0;  /* C  */
    case GDK_KEY_7:            return 12 * (oct + 1) + 1;  /* C# */
    case GDK_KEY_u:            return 12 * (oct + 1) + 2;  /* D  */
    case GDK_KEY_8:            return 12 * (oct + 1) + 3;  /* D# */
    case GDK_KEY_i:            return 12 * (oct + 1) + 4;  /* E  */
    case GDK_KEY_o:            return 12 * (oct + 1) + 5;  /* F  */
    case GDK_KEY_0:            return 12 * (oct + 1) + 6;  /* F# */
    case GDK_KEY_p:            return 12 * (oct + 1) + 7;  /* G  */
    case GDK_KEY_minus:        return 12 * (oct + 1) + 8;  /* G# */
    case GDK_KEY_bracketleft:  return 12 * (oct + 1) + 9;  /* A  */
    case GDK_KEY_equal:        return 12 * (oct + 1) + 10; /* A# */
    case GDK_KEY_bracketright: return 12 * (oct + 1) + 11; /* B  */
    default: return -1;
  }
}

bool InputManager::on_key_press(GdkEventKey* event) {
  int note = keyToNote(event);
  if (note >= 0) {
    if (pressed_notes.find(note) == pressed_notes.end()) {
      sendNote(note, true);
      pressed_notes.insert(note);
    }
    return true;
  }

  switch (event->keyval) {
    case GDK_KEY_Up:       m_state_manager->KeyPress(KeyUp);      break;
    case GDK_KEY_Down:     m_state_manager->KeyPress(KeyDown);    break;
    case GDK_KEY_Left:     m_state_manager->KeyPress(KeyLeft);    break;
    case GDK_KEY_Right:    m_state_manager->KeyPress(KeyRight);   break;
    case GDK_KEY_space:    m_state_manager->KeyPress(KeySpace);   break;
    case GDK_KEY_Return:   m_state_manager->KeyPress(KeyEnter);   break;
    case GDK_KEY_Escape:   m_state_manager->KeyPress(KeyEscape);  break;
    case GDK_KEY_BackSpace: m_state_manager->KeyPress(KeyBackspace); break;
    case GDK_KEY_F6:       m_state_manager->KeyPress(KeyF6);      break;
    case GDK_KEY_F7:       m_state_manager->KeyPress(KeyF7);      break;
    case GDK_KEY_period:    m_state_manager->KeyPress(KeyGreater); break;
    case GDK_KEY_comma:     m_state_manager->KeyPress(KeyLess);    break;
    case GDK_KEY_Page_Down: m_state_manager->KeyPress(KeyForward);  break;
    case GDK_KEY_Page_Up:   m_state_manager->KeyPress(KeyBackward); break;
    case GDK_KEY_KP_Add:  m_state_manager->KeyPress(KeyVolumeDown); break;
    case GDK_KEY_KP_Subtract: m_state_manager->KeyPress(KeyVolumeUp);   break;
    default:
      return false;
  }

  return true;
}


bool InputManager::on_key_release(GdkEventKey* event) {
  int note = keyToNote(event);
  if (note >= 0) {
    auto it = pressed_notes.find(note);
    if (it != pressed_notes.end()) {
      sendNote(note, false);
      pressed_notes.erase(it);
    }
    return true;
  }

  return false;
}
