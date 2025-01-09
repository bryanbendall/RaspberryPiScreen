#pragma once

#include "gui/components/RemoteCamera.h"
#include "raylib.h"

class CenterWindow {

public:
    CenterWindow();
    ~CenterWindow();
    void draw();

private:
    Vector2 getTouchPositionScaled();
    bool isTouchDown();
    void pollTouchEvents();

private:
    int m_windowID = -1;
    int m_width = 800;
    int m_height = 1280;
};