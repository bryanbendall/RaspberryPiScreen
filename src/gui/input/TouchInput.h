#pragma once

#include <raylib.h>

class TouchInput {

public:
    TouchInput(float width, float height);
    void pollTouchEvents();
    bool isDown();
    bool isDown(Rectangle rect);
    Vector2 getTouchPositionScaled();
    bool isClick(Rectangle rect);

private:
    float m_width;
    float m_height;
    bool lastTouch = false;
    bool upThisFrame = false;
    Vector2 downPos;
    Vector2 upPos;
};