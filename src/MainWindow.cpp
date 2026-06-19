#include "MainWindow.h"
#include "Renderer.h"
#include <iostream>

// Defined in main.cpp

extern int vsync_interval;

MainWindow::MainWindow(GameStateManager* state_manager, InputManager* input_manager)
    : m_state_manager(state_manager),
      m_input_manager(input_manager) {

  set_title("Linthesia");
  set_default_size(1280, 720);

  m_gl_area.set_has_depth_buffer(false);
  m_gl_area.set_auto_render(true);

  m_gl_area.signal_render().connect(sigc::mem_fun(*this, &MainWindow::on_render));
  m_gl_area.signal_realize().connect(sigc::mem_fun(*this, &MainWindow::on_realize));
  m_gl_area.signal_unrealize().connect(sigc::mem_fun(*this, &MainWindow::on_unrealize));
  m_gl_area.signal_resize().connect(sigc::mem_fun(*this, &MainWindow::on_resize));

  m_gl_area.set_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK |
                       Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK |
                       Gdk::BUTTON_RELEASE_MASK);
  m_gl_area.set_can_focus(true);

  add(m_gl_area);
  m_gl_area.show();

  // Start the main loop timer (approx 60fps)
  m_timeout_connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &MainWindow::on_timeout), 16);
}

MainWindow::~MainWindow() {
  m_timeout_connection.disconnect();
}

bool MainWindow::on_key_press_event(GdkEventKey* key_event) {
  return m_input_manager->on_key_press(key_event);
}

bool MainWindow::on_key_release_event(GdkEventKey* key_event) {
  return m_input_manager->on_key_release(key_event);
}

bool MainWindow::on_button_press_event(GdkEventButton* button_event) {
  return m_input_manager->on_button_press(button_event);
}

bool MainWindow::on_button_release_event(GdkEventButton* release_event) {
  return m_input_manager->on_button_press(release_event); // The manager handles both
}

bool MainWindow::on_motion_notify_event(GdkEventMotion* motion_event) {
  return m_input_manager->on_motion_notify(motion_event);
}

void MainWindow::on_realize() {
  m_gl_area.make_current();
}

void MainWindow::on_unrealize() {
  m_gl_area.make_current();
}

void MainWindow::on_resize(int width, int height) {
  m_gl_area.make_current();
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1, 1);
  m_state_manager->SetStateDimensions(width, height);
}

bool MainWindow::on_render(const Glib::RefPtr<Gdk::GLContext>& context) {
  glClearColor(.25, .25, .25, 1.0);
  glClearDepth(1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glShadeModel(GL_SMOOTH);

  if (true) {
    Renderer rend(context, PGContext(nullptr));
    rend.SetVSyncInterval(vsync_interval);
    m_state_manager->Draw(rend);
  }

  // Flush errors (optional but good practice)
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL Error: " << err << std::endl;
  }

  return true;
}

bool MainWindow::on_timeout() {
  // Update game logic
  m_state_manager->Update(false);

  // Queue a redraw
  m_gl_area.queue_draw();

  return true; // Keep the timer running
}
