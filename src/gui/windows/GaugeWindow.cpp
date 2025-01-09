#include "GaugeWindow.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/panels/GaugeWindow/EgtPanel.h"
#include "gui/panels/GaugeWindow/RightMainPanel.h"
#include "gui/panels/GaugeWindow/RightMapPanel.h"
#include <raylib.h>
#include <rlgl.h>

int rightPanelIndex = 1;

GaugeWindow::GaugeWindow()
{
    m_rightPanels.emplace_back(std::make_unique<RightMainPanel>());
    m_rightPanels.emplace_back(std::make_unique<EgtPanel>());
    m_rightPanels.emplace_back(std::make_unique<RightMapPanel>());

    unsigned int flags = 0;
    // flags |= FLAG_MSAA_4X_HINT;
#ifndef PC_BUILD
    flags |= FLAG_FULLSCREEN_MODE;
#endif

    m_windowID = InitWindowPro(1280.0f, 480.0f, "Gauge Window", flags);

    if (!AssetManager::get().setActiveWindow(m_windowID))
        return;

#ifdef PC_BUILD
    SetWindowPosition(200, 40);
#endif
}

GaugeWindow::~GaugeWindow()
{
    SetActiveWindowContext(m_windowID);
    CloseWindow();
}

void GaugeWindow::draw()
{
    // if (IsKeyPressed(KEY_C))
    //     m_camera.open("http://192.168.1.108:8080/stream.mjpeg");
    // if (IsKeyPressed(KEY_D))
    //     m_camera.close();

    if (IsKeyDown(KEY_L))
        GlobalInputs::button0 = 1.0f;
    else
        GlobalInputs::button0 = 0.0f;

    if (IsKeyPressed(KEY_P))
        rightPanelIndex++;

    if (!AssetManager::get().setActiveWindow(m_windowID))
        return;

    BeginDrawing();

    ClearBackground(GetColor(GlobalOutputs::black));

    m_leftMainPanel.draw();
    m_indicatorsPanel.draw();
    m_centerMainPanel.draw();
    m_fuelLevelPanel.draw();

    drawRightPanel();

    DrawFPS(0, 0);

#ifndef PC_BUILD
    DrawRectangleLines(0, 0, 1280, 480, WHITE);
#endif

    EndDrawing();
}

void GaugeWindow::drawRightPanel()
{
    BeginScissorMode(950, 0, 1280 - 950, 430);
    rlPushMatrix();
    rlTranslatef(950.0f, 0.0f, 0.0f);

    // Wrap around if more then max panels
    rightPanelIndex = rightPanelIndex % m_rightPanels.size();
    if (rightPanelIndex < m_rightPanels.size())
        m_rightPanels[rightPanelIndex]->draw();

    rlPopMatrix();
    EndScissorMode();
    return;
}