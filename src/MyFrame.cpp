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
    wxFrame(nullptr, Bezier_MainWindow, title, pos, size) {
    // Set the frame icon
    // SetIcon(wxICON(sample))

#if wxUSE_MENUS
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
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // Create a satus bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_("Bezier Curves"));
#endif // wxUSE_STATUSBAR

#if wxUSE_LOGWINDOW
    // Open a log window, don't show it though
    m_LogWin = new wxLogWindow(nullptr, _("Bezier Curves log window"), false, false);
    wxLog::SetActiveTarget(m_LogWin);
#endif // wxUSE_LOGWINDOW

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