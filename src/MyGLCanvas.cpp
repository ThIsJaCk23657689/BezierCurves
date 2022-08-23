#include <glad/glad.h>
#include "MyGLCanvas.hpp"

wxBEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
    EVT_PAINT(MyGLCanvas::OnPaint)
    EVT_SIZE(MyGLCanvas::OnSize)
    EVT_MOUSE_EVENTS(MyGLCanvas::OnMouse)
wxEND_EVENT_TABLE()

static float red = 1.0f;

MyGLCanvas::MyGLCanvas(MyFrame *parent, const wxGLAttributes &canvasAttrs) :
    wxGLCanvas(parent, canvasAttrs) {
    m_parent = parent;
    m_winHeight = 0;

    // Explicitly create a new rendering context instance for this canvas.
    wxGLContextAttrs ctxAttrs;
    ctxAttrs.CoreProfile().OGLVersion(3, 3).Robust().ResetIsolation().EndList();
    m_oglContext = new wxGLContext(this, nullptr, &ctxAttrs);

    if (!m_oglContext->IsOK()) {
        wxMessageBox("This sample needs an OpenGL 3.3 capable driver.\nThe app will end now.",
            "OpenGL version error", wxOK | wxICON_INFORMATION, this);
        delete m_oglContext;
        m_oglContext = nullptr;
    } else {
#if wxUSE_LOGWINDOW
        wxLogMessage("OpenGL Core Profile 3.2 successfully set.");
#endif // wxUSE_LOGWINDOW
    }

    Bind(wxEVT_MOUSEWHEEL, [&red, this](wxMouseEvent& event){
        float diff = static_cast<float>(event.GetWheelRotation()) / 1200.0f;
        red += diff;
        Refresh();
    });
}

MyGLCanvas::~MyGLCanvas() {
    if (m_oglContext)
        SetCurrent(*m_oglContext);

    if (m_oglContext) {
        delete m_oglContext;
        m_oglContext = nullptr;
    }
}

bool MyGLCanvas::oglInit() {
    if (!m_oglContext)
        return false;

    // The current context must be set before we get OGL pointers
    SetCurrent(*m_oglContext);

    // Initialize our OGL pointers
    gladLoadGL();
}

void MyGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    wxPaintDC dc(this);

    if (m_winHeight < 1 )
        return;

    SetCurrent(*m_oglContext);
    glClearColor(red, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SwapBuffers();
}

void MyGLCanvas::OnSize(wxSizeEvent& event) {
    event.Skip();

    // If this window is not fully initialized, dismiss this event
    if (!IsShownOnScreen())
        return;

    SetCurrent(*m_oglContext);

    const wxSize size = event.GetSize() * GetContentScaleFactor();
    m_winHeight = size.y;

    // Generate paint event without erasing the background
    Refresh(false);
}

void MyGLCanvas::OnMouse(wxMouseEvent &event) {
    event.Skip();

    int oglwinY = m_winHeight - event.GetY();

    if (event.LeftIsDown()) {
        if (!event.Dragging()) {
            // Store positions

        } else {
            // Rotation

            // Generate paint event without erasing the background
            Refresh(false);
        }
    }
}