#include "Speedometer.h"

#include "data/GlobalVariables.h"
#include <fmt/format.h>

static constexpr int largeFontSize = 100;
static constexpr int smallFontSize = 26;
static Font largeFont;
static Font smallFont;

Speedometer::Speedometer(Vector2 center)
    : m_center(center)
{
}

Speedometer::~Speedometer()
{
    UnloadFont(largeFont);
    UnloadFont(smallFont);
}

void Speedometer::initResources()
{
    largeFont = LoadFontEx("../resources/fonts/RussoOne-Regular.ttf", largeFontSize, 0, 250);
    smallFont = LoadFontEx("../resources/fonts/RussoOne-Regular.ttf", smallFontSize, 0, 250);
}

void Speedometer::draw()
{
    // Value
    std::string lable = fmt::format("{:.0f}", m_value);
    Vector2 valueMeasure = MeasureTextEx(largeFont, lable.c_str(), largeFontSize, 0);
    DrawTextEx(largeFont, lable.c_str(), { m_center.x - (valueMeasure.x / 2.0f), m_center.y - (valueMeasure.y / 2.0f) }, largeFontSize, 0, GetColor(GlobalVariables::white));

    // Unit
    std::string unit = m_useKph ? "KPH" : "MPH";
    Vector2 unitMeasure = MeasureTextEx(smallFont, unit.c_str(), smallFontSize, 0);
    DrawTextEx(smallFont, unit.c_str(), { m_center.x - (unitMeasure.x / 2.0f), m_center.y + (valueMeasure.y / 2.0f) - 10.0f }, smallFontSize, 0, GetColor(GlobalVariables::gray));
}