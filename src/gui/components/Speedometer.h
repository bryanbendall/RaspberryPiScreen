#pragma once

#include <raylib.h>

class Speedometer {

public:
    Speedometer(Vector2 center);
    ~Speedometer();
    void draw();
    void setValue(float value) { m_value = value; }
    void setKph(bool useKph) { m_useKph = useKph; }

private:
    Vector2 m_center;
    float m_value = 0.0f;
    bool m_useKph = false;
    int m_largeFontSize = 100;
    int m_smallFontSize = 26;
};