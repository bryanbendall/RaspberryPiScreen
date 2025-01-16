#include "RightMapPanel.h"

#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/CameraController.h"
#include <iostream>

RightMapPanel::RightMapPanel()
{
}

RightMapPanel::~RightMapPanel()
{
}

void RightMapPanel::draw(int width, int height)
{
    updateValues();

    RemoteCamera& screenCaptureCamera = CameraController::get().getCamera("ScreenCapture");
    if (screenCaptureCamera.isOpen()) {

        // update texture and draw it
        screenCaptureCamera.updateTexture();
        Texture2D& tex = screenCaptureCamera.getTexture();
        int xOffset = (tex.width - width) / 2;
        int yOffset = (tex.height - height) / 2;
        DrawTexture(tex, -xOffset, -yOffset, WHITE);

    } else {
        int fontSize = 24;
        Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", fontSize);
        if (font) {
            std::string text = "Waiting for connection.";
            Vector2 textSize = MeasureTextEx(*font, text.c_str(), fontSize, 0);
            Vector2 textPosition = { (width / 2.0f) - (textSize.x / 2.0f), (height / 2.0f) - (textSize.y / 2.0f) };
            DrawTextEx(*font, text.c_str(), textPosition, fontSize, 0.0f, GetColor(GlobalOutputs::white));
        }
    }
}

void RightMapPanel::updateValues()
{
}