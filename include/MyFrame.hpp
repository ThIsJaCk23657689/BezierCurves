#ifndef MYFRAME_HPP
#define MYFRAME_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize);

    void OnAbout(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
#if wxUSE_LOGWINDOW
    void OnLogWindow(wxCommandEvent& event);
#endif

private:
#if wxUSE_LOGWINDOW
    wxLogWindow* m_LogWin;
#endif

    wxDECLARE_EVENT_TABLE();
};
#endif