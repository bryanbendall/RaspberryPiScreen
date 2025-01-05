#include "BarGauge.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/Utils.h"

BarGauge::BarGauge(Vector2 position, Vector2 size)
    : m_position(position)
    , m_size(size)
{
}

BarGauge::~BarGauge()
{
}

void BarGauge::draw()
{
    Texture2D fuelIcon = AssetManager::get().getSvg("fuel.svg", m_iconSize, m_iconSize);

    DrawRectangleV(m_position, m_size, GetColor(GlobalOutputs::gray));
    float barX = Utils::mapValue(m_minValue, m_maxValue, 0.0f, m_size.x, m_value);
    DrawRectangleV(m_position, { barX, m_size.y }, Utils::getColorFromBrytec(GlobalOutputs::guageColor));

    DrawTexture(fuelIcon, m_position.x - 40.0f, m_position.y - 10.0f, GetColor(GlobalOutputs::white));
}
