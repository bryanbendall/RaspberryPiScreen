#include "GaugeWindow.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/CameraController.h"
#include "gui/components/UiComponents.h"
#include <fmt/format.h>
#include <raylib.h>
#include <rlgl.h>

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
    if (IsKeyPressed(KEY_P)) {
        GlobalInputs::guageRightPanel += 1.0f;
        if (GlobalInputs::guageRightPanel > 2.1f)
            GlobalInputs::guageRightPanel = 0.0f;
    }

    if (!AssetManager::get().setActiveWindow(m_windowID))
        return;

    BeginDrawing();

    ClearBackground(GetColor(GlobalOutputs::black));

    // Left panel
    {
        Ui::SmallGaugeSpec waterSpec {};
        waterSpec.value = GlobalOutputs::values["cts"];
        waterSpec.center = { 200.0f, 125.0f };
        waterSpec.size = 180.0f;
        waterSpec.label = "°F";
        waterSpec.iconFilename = "water-temp.svg";
        waterSpec.min = 30.0f;
        waterSpec.max = 250.0f;
        waterSpec.highWarning = GlobalOutputs::values["ctsHighWarn"];
        Ui::SmallGauge(waterSpec);

        Ui::SmallGaugeSpec oilSpec {};
        oilSpec.value = GlobalOutputs::values["oilPressure"];
        oilSpec.center = { 200.0f, 325.0f };
        oilSpec.size = 180.0f;
        oilSpec.label = "Psi";
        oilSpec.iconFilename = "engine-oil.svg";
        oilSpec.lowWarning = GlobalOutputs::values["oilPressureLowWarn"];
        Ui::SmallGauge(oilSpec);
    }

    // Indicators
    {
        Ui::Indicator({ 30.0f, 30.0f }, 50, "low-beam.svg", GlobalOutputs::values["parkingLights"], GetColor(GlobalOutputs::orange));
        Ui::Indicator({ 30.0f, 30.0f }, 50, "low-beam.svg", GlobalOutputs::values["lowBeam"], GetColor(GlobalOutputs::green));
        Ui::Indicator({ 30.0f, 30.0f }, 50, "high-beam.svg", GlobalOutputs::values["highBeam"], GetColor(GlobalOutputs::blue));
        Ui::Indicator({ 32.0f, 90.0f }, 45, "fog-lights.svg", GlobalOutputs::values["fogLights"], GetColor(GlobalOutputs::green));
        Ui::Indicator({ 30.0f, 150.0f }, 50, "parking-brake.svg", GlobalOutputs::values["parkingBrake"], GetColor(GlobalOutputs::red));
        Ui::Indicator({ 30.0f, 210.0f }, 50, "fan.svg", GlobalOutputs::values["fanState"], GetColor(GlobalOutputs::blue));
        Ui::Indicator({ 30.0f, 270.0f }, 50, "engine-light.svg", GlobalOutputs::values["engineLight"], GetColor(GlobalOutputs::orange));
    }

    // Center panel
    {
        Ui::BoostGauge({ 310.0f, 0.0f }, GlobalOutputs::values["boost"]);
        Ui::ClosedLoopGauge({ 820.0f, 0.0f }, GlobalOutputs::values["closedLoopComp"]);
        Ui::Tach({ 640.0f, 240.0f }, 450.0f, GlobalOutputs::values["rpm"], GlobalOutputs::values["revLimit"]);
        Ui::Speedometer({ 640.0f, 240.0f }, GlobalOutputs::values["speed"], GlobalOutputs::values["useKph"] > 0.0001f);
        Ui::AfrGauge({ 640.0f, 120.0f }, GlobalOutputs::values["afr"], GlobalOutputs::values["afr2"], GlobalOutputs::values["showSecondAfr"] > 0.0001f);
        Ui::GearIndicator({ 760.0f, 300.0f }, 120, GlobalOutputs::values["gear"]);
    }

    // Turn signals
    {
        Ui::Indicator({ 640.0f - 200.0f, 5.0f }, 50, "left-turn-signal.svg", GlobalOutputs::values["leftTurn"], GetColor(GlobalOutputs::green));
        Ui::Indicator({ 640.0f + 150.0f, 5.0f }, 50, "right-turn-signal.svg", GlobalOutputs::values["rightTurn"], GetColor(GlobalOutputs::green));
    }

    // Fuel levels
    {
        Ui::BarGauge({ 100.0f, 450.0f }, { 240.0f, 10.0f }, GlobalOutputs::values["gasLevel"], "fuel.svg");
        Ui::BarGauge({ 1000.0f, 450.0f }, { 240.0f, 10.0f }, GlobalOutputs::values["methLevel"], "fuel.svg");
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

    // Odometer
    {
        double trip = GlobalInputs::trip;
        double odometer = GlobalInputs::odometer;
        if (GlobalOutputs::values["useKph"] > 0.0001f) {
            trip = trip * 1.609344;
            odometer = odometer * 1.609344;
        }

        Ui::Text({ 640.0f, 380.0f }, "Trip", 20.0f, GetColor(GlobalOutputs::gray));
        std::string tripLable = fmt::format("{:.{}f}", trip, 1);
        Ui::Text({ 640.0f, 400.0f }, tripLable, 30.0f);

        Ui::Text({ 640.0f, 430.0f }, "Odometer", 20.0f, GetColor(GlobalOutputs::gray));
        std::string odoLable = fmt::format("{:.{}f}", odometer, 1);
        Ui::Text({ 640.0f, 450.0f }, odoLable, 30.0f);
    }

    // DrawFPS(0, 0);

    EndDrawing();
}

void GaugeWindow::drawRightPanel()
{
    BeginScissorMode(950, 0, 1280 - 950, 430);
    rlPushMatrix();
    rlTranslatef(950.0f, 0.0f, 0.0f);

    // Wrap around if more then max panels
    constexpr int numberOfPanels = 3;
    int rightPanelIndex = GlobalOutputs::values["guageRightPanel"] + 0.5f;
    rightPanelIndex = rightPanelIndex % numberOfPanels;

    int panelWidth = 1280 - 950;
    int panelHeight = 430;

    switch (rightPanelIndex) {
    case 0: // Standard gauges
    {
        Ui::SmallGaugeSpec batterySpec {};
        batterySpec.value = GlobalOutputs::values["battery"];
        batterySpec.center = { 80.0f, 140.0f };
        batterySpec.size = 140.0f;
        batterySpec.label = "V";
        batterySpec.iconFilename = "battery.svg";
        batterySpec.min = 6.0f;
        batterySpec.max = 18.0f;
        batterySpec.decimals = 1;
        batterySpec.lowWarning = GlobalOutputs::values["batteryLowWarn"];
        batterySpec.highWarning = GlobalOutputs::values["batteryHighWarn"];
        Ui::SmallGauge(batterySpec);

        Ui::SmallGaugeSpec transSpec {};
        transSpec.value = GlobalOutputs::values["battery"];
        transSpec.center = { 240.0f, 140.0f };
        transSpec.size = 140.0f;
        transSpec.label = "°F";
        transSpec.iconFilename = "transmission-temp.svg";
        transSpec.min = 50.0f;
        transSpec.max = 280.0f;
        transSpec.highWarning = GlobalOutputs::values["transTempHighWarn"];
        Ui::SmallGauge(transSpec);

        Ui::SmallGaugeSpec gasSpec {};
        gasSpec.value = GlobalOutputs::values["fuelPressure"];
        gasSpec.center = { 80.0f, 320.0f };
        gasSpec.size = 140.0f;
        gasSpec.label = "Gas";
        gasSpec.iconFilename = "fuel.svg";
        gasSpec.lowWarning = GlobalOutputs::values["fuelPressureLowWarn"];
        Ui::SmallGauge(gasSpec);

        Ui::SmallGaugeSpec methSpec {};
        methSpec.value = GlobalOutputs::values["methPressure"];
        methSpec.center = { 240.0f, 320.0f };
        methSpec.size = 140.0f;
        methSpec.label = "Meth";
        methSpec.iconFilename = "fuel.svg";
        methSpec.lowWarning = GlobalOutputs::values["methPressureLowWarn"];
        Ui::SmallGauge(methSpec);

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