#include "EgtPanel.h"

EgtPanel::EgtPanel()
{
}

EgtPanel::~EgtPanel()
{
}

void EgtPanel::draw()
{
    updateValues();

    DrawRectangle(1020, 100, 200, 200, YELLOW);
}

void EgtPanel::updateValues()
{
}