#pragma once

#include <raylib.h>

class ClosedLoopGauge {

public:
    ClosedLoopGauge(Vector2 position);
    ~ClosedLoopGauge();
    void initResources();
    void draw();
    void setValue(float value) { m_value = value; }

private:
    Vector2 m_position;
    float m_value = 0.0f;
    int m_boarders = 60;
    int m_width = 150;
    int m_sectors = 4;
};