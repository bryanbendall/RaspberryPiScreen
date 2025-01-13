#pragma once

#include "gui/components/AfrGauge.h"
#include "gui/components/BoostGauge.h"
#include "gui/components/ClosedLoopGauge.h"
#include "gui/components/GearIndicator.h"
#include "gui/components/Indicator.h"
#include "gui/components/Speedometer.h"
#include "gui/components/TachGauge.h"
#include "gui/panels/Panel.h"

class CenterMainPanel : public Panel {

public:
    CenterMainPanel();
    virtual ~CenterMainPanel();

    void draw(int width, int height) override;

private:
    void updateValues();

private:
    BoostGauge m_boost;
    ClosedLoopGauge m_closedLoop;
    TachGauge m_tach;
    Speedometer m_speedometer;
    AfrGauge m_afrGauge;
    Indicator m_leftTurn;
    Indicator m_rightTurn;
    GearIndicator m_gearIndicator;
};