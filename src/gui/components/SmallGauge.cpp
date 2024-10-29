#include "SmallGauge.h"

#include <algorithm>
#include <format>
#include <iostream>
#include <string>

int refs = 0;
Shader shader;
int windowSizeLoc;
int positionLoc;
int sizeLoc;
int valueLoc;

float windowSize[2];

SmallGauge::SmallGauge(Vector2 position, float size, float minValue, float maxValue)
    : m_minValue(minValue)
    , m_maxValue(maxValue)
{
    refs++;
    setPosition(position);
    m_size = size;
}

SmallGauge::~SmallGauge()
{
    refs--;

    if (refs <= 0)
        UnloadShader(shader);
}

void SmallGauge::draw()
{
    if (!IsShaderReady(shader)) {
        std::cout << "Small gauge shader not initalized!" << std::endl;
        return;
    }

    float angle = calculateValueAngle();

    BeginShaderMode(shader);

    SetShaderValue(shader, windowSizeLoc, &windowSize, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, positionLoc, &m_position, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, sizeLoc, &m_size, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, valueLoc, &angle, SHADER_UNIFORM_FLOAT);
    DrawRectangle(m_position[0], m_position[1], m_size, m_size, RED);

    EndShaderMode();

    std::string lable = std::format("{:.1f}", m_value);
    MeasureText(lable.c_str(), 30);
    DrawText(lable.c_str(), m_position[0] + (m_size / 3), m_position[1] + (m_size / 3), 30, LIGHTGRAY);
}

void SmallGauge::setPosition(Vector2 position)
{
    m_position[0] = position.x;
    m_position[1] = position.y;
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

void SmallGauge::initShader()
{
    shader = LoadShader(0, "../resources/shaders/RingGauge.fs");
    windowSizeLoc = GetShaderLocation(shader, "u_windowSize");
    positionLoc = GetShaderLocation(shader, "u_position");
    sizeLoc = GetShaderLocation(shader, "u_size");
    valueLoc = GetShaderLocation(shader, "u_value");

    windowSize[0] = GetScreenWidth();
    windowSize[1] = GetScreenHeight();
}