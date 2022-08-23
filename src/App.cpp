#include "App.hpp"
#include "MyFrame.hpp"
#include "MyGLCanvas.hpp"

wxIMPLEMENT_APP(App);

App::App() {

}

bool App::OnInit() {
    if (!wxApp::OnInit())
        return false;

    // Create the main application window
    auto* frame = new MyFrame(_("Bezier Curves"), wxDefaultPosition, wxSize(800, 600));

    // Setting OpenGL Display mode (RGBA, Depth 16 bits, Double Buffer, 1 Sample Buffer, 4 Sampler)
    wxGLAttributes vAttrs;
    vAttrs.PlatformDefaults().Defaults().EndList();
    bool accepted = wxGLCanvas::IsDisplaySupported(vAttrs);
    if (!accepted) {
        wxMessageBox("Visual attributes for OpenGL are not accepted.\nThe app will exit now.",
            "Error with OpenGL", wxOK | wxICON_ERROR);
    }

    auto* canvas = new MyGLCanvas(frame, vAttrs);
    frame->Show(true);
    canvas->oglInit();

    return true;
}
