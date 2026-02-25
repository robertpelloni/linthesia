// -*- mode: c++; coding: utf-8 -*-

// Linthesia

#include "KeyMapper.h"

KeyMapper::KeyMapper() : m_layout(LayoutQWERTY) {
    BuildQWERTY();
}

int KeyMapper::GetNote(SDL_Scancode scancode) const {
    auto it = m_map.find(scancode);
    if (it != m_map.end()) {
        return it->second;
    }
    return -1;
}

void KeyMapper::SetLayout(KeyboardLayout layout) {
    m_layout = layout;
    m_map.clear();
    switch (layout) {
        case LayoutQWERTY: BuildQWERTY(); break;
        case LayoutAZERTY: BuildAZERTY(); break; // Placeholder, same as QWERTY if scancodes are physical
        case LayoutQWERTZ: BuildQWERTZ(); break; // Placeholder
        default: BuildQWERTY(); break;
    }
}

std::string KeyMapper::GetLayoutName(KeyboardLayout layout) const {
    switch (layout) {
        case LayoutQWERTY: return "Standard (Physical)";
        case LayoutAZERTY: return "AZERTY (Logical)"; // Implies remapping logic if needed
        case LayoutQWERTZ: return "QWERTZ (Logical)";
        default: return "Unknown";
    }
}

void KeyMapper::BuildQWERTY() {
    const unsigned short oct = 4;

    // Row 1 (Numbers) - Black Keys
    // Row 2 (QWERTY) - White Keys (mostly)
    // The mapping from main.cpp:

    m_map[SDL_SCANCODE_GRAVE] = 12*oct + 1;      /* C# */
    m_map[SDL_SCANCODE_TAB]   = 12*oct + 2;      /* D  */
    m_map[SDL_SCANCODE_1]     = 12*oct + 3;      /* D# */
    m_map[SDL_SCANCODE_Q]     = 12*oct + 4;      /* E  */
    m_map[SDL_SCANCODE_W]     = 12*oct + 5;      /* F  */
    m_map[SDL_SCANCODE_3]     = 12*oct + 6;      /* F# */
    m_map[SDL_SCANCODE_E]     = 12*oct + 7;      /* G  */
    m_map[SDL_SCANCODE_4]     = 12*oct + 8;      /* G# */
    m_map[SDL_SCANCODE_R]     = 12*oct + 9;      /* A  */
    m_map[SDL_SCANCODE_5]     = 12*oct + 10;     /* A# */
    m_map[SDL_SCANCODE_T]     = 12*oct + 11;     /* B  */

    m_map[SDL_SCANCODE_Y]     = 12*(oct+1) + 0;  /* C  */
    m_map[SDL_SCANCODE_7]     = 12*(oct+1) + 1;  /* C# */
    m_map[SDL_SCANCODE_U]     = 12*(oct+1) + 2;  /* D  */
    m_map[SDL_SCANCODE_8]     = 12*(oct+1) + 3;  /* D# */
    m_map[SDL_SCANCODE_I]     = 12*(oct+1) + 4;  /* E  */
    m_map[SDL_SCANCODE_O]     = 12*(oct+1) + 5;  /* F  */
    m_map[SDL_SCANCODE_0]     = 12*(oct+1) + 6;  /* F# */
    m_map[SDL_SCANCODE_P]     = 12*(oct+1) + 7;  /* G  */
    m_map[SDL_SCANCODE_MINUS] = 12*(oct+1) + 8;  /* G# */
    m_map[SDL_SCANCODE_LEFTBRACKET]  = 12*(oct+1) + 9;  /* A  */
    m_map[SDL_SCANCODE_EQUALS]       = 12*(oct+1) + 10; /* A# */
    m_map[SDL_SCANCODE_RIGHTBRACKET] = 12*(oct+1) + 11; /* B  */
}

void KeyMapper::BuildAZERTY() {
    // If Scancodes are physical, this might be identical to QWERTY.
    // But if user expects 'A' key (QWERTY Q position) to map to 'A' note? No.
    // If we map logically (Letter -> Note), that's different.
    // Let's copy QWERTY for now, assuming physical mapping is desired.
    BuildQWERTY();
}

void KeyMapper::BuildQWERTZ() {
    BuildQWERTY();
}
