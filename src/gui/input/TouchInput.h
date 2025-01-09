#pragma once

#include <raylib.h>

class TouchInput {

public:
    TouchInput(float width, float height);
    void pollTouchEvents();
    bool isDown();
    bool isDown(Rectangle rect);
    Vector2 getTouchPositionScaled();
    bool isClicked(Rectangle rect);

private:
    float m_width;
    float m_height;
    bool m_lastTouchState = false;
    bool m_upThisFrame = false;
    Vector2 m_downPosition;
    Vector2 m_upPosition;
};