#ifndef MYFRAME_HPP
#define MYFRAME_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "MyGLCanvas.hpp"
#include "MyTimer.hpp"

class MyGLCanvas;
class MyTimer;

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize);

    void OpenGLInit();
    void OnAbout(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
#if wxUSE_LOGWINDOW
    void OnLogWindow(wxCommandEvent& event);
#endif

private:
    void MenuInit();
    void StatusBarInit();

    MyGLCanvas* m_canvas;
    MyTimer* m_timer;
#if wxUSE_LOGWINDOW
    wxLogWindow* m_LogWin;
#endif

    wxDECLARE_EVENT_TABLE();
};
#endif