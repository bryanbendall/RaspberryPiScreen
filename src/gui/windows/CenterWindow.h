#pragma once

#include "raylib.h"

class CenterWindow {

public:
    CenterWindow();
    ~CenterWindow();
    void draw();

private:
    Vector2 getTouchPositionScaled();

private:
    int m_windowID = -1;
    int m_width = 800;
    int m_height = 1280;
};