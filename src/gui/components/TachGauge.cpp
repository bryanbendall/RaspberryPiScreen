#include "TachGauge.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/Utils.h"
#include <cmath>
#include <fmt/format.h>
#include <raymath.h>
#include <rlgl.h>
#include <string>

TachGauge::TachGauge(Vector2 center, float size)
    : m_center(center)
    , m_size(size)
{
}

TachGauge::~TachGauge()
{
}

void TachGauge::draw()
{
    Font largeFont = AssetManager::get().getFont("RussoOne-Regular.ttf", 40);
    Font smallFont = AssetManager::get().getFont("RussoOne-Regular.ttf", 16);

    Texture2D colorTicks = AssetManager::get().getSvg("tach/ColorTicks.svg", 458, 426);
    Texture2D bottomPanel = AssetManager::get().getSvg("tach/BottomPanel.svg", 244, 122);
    Texture2D gaugeTexture = AssetManager::get().getSvg("tach/Gauge.svg", 476, 457);
    Texture2D smallTicksTexture = AssetManager::get().getSvg("tach/SmallTicks.svg", 453, 422);

    Texture2D needleTexture = AssetManager::get().getImage("tach/Needle.png");

    // Background small ticks
    DrawTextureV(smallTicksTexture, { m_center.x - (453.0f / 2.0f), 13.663f }, GetColor(GlobalOutputs::white));

    // Colored gauge amount
    float valueAngle = Utils::mapValue(0.0f, 10000.0f, 120.0f, 360.0f, m_value);
    Color gaugeColor = m_value > GlobalOutputs::revLimit ? GetColor(GlobalOutputs::red) : Utils::getColorFromBrytec(GlobalOutputs::guageColor);
    DrawCircleSector(m_center, m_size / 2.0f + 3.0f, 120.0f, valueAngle, 20, gaugeColor);

    // Rest of the gauge
    DrawTexture(colorTicks, m_center.x - (458.0f / 2.0f), m_center.y - (426.0f / 2.0f) - 15.0f, Utils::getColorFromBrytec(GlobalOutputs::guageColor));
    DrawTextureV(gaugeTexture, { m_center.x - (476.0f / 2.0f), 2.964f }, GetColor(GlobalOutputs::white));

    // Numbers
    int lableNumber = 10;
    for (int i = 90; i < 330; i += 24) {
        float angle = (float)i * DEG2RAD;
        float r = m_size / 2.0f - 60.0f;
        float x = r * std::sin(angle);
        float y = r * std::cos(angle);

        Color numberColor = lableNumber * 1000 + 1 > GlobalOutputs::revLimit ? GetColor(GlobalOutputs::red) : GetColor(GlobalOutputs::white);

        std::string lable = fmt::format("{:d}", lableNumber);
        Vector2 fontSize = MeasureTextEx(largeFont, lable.c_str(), 40, 0);
        DrawTextEx(largeFont, lable.c_str(), { m_center.x + x - (fontSize.x / 2.0f), m_center.y + y - (fontSize.y / 2.0f) }, 40, 0, numberColor);
        lableNumber--;
    }

    // Needle
    {
        float mappedAngle = Utils::mapValue(0.0f, 10000.0f, 330.0f, 90.0f, m_value, false);
        float angle = mappedAngle * DEG2RAD;
        float r = m_size / 2.0f - 30.0f;
        float x = r * std::sin(angle);
        float y = r * std::cos(angle);

        rlPushMatrix();

        rlTranslatef(m_center.x, m_center.y, 0.0f);
        rlTranslatef(x, y, 0.0f);
        rlRotatef(-(angle * RAD2DEG) - 180.0f, 0.0f, 0.0f, 1.0f);

        DrawTexture(needleTexture, -10, -60, WHITE);

        rlPopMatrix();
    }

    // Bottom panel
    DrawTexture(bottomPanel, m_center.x - (244.0f / 2.0f), 350.0f, GetColor(GlobalOutputs::white));

    // Label
    std::string rpmLable = fmt::format("{:.0f}", m_value);
    DrawTextEx(smallFont, rpmLable.c_str(), Vector2Add(m_center, { m_size / 2.0f - 20.0f, 20.0f }), 16.0f, 0.0f, GetColor(GlobalOutputs::white));
    DrawTextEx(smallFont, "RPM", Vector2Add(m_center, { m_size / 2.0f - 20.0f, 36.0f }), 16.0f, 0.0f, GetColor(GlobalOutputs::gray));
}
