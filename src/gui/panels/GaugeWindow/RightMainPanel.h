#pragma once

#include "gui/components/SmallGauge.h"
#include "gui/panels/Panel.h"

class RightMainPanel : public Panel {

public:
    RightMainPanel();
    virtual ~RightMainPanel();

    void draw(int width, int height) override;

private:
    void updateValues();

private:
    SmallGauge m_batteryGauge;
    SmallGauge m_transGauge;
    SmallGauge m_gasGauge;
    SmallGauge m_methGauge;
};