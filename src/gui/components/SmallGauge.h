#pragma once

#include "raylib.h"

class SmallGauge {

public:
    SmallGauge(Vector2 position, float size, float minValue, float maxValue);
    ~SmallGauge();
    void draw();
    void setPosition(Vector2 position);
    void setSize(float size) { m_size = size; }
    void setValue(float value) { m_value = value; }

private:
    float calculateValueAngle();

public:
    static void initShader();

private:
    float m_position[2];
    float m_size;
    float m_minValue;
    float m_maxValue;
    float m_value = 0.0f;
};