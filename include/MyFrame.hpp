#ifndef MYFRAME_HPP
#define MYFRAME_HPP

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "MyGLCanvas.hpp"

class MyGLCanvas;

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

    void OnAbout(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);

#if wxUSE_LOGWINDOW
    void OnLogWindow(wxCommandEvent& event);
#endif

    void SetOGLString(const wxString& ogls) {
        m_OGLString = ogls;
    }

    bool OGLAvailable();

private:
#if wxUSE_LOGWINDOW
    wxLogWindow* m_LogWin;
#endif
    wxString m_OGLString;
    MyGLCanvas* m_mycanvas;

    wxDECLARE_EVENT_TABLE();
};
#endif