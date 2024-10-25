
#include "gui/CenterWindow.h"
#include "gui/GaugeWindow.h"
#include "raylib.h"
#include "raymath.h"

int main(void)
{
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