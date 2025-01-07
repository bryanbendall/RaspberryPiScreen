#include "Indicator.h"

#include "gui/Assets/AssetManager.h"

Indicator::Indicator(Vector2 position, int size, std::filesystem::path iconFilename, Color activeColor)
    : m_position(position)
    , m_size(size)
    , m_iconFilename(iconFilename)
    , m_activeColor(activeColor)
{
}

Indicator::~Indicator()
{
}

void Indicator::draw()
{
    Texture2D* icon = AssetManager::get().getSvg(m_iconFilename, m_size, m_size);

    if (!icon)
        return;

    if (m_value > 0.0001f)
        DrawTexture(*icon, m_position.x, m_position.y, m_activeColor);
}