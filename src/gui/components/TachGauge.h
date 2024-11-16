#pragma once

#include <raylib.h>

class TachGauge {

public:
    TachGauge(Vector2 center, float size, float maxValue);
    ~TachGauge();
    void initResources();
    void Draw();
    void setValue(float value) { m_value = value; }

private:
    Vector2 m_center;
    float m_size;
    float m_maxValue;
    float m_value = 0.0f;
};