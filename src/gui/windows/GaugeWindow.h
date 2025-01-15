#pragma once

#include "gui/panels/Panel.h"
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
    std::vector<std::unique_ptr<Panel>> m_rightPanels;
};