#include "CenterWindow.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/components/SmallGauge.h"
#include <fmt/format.h>
#include <iostream>
#include <rlgl.h>

SmallGauge testGauge({ 200.0f, 200.0f }, 300.0f, "°F", "water-temp.svg");
SmallGauge testGauge1({ 200.0f, 525.0f }, 200.0f, "°F", "water-temp.svg");
SmallGauge testGauge2({ 200.0f, 750.0f }, 100.0f, "°F", "water-temp.svg");
SmallGauge testGauge3({ 200.0f, 875.0f }, 50.0f, "°F", "water-temp.svg");

CenterWindow::CenterWindow()
    : m_touchInput(m_width, m_height)
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

    m_touchInput.pollTouchEvents();

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

    if (m_touchInput.isDown(rect))
        col = YELLOW;

    if (m_touchInput.isClicked(rect))
        std::cout << "Clicked the button" << std::endl;

    DrawRectangleRec(rect, col);

    rlPopMatrix();
    EndDrawing();
}
