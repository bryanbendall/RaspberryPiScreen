#include "EgtPanel.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/components/BarGauge.h"

BarGauge b[] = {
    { { 1000.0f, 90.0f }, { 240.0f, 10.0f } },
    { { 1000.0f, 130.0f }, { 240.0f, 10.0f } },
    { { 1000.0f, 170.0f }, { 240.0f, 10.0f } },
    { { 1000.0f, 210.0f }, { 240.0f, 10.0f } },
    { { 1000.0f, 250.0f }, { 240.0f, 10.0f } },
    { { 1000.0f, 290.0f }, { 240.0f, 10.0f } },
    { { 1000.0f, 330.0f }, { 240.0f, 10.0f } },
    { { 1000.0f, 370.0f }, { 240.0f, 10.0f } },
};

EgtPanel::EgtPanel()
{
    b[0].setLabel("#1");
    b[1].setLabel("#2");
    b[2].setLabel("#3");
    b[3].setLabel("#4");
    b[4].setLabel("#5");
    b[5].setLabel("#6");
    b[6].setLabel("#7");
    b[7].setLabel("#8");
}

EgtPanel::~EgtPanel()
{
}

void EgtPanel::draw()
{
    updateValues();

    Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", m_titleSize);

    if (!font)
        return;

    DrawTextEx(*font, "EGT", { 1070.0f, 35.0f }, m_titleSize, 0.0f, GetColor(GlobalOutputs::white));

    for (auto& bar : b)
        bar.draw();
}

void EgtPanel::updateValues()
{
}