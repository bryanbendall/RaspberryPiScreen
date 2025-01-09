#include "RightMainPanel.h"

#include "data/GlobalOutputs.h"
#include <raylib.h>

RightMainPanel::RightMainPanel()
    : m_batteryGauge({ 80.0f, 140.0f }, 140.0f, "V", "battery.svg")
    , m_transGauge({ 240.0f, 140.0f }, 140.0f, "°F", "transmission-temp.svg")
    , m_gasGauge({ 80.0f, 320.0f }, 140.0f, "Gas", "fuel.svg")
    , m_methGauge({ 240.0f, 320.0f }, 140.0f, "Meth", "fuel.svg")
{
    m_batteryGauge.setDecimals(1);
    m_batteryGauge.setMin(6.0f);
    m_batteryGauge.setMax(18.0f);

    m_transGauge.setMin(50.0f);
    m_transGauge.setMax(280.0f);
}

RightMainPanel::~RightMainPanel()
{
}

void RightMainPanel::draw()
{
    updateValues();

    m_batteryGauge.draw();
    m_transGauge.draw();
    m_gasGauge.draw();
    m_methGauge.draw();
}

void RightMainPanel::updateValues()
{
    m_batteryGauge.setValue(GlobalOutputs::battery);
    m_transGauge.setValue(GlobalOutputs::lineTemp);
    m_gasGauge.setValue(GlobalOutputs::fuelPressure);
    m_methGauge.setValue(GlobalOutputs::methPressure);
}