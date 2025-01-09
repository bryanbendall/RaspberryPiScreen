#include "TouchInput.h"

#include <iostream>

TouchInput::TouchInput(float width, float height)
    : m_width(width)
    , m_height(height)
{
}

void TouchInput::pollTouchEvents()
{
    m_upThisFrame = false;

    if (isDown() && !m_lastTouchState) {
        m_downPosition = getTouchPositionScaled();
    }

    if (!isDown() && m_lastTouchState) {
        m_upPosition = getTouchPositionScaled();
        m_upThisFrame = true;
    }

    m_lastTouchState = isDown();
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

bool TouchInput::isClicked(Rectangle rect)
{
    return CheckCollisionPointRec(m_downPosition, rect) && CheckCollisionPointRec(m_upPosition, rect) && m_upThisFrame;
}