#include "IndicatorsPanel.h"

#include "data/GlobalOutputs.h"
#include <raylib.h>

IndicatorsPanel::IndicatorsPanel()
    : m_parkingLight({ 30.0f, 30.0f }, 50, "low-beam.svg", GetColor(GlobalOutputs::orange))
    , m_lowBeam({ 30.0f, 30.0f }, 50, "low-beam.svg", GetColor(GlobalOutputs::green))
    , m_highBeam({ 30.0f, 30.0f }, 50, "high-beam.svg", GetColor(GlobalOutputs::blue))
    , m_fogLight({ 32.0f, 90.0f }, 45, "fog-lights.svg", GetColor(GlobalOutputs::green))
    , m_parkingBrake({ 30.0f, 150.0f }, 50, "parking-brake.svg", GetColor(GlobalOutputs::red))
    , m_fan({ 30.0f, 210.0f }, 50, "fan.svg", GetColor(GlobalOutputs::blue))
    , m_engineLight({ 30.0f, 270.0f }, 50, "engine-light.svg", GetColor(GlobalOutputs::orange))
{
}

IndicatorsPanel::~IndicatorsPanel()
{
}

void IndicatorsPanel::draw()
{
    updateValues();

    m_parkingLight.draw();
    m_lowBeam.draw();
    m_highBeam.draw();
    m_fogLight.draw();
    m_parkingBrake.draw();
    m_fan.draw();
    m_engineLight.draw();
}

void IndicatorsPanel::updateValues()
{
    m_parkingLight.setValue(GlobalOutputs::parkingLights);
    m_lowBeam.setValue(GlobalOutputs::lowBeam);
    m_highBeam.setValue(GlobalOutputs::highBeam);
    m_fogLight.setValue(GlobalOutputs::fogLights);
    m_parkingBrake.setValue(GlobalOutputs::parkingBrake);
    m_fan.setValue(GlobalOutputs::fanState);
    m_engineLight.setValue(GlobalOutputs::engineLight);
}