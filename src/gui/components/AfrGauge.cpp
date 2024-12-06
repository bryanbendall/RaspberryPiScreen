#include "AfrGauge.h"

#include "data/GlobalOutputs.h"
#include <fmt/format.h>

AfrGauge::AfrGauge(Vector2 center)
    : m_center(center)
{
}

AfrGauge::~AfrGauge()
{
    UnloadFont(m_smallFont);
    UnloadFont(m_largeFont);
}

void AfrGauge::initResources()
{
    m_smallFont = LoadFontEx("../resources/fonts/RussoOne-Regular.ttf", m_smallFontSize, 0, 250);
    m_largeFont = LoadFontEx("../resources/fonts/RussoOne-Regular.ttf", m_largeFontSize, 0, 250);
}

void AfrGauge::draw()
{
    std::string lable = "AFR";
    Vector2 afrSize = MeasureTextEx(m_smallFont, lable.c_str(), m_smallFontSize, 0.0f);
    DrawTextEx(m_smallFont, lable.c_str(), { m_center.x - (afrSize.x / 2.0f), m_center.y }, m_smallFontSize, 0, GetColor(GlobalOutputs::gray));

    if (!m_showBoth) {
        std::string lable = fmt::format("{:.1f}", m_values[0]);
        Vector2 textSize = MeasureTextEx(m_largeFont, lable.c_str(), m_largeFontSize, 0.0f);
        DrawTextEx(m_largeFont, lable.c_str(), { m_center.x - (textSize.x / 2.0f), m_center.y + m_smallFontSize }, m_largeFontSize, 0, GetColor(GlobalOutputs::white));
    } else {
        std::string leftLable = fmt::format("{:.1f}", m_values[0]);
        Vector2 leftSize = MeasureTextEx(m_largeFont, leftLable.c_str(), m_largeFontSize, 0.0f);
        DrawTextEx(m_largeFont, leftLable.c_str(), { m_center.x - leftSize.x - 10.0f, m_center.y + m_smallFontSize }, m_largeFontSize, 0, GetColor(GlobalOutputs::white));

        std::string rightLable = fmt::format("{:.1f}", m_values[1]);
        DrawTextEx(m_largeFont, rightLable.c_str(), { m_center.x + 10.0f, m_center.y + m_smallFontSize }, m_largeFontSize, 0, GetColor(GlobalOutputs::white));
    }
}