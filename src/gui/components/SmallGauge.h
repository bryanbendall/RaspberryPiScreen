#pragma once

#include "raylib.h"
#include <string>

class SmallGauge {

public:
    enum Icon {
        WaterTemp = 0,
        TransTemp,
        Fuel,
        Oil,
        Battery,
        Count
    };

public:
    SmallGauge(Vector2 center, float size, float minValue, float maxValue, std::string label, Icon icon);
    ~SmallGauge();
    void draw();
    void setPosition(Vector2 center) { m_center = center; }
    void setSize(float size) { m_size = size; }
    void setValue(float value) { m_value = value; }

private:
    float calculateValueAngle();

public:
    static void initResources();

private:
    Vector2 m_center;
    float m_size;
    float m_minValue;
    float m_maxValue;
    float m_value = 0.0f;
    std::string m_label;
    Icon m_icon;
};