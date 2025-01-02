#include "BarGauge.h"

#include "data/GlobalOutputs.h"
#include "gui/Utils.h"

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
    DrawRectangleV(m_position, m_size, GetColor(GlobalOutputs::gray));
    float barX = Utils::mapValue(m_minValue, m_maxValue, 0.0f, m_size.x, m_value);
    DrawRectangleV(m_position, { barX, m_size.y }, Utils::getColorFromBrytec(GlobalOutputs::guageColor));

    DrawTexture(fuelIcon, m_position.x - 40.0f, m_position.y - 10.0f, GetColor(GlobalOutputs::white));
}

void BarGauge::initResources()
{
    int iconSize = 30;
    Image img = LoadImageSvg("../resources/images/fuel.svg", iconSize, iconSize);
    fuelIcon = LoadTextureFromImage(img);
    UnloadImage(img);
}