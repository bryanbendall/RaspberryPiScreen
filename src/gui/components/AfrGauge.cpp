#include "AfrGauge.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include <fmt/format.h>

AfrGauge::AfrGauge(Vector2 center)
    : m_center(center)
{
}

AfrGauge::~AfrGauge()
{
}

void AfrGauge::draw()
{
    Font largeFont = AssetManager::get().getFont("RussoOne-Regular.ttf", m_largeFontSize);
    Font smallFont = AssetManager::get().getFont("RussoOne-Regular.ttf", m_smallFontSize);

    std::string lable = "AFR";
    Vector2 afrSize = MeasureTextEx(smallFont, lable.c_str(), m_smallFontSize, 0.0f);
    DrawTextEx(smallFont, lable.c_str(), { m_center.x - (afrSize.x / 2.0f), m_center.y }, m_smallFontSize, 0, GetColor(GlobalOutputs::gray));

    if (!m_showBoth) {
        std::string lable = fmt::format("{:.1f}", m_values[0]);
        Vector2 textSize = MeasureTextEx(largeFont, lable.c_str(), m_largeFontSize, 0.0f);
        DrawTextEx(largeFont, lable.c_str(), { m_center.x - (textSize.x / 2.0f), m_center.y + m_smallFontSize }, m_largeFontSize, 0, GetColor(GlobalOutputs::white));
    } else {
        std::string leftLable = fmt::format("{:.1f}", m_values[0]);
        Vector2 leftSize = MeasureTextEx(largeFont, leftLable.c_str(), m_largeFontSize, 0.0f);
        DrawTextEx(largeFont, leftLable.c_str(), { m_center.x - leftSize.x - 10.0f, m_center.y + m_smallFontSize }, m_largeFontSize, 0, GetColor(GlobalOutputs::white));

        std::string rightLable = fmt::format("{:.1f}", m_values[1]);
        DrawTextEx(largeFont, rightLable.c_str(), { m_center.x + 10.0f, m_center.y + m_smallFontSize }, m_largeFontSize, 0, GetColor(GlobalOutputs::white));
    }
}