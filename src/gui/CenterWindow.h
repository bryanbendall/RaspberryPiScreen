#pragma once

#include "raylib.h"

class CenterWindow {

public:
    CenterWindow();
    ~CenterWindow();
    void draw();

private:
    void drawRotatedTextureToScreen();

private:
    int m_windowID;
    int m_width = 800;
    int m_height = 1280;
    float m_rotation = 90.0f;
    RenderTexture2D m_renderTexture;
};