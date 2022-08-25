#include "MyFrame.hpp"
#include "ID.hpp"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Bezier_Quit, MyFrame::OnQuit)
    EVT_MENU(Bezier_About, MyFrame::OnAbout)
#if wxUSE_LOGWINDOW
    EVT_MENU(Bezier_LogW, MyFrame::OnLogWindow)
#endif // wxUSE_LOGWINDOW
wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) :
    wxFrame(nullptr, Bezier_MainWindow, title, pos, size),
    m_canvas(nullptr),
    m_timer(nullptr) {
    // Set the frame icon
    // SetIcon(wxICON(sample))

    MenuInit();
    StatusBarInit();

    // Log window
#if wxUSE_LOGWINDOW
    // Open a log window, don't show it though
    m_LogWin = new wxLogWindow(nullptr, _("Bezier Curves log window"), false, false);
    wxLog::SetActiveTarget(m_LogWin);
#endif // wxUSE_LOGWINDOW


    // Setting OpenGL Display mode (RGBA, Depth 16 bits, Double Buffer, 1 Sample Buffer, 4 Sampler)
    wxGLAttributes vAttrs;
    vAttrs.PlatformDefaults().Defaults().EndList();
    bool accepted = wxGLCanvas::IsDisplaySupported(vAttrs);
    if (!accepted) {
        wxMessageBox("Visual attributes for OpenGL are not accepted.\nThe app will exit now.",
                     "Error with OpenGL", wxOK | wxICON_ERROR);
        Close();
    }

    // Sizer
    auto* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    auto* controlSizer = new wxBoxSizer(wxVERTICAL);
    auto* rightPanel = new wxPanel(this, wxID_ANY);

    // Create OpenGL Canvas
    m_canvas = new MyGLCanvas(this, vAttrs);

    // Create Timer
    m_timer = new MyTimer(m_canvas);

    controlSizer->Add(rightPanel, wxSizerFlags().Proportion(1).Expand());
    mainSizer->Add(m_canvas, wxSizerFlags().Proportion(8).Expand());
    mainSizer->Add(controlSizer, wxSizerFlags().Proportion(2).Expand());
    SetSizer(mainSizer);
    SetMinSize(wxSize(1000, 600));
    mainSizer->Fit(this);
}

void MyFrame::OpenGLInit() {
    m_canvas->Init();
    m_timer->Start(60);
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event)) {
    // true is to force the frame to close
    m_timer->Stop();
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event)) {
    wxMessageBox(wxString::Format(
        "Welcome to %s!\n"
        "\n"
        "This is the wxWidgets OpenGL Bezier Curves sample.\n"
        "%s\n",
        wxVERSION_STRING
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

void MyFrame::MenuInit() {
    // Create a menu bar
    auto *fileMenu = new wxMenu;
#if wxUSE_LOGWINDOW
    fileMenu->Append(Bezier_LogW, "&Log window", "Open the log window");
    fileMenu->AppendSeparator();
#endif // wxUSE_LOGWINDOW
    fileMenu->Append(Bezier_Quit, "E&xit\tAlt-X", "Quit this program");

    // The "About" item should be in help menu
    auto *helpMenu = new wxMenu;
    helpMenu->Append(Bezier_About, "&About\tF1", "Show about dialog");

    // now append the freshly crated menu to the menu bar...
    auto* menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");
    // and attach this menu bar to the frame
    SetMenuBar(menuBar);
}

void MyFrame::StatusBarInit() {
    // Create a satus bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_("Bezier Curves"));
}