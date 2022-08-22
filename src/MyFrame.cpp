#include "MyFrame.hpp"
#include "ID.hpp"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Bezier_Quit, MyFrame::OnQuit)
    EVT_MENU(Bezier_About, MyFrame::OnAbout)
#if wxUSE_LOGWINDOW
    EVT_MENU(Bezier_LogW, MyFrame::OnLogWindow)
#endif // wxUSE_LOGWINDOW
wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString &title) :
    wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)) {
    // Set the frame icon
    // SetIcon(wxICON(sample))

#if wxUSE_MENUS
    // Create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // The "About" item should be in help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Bezier_About, "&About\tF1", "Show about dialog");

#if wxUSE_LOGWINDOW
    fileMenu->Append(Bezier_LogW, "&Log window", "Open the log window");
    fileMenu->AppendSeparator();
#endif // wxUSE_LOGWINDOW
    fileMenu->Append(Bezier_Quit, "E&xit\tAlt-X", "Quit this program");

    // now append the freshly crated menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // Create a satus bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText("Welcome to wxWidgets");
#endif // wxUSE_STATUSBAR

#if wxUSE_LOGWINDOW
    // Open a log window, don't show it though
    m_LogWin = new wxLogWindow(nullptr, _("Bezier Curves log window"), false, false);
    wxLog::SetActiveTarget(m_LogWin);
#endif // wxUSE_LOGWINDOW

    // The canvas
    m_mycanvas = nullptr;
    wxGLAttributes vAttrs;
    // Default should be accepted
    vAttrs.PlatformDefaults().Defaults().EndList();
    bool accepted = wxGLCanvas::IsDisplaySupported(vAttrs);

    if (accepted) {
#if wxUSE_LOGWINDOW
        wxLogMessage("The display supports required visual attributes.");
#endif // wxUSE_LOGWINDOW
    } else {
#if wxUSE_LOGWINDOW
        wxLogMessage("First try with OpenGL default visual attributes failed.");
#endif // wxUSE_LOGWINDOW
        // Try again without sample buffers
        vAttrs.Reset();
        vAttrs.PlatformDefaults().RGBA().DoubleBuffer().Depth(16).EndList();
        accepted = wxGLCanvas::IsDisplaySupported(vAttrs);

        if (!accepted) {
            wxMessageBox("Visual attributes for OpenGL are not accepted.\nThe app will exit now.",
                "Error with OpenGL", wxOK | wxICON_ERROR);
        } else {
#if wxUSE_LOGWINDOW
            wxLogMessage("Second try with other visual attributes worked.");
#endif // wxUSE_LOGWINDOW
        }
    }

//    if (accepted)
//        m_mycanvas = new MyGLCanvas(this, vAttrs);

    SetMinSize(wxSize(250, 200));
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
    wxMessageBox(wxString::Format(
        "Welcome to %s!\n"
        "\n"
        "This is the wxWidgets OpenGL Bezier Curves sample.\n"
        "%s\n",
        wxVERSION_STRING,
        m_OGLString
    ), "About wxWidgets Bezier Curves sample",
    wxOK | wxICON_INFORMATION, this);
}

#if wxUSE_LOGWINDOW
void MyFrame::OnLogWindow(wxCommandEvent& WXUNUSED(event)) {
    if (m_LogWin->GetFrame()->IsIconized())
        m_LogWin->GetFrame()->Restore();

    if (!m_LogWin->GetFrame()->IsShown())
        m_LogWin->Show();

    m_LogWin->GetFrame()->SetFocus();
}
#endif // wxUSE_LOGWINDOW

bool MyFrame::OGLAvailable() {
    // Test if visual attributes were accepted
    if (!m_mycanvas)
        return false;

    // Test if OGL context could be created
    return m_mycanvas->OglCtxAvailable();
}