#include "App.hpp"

wxIMPLEMENT_APP(App);

App::App() : m_frame(nullptr) {

}

bool App::OnInit() {
    if (!wxApp::OnInit())
        return false;

    // Create the main application window
    m_frame = new MyFrame(_("Bezier Curves"), wxDefaultPosition, wxSize(800, 600));
    m_frame->Show(true);
    m_frame->OpenGLInit();

    return true;
}
