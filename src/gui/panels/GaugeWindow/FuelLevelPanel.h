#pragma once

#include "gui/components/BarGauge.h"
#include "gui/panels/Panel.h"

class FuelLevelPanel : public Panel {

public:
    FuelLevelPanel();
    virtual ~FuelLevelPanel();

    void draw(int width, int height) override;

private:
    void updateValues();

private:
    BarGauge m_gasLevel;
    BarGauge m_methLevel;
};