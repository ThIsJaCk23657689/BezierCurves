#ifndef MYTIMER_HPP
#define MYTIMER_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/timer.h>
#include "MyGLCanvas.hpp"

class MyGLCanvas;

class MyTimer : public wxTimer {
public:
    MyTimer(MyGLCanvas* canvas);
    void Notify();

private:
    MyGLCanvas* m_canvas;

};

#endif