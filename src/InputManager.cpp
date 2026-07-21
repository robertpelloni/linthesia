#include "InputManager.h"
#include "KeyMapper.h"
#include "MidiComm.h"

InputManager::InputManager(GameStateManager* state_manager)
    : m_state_manager(state_manager) {
    KeyMapper::Initialize();
}

InputManager::~InputManager() {
    ResetAllNotes();
}

bool InputManager::SendNoteOff(int note) {
    auto it = m_pressed_notes.find(note);
    if (it == m_pressed_notes.end())
        return false;

    sendNote(note, false);
    MidiEvent ev = MidiEvent::Build(MidiEventSimple(0x80, note, 0));
    m_state_manager->OnMidiEvent(ev);
    m_pressed_notes.erase(it);

    return true;
}

void InputManager::ResetAllNotes() {
    for (int note : m_pressed_notes) {
        sendNote(note, false);
    }
    m_pressed_notes.clear();
}

bool InputManager::OnKeyPress(const GdkEventKey* event) {
    int note = KeyMapper::KeyToNote(event);
    if (note >= 0) {
        auto it = m_pressed_notes.find(note);
        if (it == m_pressed_notes.end()) {
            sendNote(note, true);
            MidiEvent ev = MidiEvent::Build(MidiEventSimple(0x90, note, 127));
            m_state_manager->OnMidiEvent(ev);
            m_pressed_notes.insert(note);
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
        case GDK_KEY_BackSpace:m_state_manager->KeyPress(KeyBackspace); break;

        case GDK_KEY_F1:       m_state_manager->KeyPress(KeyLoopA);      break;
        case GDK_KEY_F2:       m_state_manager->KeyPress(KeyLoopB);      break;
        case GDK_KEY_F6:       m_state_manager->KeyPress(KeyF6);      break;
        case GDK_KEY_F7:       m_state_manager->KeyPress(KeyF7);      break;

        case GDK_KEY_period:   m_state_manager->KeyPress(KeyGreater); break;
        case GDK_KEY_comma:    m_state_manager->KeyPress(KeyLess);    break;

        case GDK_KEY_Page_Down:m_state_manager->KeyPress(KeyForward);  break;
        case GDK_KEY_Page_Up:  m_state_manager->KeyPress(KeyBackward); break;

        case GDK_KEY_KP_Add:   m_state_manager->KeyPress(KeyVolumeDown); break;
        case GDK_KEY_KP_Subtract: m_state_manager->KeyPress(KeyVolumeUp);   break;

        default:
            return false;
    }
    return true;
}

bool InputManager::OnKeyRelease(const GdkEventKey* event) {
    int note = KeyMapper::KeyToNote(event);
    if (note >= 0) {
        SendNoteOff(note);
        return true;
    }
    return false;
}

bool InputManager::OnMotionNotify(const GdkEventMotion* event) {
    m_state_manager->MouseMove(static_cast<int>(event->x), static_cast<int>(event->y));
    return true;
}

bool InputManager::OnButtonPress(const GdkEventButton* event) {
    MouseButton b;
    if (event->button == 1)
        b = MouseLeft;
    else if (event->button == 3)
        b = MouseRight;
    else
        return false;

    m_state_manager->MousePress(b);
    return true;
}

bool InputManager::OnButtonRelease(const GdkEventButton* event) {
    MouseButton b;
    if (event->button == 1)
        b = MouseLeft;
    else if (event->button == 3)
        b = MouseRight;
    else
        return false;

    m_state_manager->MouseRelease(b);
    return true;
}

void InputManager::OnTextInput(const std::string& text) {
    m_state_manager->TextInput(text);
}
