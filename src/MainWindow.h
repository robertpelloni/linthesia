#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include "GameState.h"
#include "InputManager.h"

class MainWindow : public Gtk::Window {
public:
  MainWindow(GameStateManager* state_manager, InputManager* input_manager);
  virtual ~MainWindow();

protected:
  // Override default signal handlers
  bool on_key_press_event(GdkEventKey* key_event) override;
  bool on_key_release_event(GdkEventKey* key_event) override;
  bool on_button_press_event(GdkEventButton* button_event) override;
  bool on_button_release_event(GdkEventButton* release_event) override;
  bool on_motion_notify_event(GdkEventMotion* motion_event) override;

  // GLArea signals
  bool on_render(const Glib::RefPtr<Gdk::GLContext>& context);
  void on_realize();
  void on_unrealize();
  void on_resize(int width, int height);

  // Main loop timer
  bool on_timeout();

private:
  Gtk::GLArea m_gl_area;
  GameStateManager* m_state_manager;
  InputManager* m_input_manager;
  sigc::connection m_timeout_connection;
};

#endif // MAINWINDOW_H
