#pragma once

#include "raylib.h"
#include <filesystem>

class BarGauge {

public:
    BarGauge(Vector2 position, Vector2 size);
    ~BarGauge();
    void draw();
    void setMin(float min) { m_minValue = min; }
    void setMax(float max) { m_maxValue = max; }
    void setValue(float value) { m_value = value; }
    void setIconFilename(std::filesystem::path iconFilename) { m_iconFilename = iconFilename; }
    void setLabel(std::string label) { m_label = label; }

private:
    Vector2 m_position;
    Vector2 m_size;
    float m_minValue = 0.0f;
    float m_maxValue = 100.0f;
    float m_value = 0.0f;
    int m_iconSize = 30;
    std::filesystem::path m_iconFilename = {};
    std::string m_label;
    int m_textSize = 20;
};