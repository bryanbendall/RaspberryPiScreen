#include "ClosedLoopGauge.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/Utils.h"
#include <cmath>
#include <fmt/format.h>
#include <iostream>

ClosedLoopGauge::ClosedLoopGauge(Vector2 position)
    : m_position(position)
{
}

ClosedLoopGauge::~ClosedLoopGauge()
{
}

void ClosedLoopGauge::draw()
{
    Font font = AssetManager::get().getFont("RussoOne-Regular.ttf", 24);
    Texture2D maskTexture = AssetManager::get().getSvg("side gauge mask.svg", 150, 480);

    // Value bar
    Color gaugeColor = m_value > 25.0f || m_value < -25.0f ? GetColor(GlobalOutputs::red) : Utils::getColorFromBrytec(GlobalOutputs::guageColor);
    if (m_value > 0.0f) {
        float barTopY = Utils::mapValue(0.0f, 50.0f, 240, m_boarders, m_value);
        DrawRectangle(m_position.x, barTopY, m_width, 240 - barTopY, gaugeColor);
    } else {
        float barHeight = Utils::mapValue(0.0f, -50.0f, 240, 480 - m_boarders, m_value);
        DrawRectangle(m_position.x, 240, m_width, barHeight - 240, gaugeColor);
    }

    // White curved line
    Rectangle srcRect { 0, 0, -150, 480 };
    DrawTextureRec(maskTexture, srcRect, { m_position.x - 3.0f, m_position.y }, GetColor(GlobalOutputs::white));

    // Sector lines
    int tickHeight = (480 - (m_boarders * 2)) / m_sectors;
    for (int i = 0; i <= m_sectors; i++)
        DrawRectangle(m_position.x, tickHeight * i + m_boarders - 1, m_width, 2, GetColor(GlobalOutputs::white));

    // Mask
    DrawTextureRec(maskTexture, srcRect, m_position, GetColor(GlobalOutputs::black));
    DrawRectangle(m_position.x, 0, m_width, m_boarders - 1, GetColor(GlobalOutputs::black));
    DrawRectangle(m_position.x, 480 - m_boarders + 1, m_width, m_boarders, GetColor(GlobalOutputs::black));
    DrawRectangle(m_position.x - 10, 0, 10, 480, GetColor(GlobalOutputs::black));

    // Scale numbers
    for (int i = 0; i <= m_sectors; i++) {

        float r = 60.0f;
        float y = (tickHeight * i + m_boarders);
        float circleY = y - 240.0f;
        float angle = (std::cos(-1.0f) * circleY) / r;
        float x = r * std::sin(angle + PI / 2.0f);

        std::string lable = fmt::format("{:d}", (2 - i) * 25);
        Vector2 textSize = MeasureTextEx(font, lable.c_str(), 24.0f, 0.0f);
        DrawTextEx(font, lable.c_str(), { 640 + x + 215 + (textSize.x / 2.0f), y - (textSize.y / 2.0f) }, 24.0f, 0.0f, GetColor(GlobalOutputs::white));
    }

    // Label
    Vector2 textSize = MeasureTextEx(font, "CL%", 24.0f, 0.0f);
    DrawTextEx(font, "CL%", { m_position.x, 480.0f - m_boarders + 15.0f }, 24.0f, 0.0f, GetColor(GlobalOutputs::gray));
}