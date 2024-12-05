#pragma once

#include <raylib.h>
#include <string>

class Indicator {

public:
    Indicator(Vector2 position, int size, std::string iconPath, Color activeColor);
    ~Indicator();
    void initResources();
    void draw();
    void setValue(float value) { m_value = value; }

private:
    Vector2 m_position;
    int m_size;
    float m_minValue;
    float m_maxValue;
    float m_value = 0.0f;
    std::string m_iconPath;
    Texture2D m_texture;
    Color m_activeColor;
};