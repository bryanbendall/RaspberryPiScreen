#include "BarGauge.h"

static int refs = 0;
static Texture2D fuelIcon;

BarGauge::BarGauge(Vector2 position, Vector2 size)
    : m_position(position)
    , m_size(size)
{
    refs++;
}

BarGauge::~BarGauge()
{
    refs--;

    if (refs <= 0) {
        UnloadTexture(fuelIcon);
    }
}

void BarGauge::draw()
{
    DrawRectangleV(m_position, m_size, GRAY);

    DrawTexture(fuelIcon, m_position.x - 40.0f, m_position.y - 10.0f, GRAY);
}

void BarGauge::initResources()
{
    int iconSize = 30;
    Image img = LoadImageSvg("../resources/images/fuel.svg", iconSize, iconSize);
    fuelIcon = LoadTextureFromImage(img);
    UnloadImage(img);
}