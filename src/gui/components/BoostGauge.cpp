#include "BoostGauge.h"

#include "data/GlobalVariables.h"
#include "gui/Utils.h"
#include <cmath>
#include <fmt/format.h>
#include <iostream>

static Texture2D maskTexture;
static Font font;

BoostGauge::BoostGauge(Vector2 position)
    : m_position(position)
{
}

BoostGauge::~BoostGauge()
{
    UnloadTexture(maskTexture);
    UnloadFont(font);
}

void BoostGauge::initResources()
{
    Image img = LoadImageSvg("../resources/images/side gauge mask.svg", 150, 480);
    maskTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    font = LoadFontEx("../resources/fonts/RussoOne-Regular.ttf", 24, 0, 250);
}

void BoostGauge::draw()
{
    // Value bar
    float barTopY = Utils::mapValue(0.0f, (float)m_sectors * 10.0f, 480 - m_boarders, m_boarders, m_value);
    DrawRectangle(m_position.x, barTopY, m_width, 480 - m_boarders, Utils::getColorFromBrytec(GlobalVariables::guageColor));

    // White curved line
    DrawTextureV(maskTexture, { m_position.x + 3.0f, m_position.y }, GetColor(GlobalVariables::white));

    // Sector lines
    int tickHeight = (480 - (m_boarders * 2)) / m_sectors;
    for (int i = 0; i <= m_sectors; i++)
        DrawRectangle(m_position.x, tickHeight * i + m_boarders - 1, m_width, 2, GetColor(GlobalVariables::white));

    // Mask
    DrawTextureV(maskTexture, m_position, GetColor(GlobalVariables::black));
    DrawRectangle(m_position.x, 0, m_width, m_boarders - 1, GetColor(GlobalVariables::black));
    DrawRectangle(m_position.x, 480 - m_boarders + 1, m_width, m_boarders, GetColor(GlobalVariables::black));
    DrawRectangle(m_position.x + m_width, 0, 10, 480, GetColor(GlobalVariables::black));

    // Scale numbers
    for (int i = 0; i <= m_sectors; i++) {

        float r = 60.0f;
        float y = (tickHeight * i + m_boarders);
        float circleY = y - 240.0f;
        float angle = (std::cos(-1.0f) * circleY) / r;
        float x = r * std::sin(angle + PI / 2.0f);

        std::string lable = fmt::format("{:d}", (m_sectors - i) * 10);
        Vector2 textSize = MeasureTextEx(font, lable.c_str(), 24.0f, 0.0f);
        DrawTextEx(font, lable.c_str(), { 640 - x - 240 - (textSize.x / 2.0f), y - (textSize.y / 2.0f) }, 24.0f, 0.0f, GetColor(GlobalVariables::white));
    }

    // Label
    Vector2 textSize = MeasureTextEx(font, "Boost", 24.0f, 0.0f);
    DrawTextEx(font, "Boost", { m_position.x + 90.0f, 480.0f - m_boarders + 15.0f }, 24.0f, 0.0f, GetColor(GlobalVariables::gray));
}