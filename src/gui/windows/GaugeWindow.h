#pragma once

#include <memory>
#include <vector>

class GaugeWindow {

public:
    GaugeWindow();
    ~GaugeWindow();
    void draw();

private:
    void drawRightPanel();

private:
    int m_windowID = -1;
};