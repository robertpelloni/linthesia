#include "MainWindow.h"
#include "Textures.h"
#include <iostream>
#include <GL/gl.h>

MainWindow::MainWindow(GameStateManager* state_manager, InputManager* input_manager)
    : m_state_manager(state_manager),
      m_input_manager(input_manager)
{
    set_title("Linthesia");
    set_default_size(1280, 720);

    // Setup GLArea
    m_gl_area.set_has_depth_buffer(true);
    m_gl_area.set_has_alpha(true);

    m_gl_area.signal_realize().connect(sigc::mem_fun(*this, &MainWindow::on_gl_realize));
    m_gl_area.signal_unrealize().connect(sigc::mem_fun(*this, &MainWindow::on_gl_unrealize));
    m_gl_area.signal_render().connect(sigc::mem_fun(*this, &MainWindow::on_render));
    m_gl_area.signal_resize().connect(sigc::mem_fun(*this, &MainWindow::on_gl_resize));

    add(m_gl_area);

    // Setup events
    add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK |
               Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);

    show_all_children();

    // Setup a 60 FPS update loop
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &MainWindow::on_timeout), 16);
}

MainWindow::~MainWindow() {
}

bool MainWindow::on_timeout() {
    m_state_manager->Update(false);
    m_gl_area.queue_render();
    return true; // continue timer
}

void MainWindow::on_gl_realize() {
    m_gl_area.make_current();
}

void MainWindow::on_gl_unrealize() {
    m_gl_area.make_current();
}

void MainWindow::on_gl_resize(int width, int height) {
    m_state_manager->SetStateDimensions(width, height);
}

bool MainWindow::on_render(const Glib::RefPtr<Gdk::GLContext>& context) {
    // The renderer creates GTK/Pango context based on the current context if not using dummy
    Renderer rend(context);
    rend.SetVSyncInterval(1); // Set to 1 if we have vsync variable

    int width = m_gl_area.get_width();
    int height = m_gl_area.get_height();

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    m_state_manager->Draw(rend);

    return true;
}

bool MainWindow::on_key_press_event(GdkEventKey* event) {
    return m_input_manager->OnKeyPress(event);
}

bool MainWindow::on_key_release_event(GdkEventKey* event) {
    return m_input_manager->OnKeyRelease(event);
}

bool MainWindow::on_motion_notify_event(GdkEventMotion* event) {
    return m_input_manager->OnMotionNotify(event);
}

bool MainWindow::on_button_press_event(GdkEventButton* event) {
    return m_input_manager->OnButtonPress(event);
}

bool MainWindow::on_button_release_event(GdkEventButton* event) {
    return m_input_manager->OnButtonRelease(event);
}
