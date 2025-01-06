#include "LeftMainPanel.h"

#include "data/GlobalOutputs.h"
#include <raylib.h>

LeftMainPanel::LeftMainPanel()
    : m_waterGauge({ 200.0f, 125.0f }, 180.0f, "°F", "water-temp.svg")
    , m_oilGauge({ 200.0f, 325.0f }, 180.0f, "Psi", "engine-oil.svg")
{
    m_waterGauge.setMin(30.0f);
    m_waterGauge.setMax(250.0f);
}

LeftMainPanel::~LeftMainPanel()
{
}

void LeftMainPanel::draw()
{
    updateValues();

    m_waterGauge.draw();
    m_oilGauge.draw();
}

void LeftMainPanel::updateValues()
{
    m_waterGauge.setValue(GlobalOutputs::cts);
    m_oilGauge.setValue(GlobalOutputs::oilPressure);
}