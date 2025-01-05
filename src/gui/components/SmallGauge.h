#pragma once

#include <filesystem>
#include <raylib.h>
#include <string>

class SmallGauge {

public:
    SmallGauge(Vector2 center, float size, std::string label, std::filesystem::path iconFilename);
    ~SmallGauge();
    void draw();
    void setPosition(Vector2 center) { m_center = center; }
    void setMin(float min) { m_minValue = min; }
    void setMax(float max) { m_maxValue = max; }
    void setDecimals(int decimals) { m_decimals = decimals; }
    void setValue(float value) { m_value = value; }

private:
    float calculateValueAngle();

private:
    Vector2 m_center;
    float m_size;
    float m_innerCircleSize;
    float m_centerLableSize;
    float m_unitLableSize;
    float m_minMaxLableSize;
    float m_iconSize;
    float m_minValue = 0.0f;
    float m_maxValue = 100.0f;
    int m_decimals = 0;
    float m_value = 0.0f;
    std::string m_label;
    std::filesystem::path m_iconFilename;
};