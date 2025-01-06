#include "FuelLevelPanel.h"

#include "data/GlobalOutputs.h"
#include <raylib.h>

FuelLevelPanel::FuelLevelPanel()
    : m_gasLevel({ 100.0f, 450.0f }, { 240.0f, 10.0f })
    , m_methLevel({ 1000.0f, 450.0f }, { 240.0f, 10.0f })
{
}

FuelLevelPanel::~FuelLevelPanel()
{
}

void FuelLevelPanel::draw()
{
    updateValues();

    m_gasLevel.draw();
    m_methLevel.draw();
}

void FuelLevelPanel::updateValues()
{
    m_gasLevel.setValue(GlobalOutputs::gasLevel);
    m_methLevel.setValue(GlobalOutputs::methLevel);
}