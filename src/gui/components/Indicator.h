#pragma once

#include <filesystem>
#include <raylib.h>

class Indicator {

public:
    Indicator(Vector2 position, int size, std::filesystem::path iconFilename, Color activeColor);
    ~Indicator();
    void draw();
    void setValue(float value) { m_value = value; }

private:
    Vector2 m_position;
    int m_size;
    float m_minValue;
    float m_maxValue;
    float m_value = 0.0f;
    std::filesystem::path m_iconFilename;
    Color m_activeColor;
};