
#include "data/DataThread.h"
#include "gui/windows/CenterWindow.h"
#include "gui/windows/GaugeWindow.h"
#include "raylib.h"

int main(void)
{
    DataThread dataThread;

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