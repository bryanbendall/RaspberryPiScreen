#include "RightMapPanel.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include <iostream>

RightMapPanel::RightMapPanel()
{
}

RightMapPanel::~RightMapPanel()
{
}

void RightMapPanel::draw()
{
    updateValues();

    static bool openCamera = false;
    if (GlobalInputs::openCamera && !openCamera) {
        std::cout << "trying to connect to: " << GlobalInputs::cameraAddress << std::endl;
        m_camera.open(GlobalInputs::cameraAddress);
        openCamera = true;
    } else if (!GlobalInputs::openCamera && openCamera) {
        m_camera.close();
        openCamera = false;
    }

    m_camera.updateTexture();
    if (m_camera.isOpen()) {
        Texture2D& tex = m_camera.getTexture();
        int yOffset = (tex.height - 480) / 2;
        DrawTexture(tex, 0, -yOffset, WHITE);
    } else {
        int fontSize = 24;
        Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", fontSize);
        if (font)
            DrawTextEx(*font, "Waiting for connection.", { 50.0f, 200.0f }, fontSize, 0.0f, GetColor(GlobalOutputs::white));
    }
}

void RightMapPanel::updateValues()
{
}