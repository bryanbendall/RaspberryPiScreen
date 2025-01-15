#include "EgtPanel.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/components/UiComponents.h"

EgtPanel::EgtPanel()
{
}

EgtPanel::~EgtPanel()
{
}

void EgtPanel::draw(int width, int height)
{
    int titleSize = 40;

    Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", titleSize);

    if (!font)
        return;

    DrawTextEx(*font, "EGT", { 130.0f, 35.0f }, titleSize, 0.0f, GetColor(GlobalOutputs::white));

    Ui::BarGauge({ 50.0f, 90.0f }, { 240.0f, 10.0f }, 0.0f, "", "#1", 0.0f, 2000.0f);
    Ui::BarGauge({ 50.0f, 130.0f }, { 240.0f, 10.0f }, 0.0f, "", "#2", 0.0f, 2000.0f);
    Ui::BarGauge({ 50.0f, 170.0f }, { 240.0f, 10.0f }, 0.0f, "", "#3", 0.0f, 2000.0f);
    Ui::BarGauge({ 50.0f, 210.0f }, { 240.0f, 10.0f }, 0.0f, "", "#4", 0.0f, 2000.0f);
    Ui::BarGauge({ 50.0f, 250.0f }, { 240.0f, 10.0f }, 0.0f, "", "#5", 0.0f, 2000.0f);
    Ui::BarGauge({ 50.0f, 290.0f }, { 240.0f, 10.0f }, 0.0f, "", "#6", 0.0f, 2000.0f);
    Ui::BarGauge({ 50.0f, 330.0f }, { 240.0f, 10.0f }, 0.0f, "", "#7", 0.0f, 2000.0f);
    Ui::BarGauge({ 50.0f, 370.0f }, { 240.0f, 10.0f }, 0.0f, "", "#8", 0.0f, 2000.0f);
}
