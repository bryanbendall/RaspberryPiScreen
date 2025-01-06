#pragma once

#include "gui/components/SmallGauge.h"
#include "gui/panels/Panel.h"

class LeftMainPanel : public Panel {

public:
    LeftMainPanel();
    virtual ~LeftMainPanel();

    void draw() override;

private:
    void updateValues();

private:
    SmallGauge m_waterGauge;
    SmallGauge m_oilGauge;
};