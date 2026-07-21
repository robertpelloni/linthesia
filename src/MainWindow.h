#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include "GameState.h"
#include "InputManager.h"
#include "Renderer.h"
#include "SharedState.h"
#include "DpmsThread.h"
#include "libmidi/Midi.h"

class MainWindow : public Gtk::Window {
public:
  MainWindow(GameStateManager* state_manager, InputManager* input_manager);
  virtual ~MainWindow();

protected:
  // GTK signal handlers
  bool on_key_press_event(GdkEventKey* event) override;
  bool on_key_release_event(GdkEventKey* event) override;
  bool on_motion_notify_event(GdkEventMotion* event) override;
  bool on_button_press_event(GdkEventButton* event) override;
  bool on_button_release_event(GdkEventButton* event) override;

  // GLArea signals
  void on_gl_realize();
  void on_gl_unrealize();
  bool on_render(const Glib::RefPtr<Gdk::GLContext>& context);
  void on_gl_resize(int width, int height);
  bool on_timeout();

private:
  Gtk::GLArea m_gl_area;
  GameStateManager* m_state_manager;
  InputManager* m_input_manager;
};

#endif // MAINWINDOW_H
