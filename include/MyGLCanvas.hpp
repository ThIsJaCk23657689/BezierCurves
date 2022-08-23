#ifndef MYGLCANVAS_HPP
#define MYGLCANVAS_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#if !wxUSE_GLCANVAS
    #error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include <wx/glcanvas.h>
#include "MyFrame.hpp"

class MyGLCanvas : public wxGLCanvas {
public:
    MyGLCanvas(MyFrame* parent, const wxGLAttributes& canvasAttrs);
    ~MyGLCanvas();

    // Init the OpenGL stuff
    bool oglInit();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnMouse(wxMouseEvent& event);

private:
    MyFrame* m_parent;
    wxGLContext* m_oglContext;
    int m_winHeight;

    wxDECLARE_EVENT_TABLE();
};

#endif