#include "GaugeWindow.h"

#include "raylib.h"

GaugeWindow::GaugeWindow()
{
    unsigned int flags = 0;
    flags |= FLAG_MSAA_4X_HINT;
#ifndef PC_BUILD
    flags |= FLAG_FULLSCREEN_MODE;
#endif

    m_windowID = InitWindowPro(1280, 480, "Gauge Window", flags);

#ifdef PC_BUILD
    SetActiveWindowContext(m_windowID);
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
    SetActiveWindowContext(m_windowID);
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("I am the main window", 190, 200, 20, LIGHTGRAY);

    DrawFPS(0, 0);
    EndDrawing();
}