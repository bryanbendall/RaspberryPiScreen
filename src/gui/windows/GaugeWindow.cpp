#include "GaugeWindow.h"

#include "gui/components/SmallGauge.h"
#include "raylib.h"

SmallGauge waterGauge({ 200.0f, 125.0f }, 150.0f, 30.0f, 250.0f, "°F", SmallGauge::Icon::WaterTemp);
SmallGauge oilGauge({ 200.0f, 325.0f }, 150.0f, 0.0f, 100.0f, "Psi", SmallGauge::Icon::Oil);

SmallGauge batteryGauge({ 1000.0f, 100.0f }, 140.0f, 6.0f, 18.0f, "V", SmallGauge::Icon::Battery);
SmallGauge transGauge({ 1170.0f, 100.0f }, 140.0f, 50.0f, 280.0f, "°F", SmallGauge::Icon::TransTemp);
SmallGauge gasGauge({ 1000.0f, 270.0f }, 140.0f, 0.0f, 100.0f, "Gas", SmallGauge::Icon::Fuel);
SmallGauge methGauge({ 1170.0f, 270.0f }, 140.0f, 0.0f, 100.0f, "Meth", SmallGauge::Icon::Fuel);

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

    SmallGauge::initShader();
}

GaugeWindow::~GaugeWindow()
{
    SetActiveWindowContext(m_windowID);
    CloseWindow();
}

void GaugeWindow::draw()
{
    static float value = 0.0f;
    value += 2.0f;
    if (value > 200.0f)
        value = -50.0f;

    waterGauge.setValue(value);
    oilGauge.setValue(value);

    SetActiveWindowContext(m_windowID);
    BeginDrawing();

    ClearBackground(BLACK);

    waterGauge.draw();
    oilGauge.draw();

    batteryGauge.draw();
    transGauge.draw();
    gasGauge.draw();
    methGauge.draw();

    DrawFPS(0, 0);
    EndDrawing();
}