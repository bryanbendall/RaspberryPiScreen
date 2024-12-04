#include "SmallGauge.h"

#include "data/GlobalOutputs.h"
#include "gui/Utils.h"
#include <fmt/format.h>
#include <iostream>
#include <string>

static int refs = 0;

static Font smallFont;
static Font largeFont;

static Texture2D iconTextures[SmallGauge::Icon::Count];
static const char* iconPaths[] = {
    "../resources/images/water-temp.svg",
    "../resources/images/transmission-temp.svg",
    "../resources/images/fuel.svg",
    "../resources/images/engine-oil.svg",
    "../resources/images/battery.svg",
};

static Texture2D outerCircleTexture;
static Texture2D innerCircleTexture;

SmallGauge::SmallGauge(Vector2 center, float size, float minValue, float maxValue, std::string label, Icon icon)
    : m_size(size)
    , m_minValue(minValue)
    , m_maxValue(maxValue)
    , m_label(label)
    , m_icon(icon)
{
    refs++;
    setPosition(center);
}

SmallGauge::~SmallGauge()
{
    refs--;

    if (refs <= 0) {
        UnloadFont(smallFont);
        UnloadFont(largeFont);

        for (int i = 0; i < Icon::Count; i++)
            UnloadTexture(iconTextures[i]);

        UnloadTexture(outerCircleTexture);
        UnloadTexture(innerCircleTexture);
    }
}

void SmallGauge::draw()
{
    // Ring
    {
        float angle = calculateValueAngle();

        DrawCircleSector(m_center, m_size / 2.0f, 90.0f, 360.0f, 20, GetColor(GlobalOutputs::gray));
        DrawCircleSector(m_center, m_size / 2.0f, 90.0f, angle, 20, Utils::getColorFromBrytec(GlobalOutputs::guageColor));

        DrawTexture(outerCircleTexture, m_center.x - (m_size / 2), m_center.y - (m_size / 2), GetColor(GlobalOutputs::black));
        DrawTexture(innerCircleTexture, m_center.x - (m_size / 2) + 15, m_center.y - (m_size / 2) + 15, GetColor(GlobalOutputs::black));
    }

    // Center value text
    {
        int fontSize = 40;
        std::string lable = fmt::format("{:.0f}", m_value);
        float textSize = MeasureText(lable.c_str(), fontSize);
        DrawTextEx(largeFont, lable.c_str(), { m_center.x - (textSize / 2.0f), m_center.y - (fontSize / 2) }, fontSize, 0, GetColor(GlobalOutputs::white));
    }

    // Gauge min and max text
    {
        int fontSize = 16;
        std::string lable = fmt::format("{:.0f}", m_minValue);
        DrawTextEx(smallFont, lable.c_str(), { m_center.x + 8.0f, m_center.y + (m_size / 2) - fontSize }, fontSize, 0, GetColor(GlobalOutputs::white));

        lable = fmt::format("{:.0f}", m_maxValue);
        DrawTextEx(smallFont, lable.c_str(), { m_center.x + (m_size / 2) - 14.0f, m_center.y + 6.0f }, fontSize, 0, GetColor(GlobalOutputs::white));
    }

    // Gauge label
    {
        int fontSize = 24;
        float textSize = MeasureText(m_label.c_str(), fontSize);
        DrawTextEx(smallFont, m_label.c_str(), { m_center.x - (textSize / 2.0f), m_center.y - 50.0f }, fontSize, 0, GetColor(GlobalOutputs::gray));
    }

    // Icon
    {
        DrawTexture(iconTextures[m_icon], m_center.x - 15.0f, m_center.y + 20.0f, GetColor(GlobalOutputs::gray));
    }
}

float SmallGauge::calculateValueAngle()
{
    return Utils::mapValue(m_minValue, m_maxValue, 90.0f, 360.0f, m_value);
}

void SmallGauge::initResources()
{
    smallFont = LoadFontEx("../resources/fonts/RussoOne-Regular.ttf", 24, 0, 250);
    largeFont = LoadFontEx("../resources/fonts/RussoOne-Regular.ttf", 40, 0, 250);

    int iconSize = 30;
    for (int i = 0; i < Icon::Count; i++) {
        Image img = LoadImageSvg(iconPaths[i], iconSize, iconSize);
        iconTextures[i] = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    Image img = LoadImageSvg("../resources/images/outerCircle.svg", 150, 150);
    outerCircleTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImageSvg("../resources/images/circle.svg", 120, 120);
    innerCircleTexture = LoadTextureFromImage(img);
    UnloadImage(img);
}