#include "TouchInput.h"

#include <iostream>

TouchInput::TouchInput(float width, float height)
    : m_width(width)
    , m_height(height)
{
}

void TouchInput::pollTouchEvents()
{
    upThisFrame = false;

    if (isDown() && !lastTouch) {
        downPos = getTouchPositionScaled();
    }

    if (!isDown() && lastTouch) {
        upPos = getTouchPositionScaled();
        upThisFrame = true;
    }

    lastTouch = isDown();
}

bool TouchInput::isDown()
{
#ifdef PC_BUILD
    return IsMouseButtonDown(0);
#else
    return GetTouchPointCount() > 0;
#endif
}

bool TouchInput::isDown(Rectangle rect)
{
    return isDown() && CheckCollisionPointRec(getTouchPositionScaled(), rect);
}

Vector2 TouchInput::getTouchPositionScaled()
{
#ifdef PC_BUILD
    Vector2 mousePos = GetMousePosition();
    return { mousePos.y, m_height - mousePos.x };
#else
    Vector2 touchPosition = GetTouchPosition(0);
    return { touchPosition.y * m_width, m_height - touchPosition.x * m_height };
#endif
}

bool TouchInput::isClick(Rectangle rect)
{
    return CheckCollisionPointRec(downPos, rect) && CheckCollisionPointRec(upPos, rect) && upThisFrame;
}