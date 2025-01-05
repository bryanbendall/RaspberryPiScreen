#include "CenterWindow.h"

#include "gui/Assets/AssetManager.h"
#include "gui/components/SmallGauge.h"
#include <iostream>

SmallGauge testGauge({ 200.0f, 200.0f }, 300.0f, "°F", "water-temp.svg");
SmallGauge testGauge1({ 200.0f, 525.0f }, 200.0f, "°F", "water-temp.svg");
SmallGauge testGauge2({ 200.0f, 750.0f }, 100.0f, "°F", "water-temp.svg");
SmallGauge testGauge3({ 200.0f, 875.0f }, 50.0f, "°F", "water-temp.svg");

CenterWindow::CenterWindow()
{
    unsigned int flags = 0;
    // flags |= FLAG_MSAA_4X_HINT;
#ifndef PC_BUILD
    flags |= FLAG_FULLSCREEN_MODE;
#endif

    m_windowID = InitWindowPro(m_height, m_width, "Center Window", flags);

    int windowStatus = SetActiveWindowContext(m_windowID);
    if (windowStatus < 0)
        return;

#ifdef PC_BUILD
    SetWindowPosition(200, 560);
#endif

    m_renderTexture = LoadRenderTexture(m_width, m_height);
}

CenterWindow::~CenterWindow()
{
    SetActiveWindowContext(m_windowID);

    UnloadRenderTexture(m_renderTexture);
    CloseWindow();
}

void CenterWindow::draw()
{
    if (!AssetManager::get().setActiveWindow(m_windowID))
        return;

    // Render to texture first to be rotated for screen
    BeginTextureMode(m_renderTexture);

    ClearBackground(RED);
    DrawText("I am the other window", 190, 200, 20, RAYWHITE);

    Rectangle rect;
    rect.x = 100.0f;
    rect.y = 100.0f;
    rect.width = 300.0f;
    rect.height = 100.0f;

    Color col = BLUE;

    Vector2 touchPosition = getTouchPositionScaled();
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(touchPosition, rect)) {
        col = YELLOW;
    }

    DrawRectangleRec(rect, col);

    testGauge.draw();
    testGauge1.draw();
    testGauge2.draw();
    testGauge3.draw();

    EndTextureMode();

    drawRotatedTextureToScreen();
}

void CenterWindow::drawRotatedTextureToScreen()
{
    BeginDrawing();
    DrawTexturePro(m_renderTexture.texture,
        (Rectangle) { 0, 0, (float)m_renderTexture.texture.width, (float)-m_renderTexture.texture.height },
        (Rectangle) { (float)m_height / 2.0f, (float)m_width / 2.0f, (float)m_width, (float)m_height },
        { (float)m_width / 2.0f, (float)m_height / 2.0f },
        m_rotation,
        WHITE);
    EndDrawing();
}

Vector2 CenterWindow::getTouchPositionScaled()
{
    Vector2 touchPosition = GetTouchPosition(0);
    return { touchPosition.y * m_width, m_height - touchPosition.x * m_height };
}
