#pragma once

#include "raylib.h"

class BarGauge {

public:
    BarGauge(Vector2 position, Vector2 size, float minValue, float maxValue);
    ~BarGauge();
    void draw();
    void setValue(float value) { m_value = value; }

public:
    static void initResources();

private:
    Vector2 m_position;
    Vector2 m_size;
    float m_minValue;
    float m_maxValue;
    float m_value = 0.0f;
};