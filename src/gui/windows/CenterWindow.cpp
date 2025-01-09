#include "CenterWindow.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/components/SmallGauge.h"
#include <fmt/format.h>
#include <iostream>
#include <rlgl.h>

struct touch {
    bool lastTouch = false;
    Vector2 downPos;
    Vector2 upPos;
    bool upThisFrame = false;
} g_touch;

SmallGauge testGauge({ 200.0f, 200.0f }, 300.0f, "°F", "water-temp.svg");
SmallGauge testGauge1({ 200.0f, 525.0f }, 200.0f, "°F", "water-temp.svg");
SmallGauge testGauge2({ 200.0f, 750.0f }, 100.0f, "°F", "water-temp.svg");
SmallGauge testGauge3({ 200.0f, 875.0f }, 50.0f, "°F", "water-temp.svg");

CenterWindow::CenterWindow()
{
    unsigned int flags = 0;
    // flags |= FLAG_MSAA_4X_HINT;
#ifndef PC_BUILD
    flags |= FLAG_FULLSCREEN_MODE;
#endif

    m_windowID = InitWindowPro(m_height, m_width, "Center Window", flags);

    int windowStatus = SetActiveWindowContext(m_windowID);
    if (windowStatus < 0)
        return;

#ifdef PC_BUILD
    SetWindowPosition(200, 560);
#endif
}

CenterWindow::~CenterWindow()
{
    SetActiveWindowContext(m_windowID);
    CloseWindow();
}

void CenterWindow::draw()
{
    if (!AssetManager::get().setActiveWindow(m_windowID))
        return;

    pollTouchEvents();

    BeginDrawing();
    rlPushMatrix();
    rlTranslatef(1280.0f, 0.0f, 0.0f);
    rlRotatef(90.0f, 0.0f, 0.0f, 1.0f);

    ClearBackground(GetColor(GlobalOutputs::black));

    Rectangle rect;
    rect.x = 100.0f;
    rect.y = 100.0f;
    rect.width = 300.0f;
    rect.height = 100.0f;

    Color col = BLUE;

    Vector2 touchPosition = getTouchPositionScaled();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(touchPosition, rect)) {
        col = YELLOW;
    }

    if (CheckCollisionPointRec(g_touch.downPos, rect) && CheckCollisionPointRec(g_touch.upPos, rect) && g_touch.upThisFrame) {
        std::cout << "Clicked the button" << std::endl;
    }

    DrawRectangleRec(rect, col);

    Vector2 rawTouchPosition = GetTouchPosition(0);
    std::string touchPointStr = fmt::format("x: {:.3f}, y: {:.3f}, touches: {:d}", rawTouchPosition.x, rawTouchPosition.y, GetTouchPointCount());

    Font* smallFont = AssetManager::get().getFont("RussoOne-Regular.ttf", 30);
    if (smallFont)
        DrawTextEx(*smallFont, touchPointStr.c_str(), { 200, 50 }, 30, 0, GetColor(GlobalOutputs::gray));

    rlPopMatrix();
    EndDrawing();
}

Vector2 CenterWindow::getTouchPositionScaled()
{
    Vector2 touchPosition = GetTouchPosition(0);
    return { touchPosition.y * m_width, m_height - touchPosition.x * m_height };
}

bool CenterWindow::isTouchDown()
{
    return GetTouchPointCount() > 0;
}

void CenterWindow::pollTouchEvents()
{
    g_touch.upThisFrame = false;

    if (isTouchDown() && !g_touch.lastTouch) {
        g_touch.downPos = getTouchPositionScaled();
    }

    if (!isTouchDown() && g_touch.lastTouch) {
        g_touch.upPos = getTouchPositionScaled();
        g_touch.upThisFrame = true;
    }

    g_touch.lastTouch = isTouchDown();
}
