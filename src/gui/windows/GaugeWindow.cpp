#include "GaugeWindow.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/CameraController.h"
#include "gui/components/UiComponents.h"
#include <raylib.h>
#include <rlgl.h>

int rightPanelIndex = 1;

GaugeWindow::GaugeWindow()
{
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
        Texture2D* texture = AssetManager::get().getCameraTexture("Backup");
        if (texture) {
            float scaling = 0.6f;
            Vector2 texPos = { 640.0f - (texture->width * scaling / 2.0f), 240.0f - (texture->height * scaling / 2.0f) };
            DrawTextureEx(*texture, texPos, 0.0f, scaling, WHITE);
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
    constexpr int numberOfPanels = 3;
    rightPanelIndex = rightPanelIndex % numberOfPanels;

    int panelWidth = 1280 - 950;
    int panelHeight = 430;

    switch (rightPanelIndex) {
    case 0: // Standard gauges
    {
        Ui::SmallGauge({ 80.0f, 140.0f }, 140.0f, "V", "battery.svg", GlobalOutputs::battery, 6.0f, 18.0f, 1);
        Ui::SmallGauge({ 240.0f, 140.0f }, 140.0f, "°F", "transmission-temp.svg", GlobalOutputs::lineTemp, 50.0f, 280.0f);
        Ui::SmallGauge({ 80.0f, 320.0f }, 140.0f, "Gas", "fuel.svg", GlobalOutputs::fuelPressure);
        Ui::SmallGauge({ 240.0f, 320.0f }, 140.0f, "Meth", "fuel.svg", GlobalOutputs::methPressure);
    } break;

    case 1: // Egt
    {
        int titleSize = 40;
        Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", titleSize);
        if (font)
            DrawTextEx(*font, "EGT", { 130.0f, 35.0f }, titleSize, 0.0f, GetColor(GlobalOutputs::white));

        Ui::BarGauge({ 50.0f, 90.0f }, { 240.0f, 10.0f }, 0.0f, "", "#1", 0.0f, 2000.0f);
        Ui::BarGauge({ 50.0f, 130.0f }, { 240.0f, 10.0f }, 0.0f, "", "#2", 0.0f, 2000.0f);
        Ui::BarGauge({ 50.0f, 170.0f }, { 240.0f, 10.0f }, 0.0f, "", "#3", 0.0f, 2000.0f);
        Ui::BarGauge({ 50.0f, 210.0f }, { 240.0f, 10.0f }, 0.0f, "", "#4", 0.0f, 2000.0f);
        Ui::BarGauge({ 50.0f, 250.0f }, { 240.0f, 10.0f }, 0.0f, "", "#5", 0.0f, 2000.0f);
        Ui::BarGauge({ 50.0f, 290.0f }, { 240.0f, 10.0f }, 0.0f, "", "#6", 0.0f, 2000.0f);
        Ui::BarGauge({ 50.0f, 330.0f }, { 240.0f, 10.0f }, 0.0f, "", "#7", 0.0f, 2000.0f);
        Ui::BarGauge({ 50.0f, 370.0f }, { 240.0f, 10.0f }, 0.0f, "", "#8", 0.0f, 2000.0f);
    } break;

    case 2: // Screen capture (map)
    {
        Texture2D* texture = AssetManager::get().getCameraTexture("ScreenCapture");
        if (texture) {

            int xOffset = (texture->width - panelWidth) / 2;
            int yOffset = (texture->height - panelHeight) / 2;
            DrawTexture(*texture, -xOffset, -yOffset, WHITE);

        } else {
            int fontSize = 24;
            Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", fontSize);
            if (font) {
                std::string text = "Waiting for connection.";
                Vector2 textSize = MeasureTextEx(*font, text.c_str(), fontSize, 0);
                Vector2 textPosition = { (panelWidth / 2.0f) - (textSize.x / 2.0f), (panelHeight / 2.0f) - (textSize.y / 2.0f) };
                DrawTextEx(*font, text.c_str(), textPosition, fontSize, 0.0f, GetColor(GlobalOutputs::white));
            }
        }
    } break;
    }

    rlPopMatrix();
    EndScissorMode();
    return;
}