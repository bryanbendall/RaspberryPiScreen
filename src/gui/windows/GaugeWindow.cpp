#include "GaugeWindow.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/CameraController.h"
#include "gui/components/UiComponents.h"
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

    // Left panel
    {
        Ui::SmallGauge({ 200.0f, 125.0f }, 180.0f, "°F", "water-temp.svg", GlobalOutputs::cts, 30.0f, 250.0f);
        Ui::SmallGauge({ 200.0f, 325.0f }, 180.0f, "Psi", "engine-oil.svg", GlobalOutputs::oilPressure);
    }

    // Indicators
    {
        Ui::Indicator({ 30.0f, 30.0f }, 50, "low-beam.svg", GlobalOutputs::parkingLights, GetColor(GlobalOutputs::orange));
        Ui::Indicator({ 30.0f, 30.0f }, 50, "low-beam.svg", GlobalOutputs::lowBeam, GetColor(GlobalOutputs::green));
        Ui::Indicator({ 30.0f, 30.0f }, 50, "high-beam.svg", GlobalOutputs::highBeam, GetColor(GlobalOutputs::blue));
        Ui::Indicator({ 32.0f, 90.0f }, 45, "fog-lights.svg", GlobalOutputs::fogLights, GetColor(GlobalOutputs::green));
        Ui::Indicator({ 30.0f, 150.0f }, 50, "parking-brake.svg", GlobalOutputs::parkingBrake, GetColor(GlobalOutputs::red));
        Ui::Indicator({ 30.0f, 210.0f }, 50, "fan.svg", GlobalOutputs::fanState, GetColor(GlobalOutputs::blue));
        Ui::Indicator({ 30.0f, 270.0f }, 50, "engine-light.svg", GlobalOutputs::engineLight, GetColor(GlobalOutputs::orange));
    }

    // Center panel
    {
        Ui::BoostGauge({ 310.0f, 0.0f }, GlobalOutputs::boost);
        Ui::ClosedLoopGauge({ 820.0f, 0.0f }, GlobalOutputs::closedLoopComp);
        Ui::Tach({ 640.0f, 240.0f }, 450.0f, GlobalOutputs::rpm, GlobalOutputs::revLimit);
        Ui::Speedometer({ 640.0f, 240.0f }, GlobalOutputs::speed, GlobalOutputs::useKph > 0.0001f);
        Ui::AfrGauge({ 640.0f, 120.0f }, GlobalOutputs::afr, GlobalOutputs::afr2, GlobalOutputs::showSecondAfr > 0.0001f);
        Ui::GearIndicator({ 760.0f, 300.0f }, 120, GlobalOutputs::gear);
    }

    // Turn signals
    {
        Ui::Indicator({ 640.0f - 200.0f, 5.0f }, 50, "left-turn-signal.svg", GlobalOutputs::leftTurn, GetColor(GlobalOutputs::green));
        Ui::Indicator({ 640.0f + 150.0f, 5.0f }, 50, "right-turn-signal.svg", GlobalOutputs::rightTurn, GetColor(GlobalOutputs::green));
    }

    // Fuel levels
    {
        Ui::BarGauge({ 100.0f, 450.0f }, { 240.0f, 10.0f }, GlobalOutputs::gasLevel, "fuel.svg");
        Ui::BarGauge({ 1000.0f, 450.0f }, { 240.0f, 10.0f }, GlobalOutputs::methLevel, "fuel.svg");
    }

    drawRightPanel();

    // Camera
    {
        RemoteCamera& backupCamera = CameraController::get().getCamera("Backup");
        if (backupCamera.isOpen()) {
            Texture2D& tex = backupCamera.getTexture();
            float scaling = 0.6f;
            Vector2 texPos = { 640.0f - (tex.width * scaling / 2.0f), 240.0f - (tex.height * scaling / 2.0f) };
            DrawTextureEx(tex, texPos, 0.0f, scaling, WHITE);
        }
    }

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
        m_rightPanels[rightPanelIndex]->draw(1280 - 950, 430);

    rlPopMatrix();
    EndScissorMode();
    return;
}