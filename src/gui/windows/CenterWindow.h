#pragma once

#include "gui/components/RemoteCamera.h"
#include "gui/input/TouchInput.h"
#include "raylib.h"

class CenterWindow {

public:
    CenterWindow();
    ~CenterWindow();
    void draw();

private:
    enum Screens {
        Info,
        Map,
        Hvac,
        Settings
    };

private:
    int m_windowID = -1;
    int m_width = 800;
    int m_height = 1280;
    TouchInput m_touchInput;
    Screens m_currentScreen = Screens::Hvac;
};