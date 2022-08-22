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
    auto* frame = new MyFrame(_("Bezier Curves"));

    // Exit if the required visual attributes or OGL context couldn't be created
//    if (!frame->OGLAvailable())
//        return false;

    wxGLAttributes vAttrs;
    vAttrs.PlatformDefaults().Defaults().EndList();
    auto* canvas = new MyGLCanvas(frame, vAttrs);

    frame->Show(true);
    canvas->oglInit();

    return true;
}
