#pragma once

#include "gui/components/RemoteCamera.h"
#include "gui/panels/GaugeWindow/CenterMainPanel.h"
#include "gui/panels/GaugeWindow/FuelLevelPanel.h"
#include "gui/panels/GaugeWindow/IndicatorsPanel.h"
#include "gui/panels/GaugeWindow/LeftMainPanel.h"
#include "gui/panels/Panel.h"
#include <memory>

class GaugeWindow {

public:
    GaugeWindow();
    ~GaugeWindow();
    void draw();

private:
    int m_windowID = -1;
    RemoteCamera m_camera;
    std::vector<std::unique_ptr<Panel>> m_rightPanels;
    IndicatorsPanel m_indicatorsPanel;
    LeftMainPanel m_leftMainPanel;
    CenterMainPanel m_centerMainPanel;
    FuelLevelPanel m_fuelLevelPanel;
};