#include "Indicator.h"

Indicator::Indicator(Vector2 position, int size, std::string iconPath, Color activeColor)
    : m_position(position)
    , m_size(size)
    , m_iconPath(iconPath)
    , m_activeColor(activeColor)
{
}

Indicator::~Indicator()
{
    UnloadTexture(m_texture);
}

void Indicator::initResources()
{
    Image img = LoadImageSvg(m_iconPath.c_str(), m_size, m_size);
    m_texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Indicator::draw()
{
    if (m_value > 0.0001f)
        DrawTexture(m_texture, m_position.x, m_position.y, m_activeColor);
}