#pragma once

#include <raylib.h>

class TachGauge {

public:
    TachGauge(Vector2 center, float size);
    ~TachGauge();
    void initResources();
    void draw();
    void setMax(float max) { m_maxValue = max; }
    void setValue(float value) { m_value = value; }

private:
    Vector2 m_center;
    float m_size;
    float m_maxValue = 10000.0f;
    float m_value = 0.0f;
};