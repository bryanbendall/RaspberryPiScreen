#include "SmallGauge.h"

#include <algorithm>
#include <format>
#include <iostream>
#include <string>

static int refs = 0;
static Shader shader;
static int glPositionLoc;
static int sizeLoc;
static int valueLoc;

static float windowSize[2];

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
        UnloadShader(shader);
        UnloadFont(smallFont);
        UnloadFont(largeFont);

        for (int i = 0; i < Icon::Count; i++)
            UnloadTexture(iconTextures[i]);
    }
}

void SmallGauge::draw()
{
    if (!IsShaderReady(shader)) {
        std::cout << "Small gauge shader not initalized!" << std::endl;
        return;
    }

    // Ring
    {
        float angle = calculateValueAngle();
        float glPosition[] = { m_center.x - (m_size / 2.0f), windowSize[1] - (m_center.y + (m_size / 2.0f)) };

        BeginShaderMode(shader);

        SetShaderValue(shader, glPositionLoc, &glPosition, SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, sizeLoc, &m_size, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shader, valueLoc, &angle, SHADER_UNIFORM_FLOAT);

        DrawRectangle(m_center.x - (m_size / 2), m_center.y - (m_size / 2), m_size, m_size, RED);

        EndShaderMode();
    }

    // Center value text
    {
        int fontSize = 40;
        std::string lable = std::format("{:.0f}", m_value);
        float textSize = MeasureText(lable.c_str(), fontSize);
        DrawTextEx(largeFont, lable.c_str(), { m_center.x - (textSize / 2.0f), m_center.y - (fontSize / 2) }, fontSize, 0, LIGHTGRAY);
    }

    // Gauge min and max text
    {
        int fontSize = 16;
        std::string lable = std::format("{:.0f}", m_minValue);
        DrawTextEx(smallFont, lable.c_str(), { m_center.x + 8.0f, m_center.y + (m_size / 2) - fontSize }, fontSize, 0, LIGHTGRAY);

        lable = std::format("{:.0f}", m_maxValue);
        DrawTextEx(smallFont, lable.c_str(), { m_center.x + (m_size / 2) - 14.0f, m_center.y + 6.0f }, fontSize, 0, LIGHTGRAY);
    }

    // Gauge label
    {
        int fontSize = 24;
        float textSize = MeasureText(m_label.c_str(), fontSize);
        DrawTextEx(smallFont, m_label.c_str(), { m_center.x - (textSize / 2.0f), m_center.y - 50.0f }, fontSize, 0, GRAY);
    }

    // Icon
    {
        DrawTexture(iconTextures[m_icon], m_center.x - 15.0f, m_center.y + 20.0f, GRAY);
    }
}

float SmallGauge::calculateValueAngle()
{
    float x = m_minValue;
    float y = 0.0f;
    float x1 = m_maxValue;
    float y1 = 270.0f;
    float sloap = (y - y1) / (x - x1);

    float angle = (sloap * (m_value - x1)) + y1;

    return std::clamp(angle, 0.0f, 270.0f);
}

void SmallGauge::initResources()
{
    shader = LoadShader(0, "../resources/shaders/RingGauge.fs");
    glPositionLoc = GetShaderLocation(shader, "u_glPosition");
    sizeLoc = GetShaderLocation(shader, "u_size");
    valueLoc = GetShaderLocation(shader, "u_value");

    windowSize[0] = GetScreenWidth();
    windowSize[1] = GetScreenHeight();

    smallFont = LoadFontEx("../resources/fonts/RussoOne-Regular.ttf", 24, 0, 250);
    largeFont = LoadFontEx("../resources/fonts/RussoOne-Regular.ttf", 40, 0, 250);

    int iconSize = 30;
    for (int i = 0; i < Icon::Count; i++) {
        Image img = LoadImageSvg(iconPaths[i], iconSize, iconSize);
        iconTextures[i] = LoadTextureFromImage(img);
        UnloadImage(img);
    }
}