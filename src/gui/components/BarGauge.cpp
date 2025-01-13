#include "BarGauge.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/Utils.h"
#include <raymath.h>

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

    DrawRectangleV(m_position, m_size, GetColor(GlobalOutputs::gray));
    float barX = Utils::mapValue(m_minValue, m_maxValue, 0.0f, m_size.x, m_value);
    DrawRectangleV(m_position, { barX, m_size.y }, Utils::getColorFromBrytec(GlobalOutputs::guageColor));

    if (!m_iconFilename.empty()) {
        Texture2D* fuelIcon = AssetManager::get().getSvg(m_iconFilename, m_iconSize, m_iconSize);
        if (fuelIcon)
            DrawTexture(*fuelIcon, m_position.x - 40.0f, m_position.y - 10.0f, GetColor(GlobalOutputs::white));
    }

    if (!m_label.empty()) {
        Font* font = AssetManager::get().getFont("RussoOne-Regular.ttf", m_textSize);
        if (font) {
            Vector2 textSize = MeasureTextEx(*font, m_label.c_str(), m_textSize, 0);
            Vector2 labelPos = Vector2Subtract(m_position, { textSize.x + 10.0f, (m_textSize - m_size.y) / 2.0f });
            DrawTextEx(*font, m_label.c_str(), labelPos, m_textSize, 0.0f, GetColor(GlobalOutputs::white));
        }
    }
}
