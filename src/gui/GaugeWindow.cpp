#include "GaugeWindow.h"

#include "raylib.h"

Shader shader;
int offsetLoc;
int sizeLoc;
int windowSizeLoc;
float offset[] = { 200.0f, 50.0f, 600.0f, 100.0f };
float size[] = { 400.0f, 400.0f };
float windowSize[2];

GaugeWindow::GaugeWindow()
{
    unsigned int flags = 0;
    // flags |= FLAG_MSAA_4X_HINT;
#ifndef PC_BUILD
    flags |= FLAG_FULLSCREEN_MODE;
#endif

    m_windowID = InitWindowPro(1280.0f, 480.0f, "Gauge Window", flags);
    windowSize[0] = GetScreenWidth();
    windowSize[1] = GetScreenHeight();

#ifdef PC_BUILD
    SetActiveWindowContext(m_windowID);
    SetWindowPosition(200, 40);
#endif

    shader = LoadShader(0, "../resources/shaders/test.fs");
    offsetLoc = GetShaderLocation(shader, "offset");
    sizeLoc = GetShaderLocation(shader, "size");
    windowSizeLoc = GetShaderLocation(shader, "windowSize");
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

    ClearBackground(BLACK);
    // DrawText("I am the main window", 190, 200, 20, LIGHTGRAY);

    DrawRing({ 2560 / 2.0f, 1080 / 2.0f }, 450.0f / 2.0f - 20.0f, 450.0f / 2.0f, 120.0f, 360.0f, 30, BLUE);

    BeginShaderMode(shader);

    SetShaderValue(shader, offsetLoc, &offset, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, sizeLoc, &size, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, windowSizeLoc, &windowSize, SHADER_UNIFORM_VEC2);
    DrawRectangle(offset[0], offset[1], size[0], size[1], RED);

    EndShaderMode();

    BeginShaderMode(shader);

    SetShaderValue(shader, offsetLoc, &offset[2], SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, sizeLoc, &size, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, windowSizeLoc, &windowSize, SHADER_UNIFORM_VEC2);
    DrawRectangle(offset[2], offset[3], size[0], size[1], RED);

    EndShaderMode();

    DrawFPS(0, 0);
    EndDrawing();
}