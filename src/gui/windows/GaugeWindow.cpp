#include "GaugeWindow.h"

#include "gui/components/SmallGauge.h"
#include "raylib.h"

SmallGauge gauge({ 50.0f, 50.0f }, 150.0f, 0.0f, 100.0f);
SmallGauge gauge2({ 50.0f, 250.0f }, 150.0f, 0.0f, 50.0f);

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
    if (value > 100.0f)
        value = 0.0f;

    gauge.setValue(value);
    gauge2.setValue(value);

    SetActiveWindowContext(m_windowID);
    BeginDrawing();

    ClearBackground(BLACK);
    // DrawText("I am the main window", 190, 200, 20, LIGHTGRAY);

    DrawRing({ 600.0f, 300.0f }, 80.0f, 100.0f, 120.0f, 360.0f, 30, BLUE);

    gauge.draw();
    gauge2.draw();

    DrawFPS(0, 0);
    EndDrawing();
}