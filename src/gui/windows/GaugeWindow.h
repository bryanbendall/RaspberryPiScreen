#pragma once

#include "gui/components/RemoteCamera.h"

class GaugeWindow {

public:
    GaugeWindow();
    ~GaugeWindow();
    void draw();

private:
    void updateValues();

private:
    int m_windowID;
    RemoteCamera m_camera;
};