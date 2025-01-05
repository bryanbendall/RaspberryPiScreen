#pragma once

#include <raylib.h>

class GearIndicator {

public:
    GearIndicator(Vector2 position, int size);
    ~GearIndicator();
    void draw();
    void setValue(float value) { m_value = value; }

private:
    Vector2 m_position;
    int m_size;
    float m_value = 0.0f;
};