
#include "gui/CenterWindow.h"
#include "gui/GaugeWindow.h"
#include "raylib.h"
#include "raymath.h"

int main(void)
{
    GaugeWindow gaugeWindow;
    CenterWindow centerWindow;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose()) {
        centerWindow.draw();
        gaugeWindow.draw();
    }

    return 0;
}