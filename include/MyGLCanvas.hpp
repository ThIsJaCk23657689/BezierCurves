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

class MyFrame;

class MyGLCanvas : public wxGLCanvas {
public:
    MyGLCanvas(MyFrame* parent, const wxGLAttributes& canvasAttrs);
    ~MyGLCanvas();

    // Init the OpenGL
    bool Init();

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnMouse(wxMouseEvent& event);
    void OnUpdate(wxTimerEvent& event);

private:
    MyFrame* m_parent;
    wxGLContext* m_context;
    int m_window_height;

    wxDECLARE_EVENT_TABLE();
};

#endif