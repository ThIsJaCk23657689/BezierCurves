#include <glad/glad.h>
#include <string>
#include "MyGLCanvas.hpp"

wxBEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
    EVT_PAINT(MyGLCanvas::OnPaint)
    EVT_SIZE(MyGLCanvas::OnSize)
    EVT_MOUSE_EVENTS(MyGLCanvas::OnMouse)
wxEND_EVENT_TABLE()

MyGLCanvas::MyGLCanvas(MyFrame *parent, const wxGLAttributes &canvasAttrs) :
    wxGLCanvas(parent, canvasAttrs) {
    m_parent = parent;
    m_window_height = 0;

    // Explicitly create a new rendering context instance for this canvas.
    wxGLContextAttrs ctxAttrs;
    ctxAttrs.CoreProfile().OGLVersion(3, 3).Robust().ResetIsolation().EndList();
    m_context = new wxGLContext(this, nullptr, &ctxAttrs);

    if (!m_context->IsOK()) {
        wxMessageBox("This sample needs an OpenGL 3.3 capable driver.\nThe app will end now.",
            "OpenGL version error", wxOK | wxICON_INFORMATION, this);
        delete m_context;
        m_context = nullptr;
    } else {
#if wxUSE_LOGWINDOW
        wxLogMessage("[INFO] OpenGL Core Profile 3.3 successfully set.");
#endif // wxUSE_LOGWINDOW
    }

    Bind(wxEVT_MOUSEWHEEL, [this](wxMouseEvent& event) {
        float diff = static_cast<float>(event.GetWheelRotation()) / 1200.0f;
    });
}

MyGLCanvas::~MyGLCanvas() {
    if (m_context)
        SetCurrent(*m_context);

    if (m_context) {
        delete m_context;
        m_context = nullptr;
    }
}

bool MyGLCanvas::Init() {
    if (!m_context)
        return false;

    // The current context must be set before we get OGL pointers
    SetCurrent(*m_context);

    // Initialize our OGL pointers
    gladLoadGL();

    // Show Infomation
#if wxUSE_LOGWINDOW
    wxString opengl = "[INFO] OpenGL Version:\t" + wxString(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    wxString glsl = "[INFO] GLSL Version:\t" + wxString(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
    wxString gpu_renderer = "[INFO] GPU Renderer:\t" + wxString(reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    wxString gpu_vendor = "[INFO] GPU Vendor:\t\t" + wxString(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    wxLogMessage(opengl);
    wxLogMessage(glsl);
    wxLogMessage(gpu_renderer);
    wxLogMessage(gpu_vendor);
#endif // wxUSE_LOGWINDOW
}

void MyGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    wxPaintDC dc(this);

    if (m_window_height < 1 )
        return;

    SetCurrent(*m_context);
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SwapBuffers();
}

void MyGLCanvas::OnSize(wxSizeEvent& event) {
    event.Skip();

    // If this window is not fully initialized, dismiss this event
    if (!IsShownOnScreen())
        return;

    SetCurrent(*m_context);

    const wxSize size = event.GetSize() * GetContentScaleFactor();
    m_window_height = size.y;

    // Generate paint event without erasing the background
    Refresh(false);
}

void MyGLCanvas::OnMouse(wxMouseEvent &event) {
    event.Skip();

    int oglwinY = m_window_height - event.GetY();

    if (event.LeftIsDown()) {
        if (!event.Dragging()) {
            // Store positions

        } else {
            // Rotation

        }
    }
}

void MyGLCanvas::OnUpdate(wxTimerEvent& event) {
    Refresh();
}