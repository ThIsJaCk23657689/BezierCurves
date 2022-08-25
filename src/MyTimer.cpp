#include "MyTimer.hpp"

MyTimer::MyTimer(MyGLCanvas* canvas) : m_canvas(canvas) {

}

void MyTimer::Notify() {
    m_canvas->Refresh();
}