#pragma once

#include "raylib.h"

class BarGauge {

public:
    BarGauge(Vector2 position, Vector2 size);
    ~BarGauge();
    void draw();
    void setMin(float min) { m_minValue = min; }
    void setMax(float max) { m_maxValue = max; }
    void setValue(float value) { m_value = value; }

private:
    Vector2 m_position;
    Vector2 m_size;
    float m_minValue = 0.0f;
    float m_maxValue = 100.0f;
    float m_value = 0.0f;
    int m_iconSize = 30;
};