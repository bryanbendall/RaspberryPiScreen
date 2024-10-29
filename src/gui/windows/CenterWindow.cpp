#include "CenterWindow.h"

CenterWindow::CenterWindow()
{
    unsigned int flags = 0;
    // flags |= FLAG_MSAA_4X_HINT;
#ifndef PC_BUILD
    flags |= FLAG_FULLSCREEN_MODE;
#endif

    m_windowID = InitWindowPro(m_height, m_width, "Center Window", flags);

#ifdef PC_BUILD
    SetActiveWindowContext(m_windowID);
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
    SetActiveWindowContext(m_windowID);

    // Render to texture first to be rotated for screen
    BeginTextureMode(m_renderTexture);

    ClearBackground(RED);
    DrawText("I am the other window", 190, 200, 20, RAYWHITE);

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