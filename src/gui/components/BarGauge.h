#pragma once

#include "raylib.h"

class BarGauge {

public:
    BarGauge(Vector2 position, Vector2 size);
    ~BarGauge();
    void draw();

public:
    static void initResources();

private:
    Vector2 m_position;
    Vector2 m_size;
};