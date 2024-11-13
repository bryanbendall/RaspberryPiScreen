#include "GaugeWindow.h"

#include "data/GlobalVariables.h"
#include "gui/Utils.h"
#include "gui/components/BarGauge.h"
#include "gui/components/SmallGauge.h"
#include "raylib.h"

SmallGauge waterGauge({ 200.0f, 125.0f }, 150.0f, 30.0f, 250.0f, "°F", SmallGauge::Icon::WaterTemp);
SmallGauge oilGauge({ 200.0f, 325.0f }, 150.0f, 0.0f, 100.0f, "Psi", SmallGauge::Icon::Oil);

SmallGauge batteryGauge({ 1000.0f, 100.0f }, 150.0f, 6.0f, 18.0f, "V", SmallGauge::Icon::Battery);
SmallGauge transGauge({ 1170.0f, 100.0f }, 150.0f, 50.0f, 280.0f, "°F", SmallGauge::Icon::TransTemp);
SmallGauge gasGauge({ 1000.0f, 270.0f }, 150.0f, 0.0f, 100.0f, "Gas", SmallGauge::Icon::Fuel);
SmallGauge methGauge({ 1170.0f, 270.0f }, 150.0f, 0.0f, 100.0f, "Meth", SmallGauge::Icon::Fuel);

BarGauge gasLevel({ 1000.0f, 390.0f }, { 240.0f, 10.0f }, 0.0f, 100.0f);
BarGauge methLevel({ 1000.0f, 430.0f }, { 240.0f, 10.0f }, 0.0f, 100.0f);

GaugeWindow::GaugeWindow()
{
    unsigned int flags = 0;
    // flags |= FLAG_MSAA_4X_HINT;
#ifndef PC_BUILD
    flags |= FLAG_FULLSCREEN_MODE;
#endif

    m_windowID = InitWindowPro(1280.0f, 480.0f, "Gauge Window", flags);

#ifdef PC_BUILD
    SetActiveWindowContext(m_windowID);
    SetWindowPosition(200, 40);
#endif

    SmallGauge::initResources();
    BarGauge::initResources();
}

GaugeWindow::~GaugeWindow()
{
    SetActiveWindowContext(m_windowID);
    CloseWindow();
}

void GaugeWindow::draw()
{
    waterGauge.setValue(GlobalVariables::cts);
    oilGauge.setValue(GlobalVariables::oilPressure);

    batteryGauge.setValue(GlobalVariables::battery);
    transGauge.setValue(GlobalVariables::lineTemp);
    gasGauge.setValue(GlobalVariables::fuelPressure);
    methGauge.setValue(GlobalVariables::methPressure);

    gasLevel.setValue(GlobalVariables::gasLevel);
    methLevel.setValue(GlobalVariables::methLevel);

    SetActiveWindowContext(m_windowID);
    BeginDrawing();

    ClearBackground(GetColor(GlobalVariables::black));

    waterGauge.draw();
    oilGauge.draw();

    batteryGauge.draw();
    transGauge.draw();
    gasGauge.draw();
    methGauge.draw();

    gasLevel.draw();
    methLevel.draw();

    DrawFPS(0, 0);

#ifndef PC_BUILD
    DrawRectangleLines(0, 0, 1280, 480, WHITE);
#endif

    EndDrawing();
}