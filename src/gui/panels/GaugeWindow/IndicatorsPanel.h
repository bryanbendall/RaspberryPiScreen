#pragma once

#include "gui/components/Indicator.h"
#include "gui/panels/Panel.h"

class IndicatorsPanel : public Panel {

public:
    IndicatorsPanel();
    virtual ~IndicatorsPanel();

    void draw(int width, int height) override;

private:
    void updateValues();

private:
    Indicator m_parkingLight;
    Indicator m_lowBeam;
    Indicator m_highBeam;
    Indicator m_fogLight;
    Indicator m_parkingBrake;
    Indicator m_fan;
    Indicator m_engineLight;
};