#include "Speedometer.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include <fmt/format.h>

Speedometer::Speedometer(Vector2 center)
    : m_center(center)
{
}

Speedometer::~Speedometer()
{
}

void Speedometer::draw()
{
    Font* largeFont = AssetManager::get().getFont("RussoOne-Regular.ttf", m_largeFontSize);
    Font* smallFont = AssetManager::get().getFont("RussoOne-Regular.ttf", m_smallFontSize);

    if (!largeFont || !smallFont)
        return;

    // Value
    std::string lable = fmt::format("{:.0f}", m_value);
    Vector2 valueMeasure = MeasureTextEx(*largeFont, lable.c_str(), m_largeFontSize, 0);
    DrawTextEx(*largeFont, lable.c_str(), { m_center.x - (valueMeasure.x / 2.0f), m_center.y - (valueMeasure.y / 2.0f) }, m_largeFontSize, 0, GetColor(GlobalOutputs::white));

    // Unit
    std::string unit = m_useKph ? "KPH" : "MPH";
    Vector2 unitMeasure = MeasureTextEx(*smallFont, unit.c_str(), m_smallFontSize, 0);
    DrawTextEx(*smallFont, unit.c_str(), { m_center.x - (unitMeasure.x / 2.0f), m_center.y + (valueMeasure.y / 2.0f) - 10.0f }, m_smallFontSize, 0, GetColor(GlobalOutputs::gray));
}