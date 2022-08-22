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

    // Used just to know if we must end now because OGL 3.3 isn't available
    bool OglCtxAvailable() {
        return m_oglContext != nullptr;
    }

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