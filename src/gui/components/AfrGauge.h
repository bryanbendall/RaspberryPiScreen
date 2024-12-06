#pragma once

#include <raylib.h>
#include <stdint.h>

class AfrGauge {

public:
    AfrGauge(Vector2 center);
    ~AfrGauge();
    void initResources();
    void draw();
    void setValue(uint8_t index, float value) { m_values[index] = value; }
    void setShowBoth(bool both) { m_showBoth = both; }

private:
    Vector2 m_center;
    float m_values[2];
    bool m_showBoth;
    Font m_smallFont;
    Font m_largeFont;
    float m_smallFontSize = 26.0f;
    float m_largeFontSize = 40.0;
};