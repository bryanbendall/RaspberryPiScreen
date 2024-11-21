#include "TachGauge.h"

#include "data/GlobalVariables.h"
#include "gui/Utils.h"
#include <cmath>
#include <fmt/format.h>
#include <raymath.h>
#include <rlgl.h>
#include <string>

static Texture2D tickTexture;
static Texture2D colorTicks;
static Texture2D bottomPanel;
static Texture2D gaugeTexture;
static Texture2D smallTicksTexture;
static Texture2D needleTexture;

static Font font;

TachGauge::TachGauge(Vector2 center, float size, float maxValue)
    : m_center(center)
    , m_size(size)
    , m_maxValue(maxValue)
{
}

TachGauge::~TachGauge()
{
    UnloadTexture(tickTexture);
    UnloadTexture(colorTicks);
    UnloadTexture(bottomPanel);
    UnloadTexture(gaugeTexture);
    UnloadTexture(smallTicksTexture);
    UnloadTexture(needleTexture);

    UnloadFont(font);
}

void TachGauge::initResources()
{
    Image img = LoadImageSvg("../resources/images/Tick.svg", 70, 22);
    tickTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImageSvg("../resources/images/tach/ColorTicks.svg", 458, 426);
    colorTicks = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImageSvg("../resources/images/tach/BottomPanel.svg", 244, 122);
    bottomPanel = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImageSvg("../resources/images/tach/Gauge.svg", 476, 457);
    gaugeTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImageSvg("../resources/images/tach/SmallTicks.svg", 453, 422);
    smallTicksTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("../resources/images/tach/Needle.png");
    needleTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    font = LoadFontEx("../resources/fonts/RussoOne-Regular.ttf", 40, 0, 250);
}

void TachGauge::draw()
{
    // Background small ticks
    DrawTextureV(smallTicksTexture, { m_center.x - (453.0f / 2.0f), 13.663f }, GetColor(GlobalVariables::white));

    // Colored gauge amount
    float valueAngle = Utils::mapValue(0.0f, 10000.0f, 120.0f, 360.0f, m_value);
    Color gaugeColor = m_value > GlobalVariables::revLimit ? GetColor(GlobalVariables::red) : Utils::getColorFromBrytec(GlobalVariables::guageColor);
    DrawCircleSector(m_center, m_size / 2.0f + 3.0f, 120.0f, valueAngle, 20, gaugeColor);

    // Rest of the gauge
    DrawTexture(colorTicks, m_center.x - (458.0f / 2.0f), m_center.y - (426.0f / 2.0f) - 15.0f, Utils::getColorFromBrytec(GlobalVariables::guageColor));
    DrawTextureV(gaugeTexture, { m_center.x - (476.0f / 2.0f), 2.964f }, GetColor(GlobalVariables::white));

    // Numbers
    int lableNumber = 10;
    for (int i = 90; i < 330; i += 24) {
        float angle = (float)i * DEG2RAD;
        float r = m_size / 2.0f - 60.0f;
        float x = r * std::sinf(angle);
        float y = r * std::cosf(angle);

        Color numberColor = lableNumber * 1000 + 1 > GlobalVariables::revLimit ? GetColor(GlobalVariables::red) : GetColor(GlobalVariables::white);

        std::string lable = fmt::format("{:d}", lableNumber);
        Vector2 fontSize = MeasureTextEx(font, lable.c_str(), 40, 0);
        DrawTextEx(font, lable.c_str(), { m_center.x + x - (fontSize.x / 2.0f), m_center.y + y - (fontSize.y / 2.0f) }, 40, 0, numberColor);
        lableNumber--;
    }

    // Needle
    {
        float mappedAngle = Utils::mapValue(0.0f, 10000.0f, 330.0f, 90.0f, m_value, false);
        float angle = mappedAngle * DEG2RAD;
        float r = m_size / 2.0f - 30.0f;
        float x = r * std::sinf(angle);
        float y = r * std::cosf(angle);

        rlPushMatrix();

        rlTranslatef(m_center.x, m_center.y, 0.0f);
        rlTranslatef(x, y, 0.0f);
        rlRotatef(-(angle * RAD2DEG) - 180.0f, 0.0f, 0.0f, 1.0f);

        DrawTexture(needleTexture, -10, -60, WHITE);

        rlPopMatrix();
    }

    // Bottom panel
    DrawTexture(bottomPanel, m_center.x - (244.0f / 2.0f), 350.0f, GetColor(GlobalVariables::white));
}
