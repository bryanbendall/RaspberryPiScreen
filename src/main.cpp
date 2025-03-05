
#include "data/DataThread.h"
#include "data/Gpio.h"
#include "gui/Assets/AssetManager.h"
#include "gui/CameraController.h"
#include "gui/windows/CenterWindow.h"
#include "gui/windows/GaugeWindow.h"
#include "raylib.h"

int main(void)
{
    DataThread dataThread;

    SetTraceLogLevel(LOG_WARNING);

    CameraController cameraController;
    AssetManager assetManager("../resources/");

    GaugeWindow gaugeWindow;
    CenterWindow centerWindow;

    SetTargetFPS(30);
#ifndef PC_BUILD
    HideCursor();
#endif

    while (!WindowShouldClose()) {
        assetManager.update();
        centerWindow.draw();
        gaugeWindow.draw();
    }

    Gpio::shutdown();

    return 0;
}