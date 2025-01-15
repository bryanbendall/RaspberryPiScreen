#include "CenterWindow.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/components/UiComponents.h"
#include <fmt/format.h>
#include <iostream>
#include <rlgl.h>

CenterWindow::CenterWindow()
    : m_touchInput(m_width, m_height)
{
    unsigned int flags = 0;
    // flags |= FLAG_MSAA_4X_HINT;
#ifndef PC_BUILD
    flags |= FLAG_FULLSCREEN_MODE;
#endif

    m_windowID = InitWindowPro(m_height, m_width, "Center Window", flags);

    TouchInput::setActiveContext(&m_touchInput);

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

    if (Ui::Button("Test", { 50, 400, 200, 100 }, 38, true)) {
        std::cout << "Clicked the button" << std::endl;
    }

    Ui::Button("Info", { 0, 1180, 150, 100 }, 38, true);
    Ui::Button("Map", { 150, 1180, 150, 100 }, 38, true);
    Ui::Button("Hvac", { 300, 1180, 150, 100 }, 38, true);
    Ui::Button("Settings", { 450, 1180, 150, 100 }, 38, true);

    rlPopMatrix();
    EndDrawing();
}
