#ifndef KEYMAPPER_H
#define KEYMAPPER_H

#include <gdk/gdk.h>
#include <string>

class KeyMapper {
public:
  static void Initialize();
  static int KeyToNote(const GdkEventKey* event);

private:
  static int GetLayout();
  static std::string current_layout;
};

#endif // KEYMAPPER_H
