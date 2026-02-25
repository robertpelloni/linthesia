// -*- mode: c++; coding: utf-8 -*-

// Linthesia

#ifndef __KEY_MAPPER_H
#define __KEY_MAPPER_H

#include <SDL.h>
#include <map>
#include <string>

enum KeyboardLayout {
    LayoutQWERTY,
    LayoutAZERTY,
    LayoutQWERTZ,
    LayoutCount
};

class KeyMapper {
public:
    KeyMapper();

    // Returns note number (0-127) or -1 if not mapped
    int GetNote(SDL_Scancode scancode) const;

    void SetLayout(KeyboardLayout layout);
    KeyboardLayout GetLayout() const { return m_layout; }

    std::string GetLayoutName(KeyboardLayout layout) const;

private:
    KeyboardLayout m_layout;
    std::map<SDL_Scancode, int> m_map;

    void BuildQWERTY();
    void BuildAZERTY();
    void BuildQWERTZ();
};

extern KeyMapper g_key_mapper;

#endif // __KEY_MAPPER_H
