
#include "gui/windows/CenterWindow.h"
#include "gui/windows/GaugeWindow.h"
#include "raylib.h"
#include "raymath.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    GaugeWindow gaugeWindow;
    CenterWindow centerWindow;

    SetTargetFPS(30);
    HideCursor();

    while (!WindowShouldClose()) {
        centerWindow.draw();
        gaugeWindow.draw();
    }

    return 0;
}