#include "KeyMapper.h"
#include "UserSettings.h"
#include <iostream>

#ifndef KEYBOARD_LAYOUT_KEY
#define KEYBOARD_LAYOUT_KEY "keyboard-layout"
#endif

std::string KeyMapper::current_layout = "QWERTY";

void KeyMapper::Initialize() {
  current_layout = UserSetting::Get(KEYBOARD_LAYOUT_KEY, "QWERTY");
}

int KeyMapper::KeyToNote(const GdkEventKey* event) {
  const unsigned short oct = 4;
  guint keyval = event->keyval;

  if (current_layout == "QWERTY") {
    switch(keyval) {
      case GDK_KEY_grave:        return 12*oct + 1;      /* C# */
      case GDK_KEY_Tab:          return 12*oct + 2;      /* D  */
      case GDK_KEY_1:            return 12*oct + 3;      /* D# */
      case GDK_KEY_q:
      case GDK_KEY_Q:            return 12*oct + 4;      /* E  */
      case GDK_KEY_w:
      case GDK_KEY_W:            return 12*oct + 5;      /* F  */
      case GDK_KEY_3:            return 12*oct + 6;      /* F# */
      case GDK_KEY_e:
      case GDK_KEY_E:            return 12*oct + 7;      /* G  */
      case GDK_KEY_4:            return 12*oct + 8;      /* G# */
      case GDK_KEY_r:
      case GDK_KEY_R:            return 12*oct + 9;      /* A  */
      case GDK_KEY_5:            return 12*oct + 10;     /* A# */
      case GDK_KEY_t:
      case GDK_KEY_T:            return 12*oct + 11;     /* B  */

      case GDK_KEY_y:
      case GDK_KEY_Y:            return 12*(oct+1) + 0;  /* C  */
      case GDK_KEY_7:            return 12*(oct+1) + 1;  /* C# */
      case GDK_KEY_u:
      case GDK_KEY_U:            return 12*(oct+1) + 2;  /* D  */
      case GDK_KEY_8:            return 12*(oct+1) + 3;  /* D# */
      case GDK_KEY_i:
      case GDK_KEY_I:            return 12*(oct+1) + 4;  /* E  */
      case GDK_KEY_o:
      case GDK_KEY_O:            return 12*(oct+1) + 5;  /* F  */
      case GDK_KEY_0:            return 12*(oct+1) + 6;  /* F# */
      case GDK_KEY_p:
      case GDK_KEY_P:            return 12*(oct+1) + 7;  /* G  */
      case GDK_KEY_minus:        return 12*(oct+1) + 8;  /* G# */
      case GDK_KEY_bracketleft:  return 12*(oct+1) + 9;  /* A  */
      case GDK_KEY_equal:        return 12*(oct+1) + 10; /* A# */
      case GDK_KEY_bracketright: return 12*(oct+1) + 11; /* B  */
    }
  } else if (current_layout == "AZERTY") {
    switch(keyval) {
      case GDK_KEY_twosuperior:  return 12*oct + 1;      /* C# */
      case GDK_KEY_Tab:          return 12*oct + 2;      /* D  */
      case GDK_KEY_ampersand:    return 12*oct + 3;      /* D# */
      case GDK_KEY_a:
      case GDK_KEY_A:            return 12*oct + 4;      /* E  */
      case GDK_KEY_z:
      case GDK_KEY_Z:            return 12*oct + 5;      /* F  */
      case GDK_KEY_quotedbl:     return 12*oct + 6;      /* F# */
      case GDK_KEY_e:
      case GDK_KEY_E:            return 12*oct + 7;      /* G  */
      case GDK_KEY_apostrophe:   return 12*oct + 8;      /* G# */
      case GDK_KEY_r:
      case GDK_KEY_R:            return 12*oct + 9;      /* A  */
      case GDK_KEY_parenleft:    return 12*oct + 10;     /* A# */
      case GDK_KEY_t:
      case GDK_KEY_T:            return 12*oct + 11;     /* B  */

      case GDK_KEY_y:
      case GDK_KEY_Y:            return 12*(oct+1) + 0;  /* C  */
      case GDK_KEY_egrave:       return 12*(oct+1) + 1;  /* C# */
      case GDK_KEY_u:
      case GDK_KEY_U:            return 12*(oct+1) + 2;  /* D  */
      case GDK_KEY_underscore:   return 12*(oct+1) + 3;  /* D# */
      case GDK_KEY_i:
      case GDK_KEY_I:            return 12*(oct+1) + 4;  /* E  */
      case GDK_KEY_o:
      case GDK_KEY_O:            return 12*(oct+1) + 5;  /* F  */
      case GDK_KEY_agrave:       return 12*(oct+1) + 6;  /* F# */
      case GDK_KEY_p:
      case GDK_KEY_P:            return 12*(oct+1) + 7;  /* G  */
      case GDK_KEY_parenright:   return 12*(oct+1) + 8;  /* G# */
      case GDK_KEY_dead_circumflex: return 12*(oct+1) + 9;  /* A  */
      case GDK_KEY_equal:        return 12*(oct+1) + 10; /* A# */
      case GDK_KEY_dollar:       return 12*(oct+1) + 11; /* B  */
    }
  } else if (current_layout == "QWERTZ") {
    switch(keyval) {
      case GDK_KEY_dead_circumflex: return 12*oct + 1;      /* C# */
      case GDK_KEY_Tab:          return 12*oct + 2;      /* D  */
      case GDK_KEY_1:            return 12*oct + 3;      /* D# */
      case GDK_KEY_q:
      case GDK_KEY_Q:            return 12*oct + 4;      /* E  */
      case GDK_KEY_w:
      case GDK_KEY_W:            return 12*oct + 5;      /* F  */
      case GDK_KEY_3:            return 12*oct + 6;      /* F# */
      case GDK_KEY_e:
      case GDK_KEY_E:            return 12*oct + 7;      /* G  */
      case GDK_KEY_4:            return 12*oct + 8;      /* G# */
      case GDK_KEY_r:
      case GDK_KEY_R:            return 12*oct + 9;      /* A  */
      case GDK_KEY_5:            return 12*oct + 10;     /* A# */
      case GDK_KEY_t:
      case GDK_KEY_T:            return 12*oct + 11;     /* B  */

      case GDK_KEY_z:
      case GDK_KEY_Z:            return 12*(oct+1) + 0;  /* C  */
      case GDK_KEY_7:            return 12*(oct+1) + 1;  /* C# */
      case GDK_KEY_u:
      case GDK_KEY_U:            return 12*(oct+1) + 2;  /* D  */
      case GDK_KEY_8:            return 12*(oct+1) + 3;  /* D# */
      case GDK_KEY_i:
      case GDK_KEY_I:            return 12*(oct+1) + 4;  /* E  */
      case GDK_KEY_o:
      case GDK_KEY_O:            return 12*(oct+1) + 5;  /* F  */
      case GDK_KEY_0:            return 12*(oct+1) + 6;  /* F# */
      case GDK_KEY_p:
      case GDK_KEY_P:            return 12*(oct+1) + 7;  /* G  */
      case GDK_KEY_ssharp:       return 12*(oct+1) + 8;  /* G# */
      case GDK_KEY_udiaeresis:   return 12*(oct+1) + 9;  /* A  */
      case GDK_KEY_dead_acute:   return 12*(oct+1) + 10; /* A# */
      case GDK_KEY_plus:         return 12*(oct+1) + 11; /* B  */
    }
  }

  return -1;
}
