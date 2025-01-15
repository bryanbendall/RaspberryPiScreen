#include "RightMainPanel.h"

#include "data/GlobalOutputs.h"
#include "gui/components/UiComponents.h"
#include <raylib.h>

RightMainPanel::RightMainPanel()

{
}

RightMainPanel::~RightMainPanel()
{
}

void RightMainPanel::draw(int width, int height)
{

    Ui::SmallGauge({ 80.0f, 140.0f }, 140.0f, "V", "battery.svg", GlobalOutputs::battery, 6.0f, 18.0f, 1);
    Ui::SmallGauge({ 240.0f, 140.0f }, 140.0f, "°F", "transmission-temp.svg", GlobalOutputs::lineTemp, 50.0f, 280.0f);
    Ui::SmallGauge({ 80.0f, 320.0f }, 140.0f, "Gas", "fuel.svg", GlobalOutputs::fuelPressure);
    Ui::SmallGauge({ 240.0f, 320.0f }, 140.0f, "Meth", "fuel.svg", GlobalOutputs::methPressure);
}
