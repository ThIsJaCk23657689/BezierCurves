#ifndef APP_HPP
#define APP_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "MyFrame.hpp"

class App : public wxApp {
public:
    App();
    bool OnInit() wxOVERRIDE;

private:
    MyFrame* m_frame;

};

DECLARE_APP(App);
#endif