#include "SmallGauge.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/Utils.h"
#include <fmt/format.h>
#include <iostream>
#include <string>

SmallGauge::SmallGauge(Vector2 center, float size, std::string label, std::filesystem::path iconFilename)
    : m_center(center)
    , m_size(size)
    , m_label(label)
    , m_iconFilename(iconFilename)
{
    m_innerCircleSize = m_size * 0.8f;
    m_centerLableSize = m_size * 0.27f;
    m_unitLableSize = m_size * 0.16f;
    m_minMaxLableSize = m_size * 0.11f;
    m_iconSize = m_size * 0.2f;
}

SmallGauge::~SmallGauge()
{
}

void SmallGauge::draw()
{
    Font* largeFont = AssetManager::get().getFont("RussoOne-Regular.ttf", m_centerLableSize);
    Font* smallFont = AssetManager::get().getFont("RussoOne-Regular.ttf", m_unitLableSize);
    Font* minMaxFont = AssetManager::get().getFont("RussoOne-Regular.ttf", m_unitLableSize);

    if (!largeFont || !smallFont || !minMaxFont)
        return;

    Texture2D* outerCircleTexture = AssetManager::get().getSvg("outerCircle.svg", m_size, m_size);
    Texture2D* innerCircleTexture = AssetManager::get().getSvg("circle.svg", m_innerCircleSize, m_innerCircleSize);
    Texture2D* iconTexture = AssetManager::get().getSvg(m_iconFilename, m_iconSize, m_iconSize);

    if (!outerCircleTexture || !innerCircleTexture || !iconTexture)
        return;

    // Ring
    {
        float angle = calculateValueAngle();

        DrawCircleSector(m_center, m_size / 2.0f, 90.0f, 360.0f, 20, GetColor(GlobalOutputs::gray));
        DrawCircleSector(m_center, m_size / 2.0f, 90.0f, angle, 20, Utils::getColorFromBrytec(GlobalOutputs::guageColor));

        DrawTexture(*outerCircleTexture, m_center.x - (m_size / 2.0f), m_center.y - (m_size / 2.0f), GetColor(GlobalOutputs::black));
        DrawTexture(*innerCircleTexture, m_center.x - (m_innerCircleSize / 2.0f), m_center.y - (m_innerCircleSize / 2.0f), GetColor(GlobalOutputs::black));
    }

    // Center value text
    {
        std::string lable = fmt::format("{:.{}f}", m_value, m_decimals);
        Vector2 textSize = MeasureTextEx(*largeFont, lable.c_str(), m_centerLableSize, 0);
        DrawTextEx(*largeFont, lable.c_str(), { m_center.x - (textSize.x / 2.0f), m_center.y - (m_centerLableSize / 2.0f) }, m_centerLableSize, 0, GetColor(GlobalOutputs::white));
    }

    // Gauge min and max text
    {
        std::string lable = fmt::format("{:.0f}", m_minValue);
        DrawTextEx(*minMaxFont, lable.c_str(), { m_center.x + 8.0f, m_center.y + (m_size / 2.0f) - m_minMaxLableSize }, m_minMaxLableSize, 0, GetColor(GlobalOutputs::white));

        lable = fmt::format("{:.0f}", m_maxValue);
        DrawTextEx(*minMaxFont, lable.c_str(), { m_center.x + (m_innerCircleSize / 2.0f), m_center.y + (m_minMaxLableSize / 4.0f) }, m_minMaxLableSize, 0, GetColor(GlobalOutputs::white));
    }

    // Gauge label
    {
        Vector2 textSize = MeasureTextEx(*smallFont, m_label.c_str(), m_unitLableSize, 0);
        DrawTextEx(*smallFont, m_label.c_str(), { m_center.x - (textSize.x / 2.0f), m_center.y - (m_size * 0.3f) }, m_unitLableSize, 0, GetColor(GlobalOutputs::gray));
    }

    // Icon
    {
        DrawTexture(*iconTexture, m_center.x - (m_iconSize / 2.0f), m_center.y + (m_size * 0.14f), GetColor(GlobalOutputs::gray));
    }
}

float SmallGauge::calculateValueAngle()
{
    return Utils::mapValue(m_minValue, m_maxValue, 90.0f, 360.0f, m_value);
}
