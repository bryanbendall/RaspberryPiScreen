#include "TachGauge.h"

#include "data/GlobalVariables.h"
#include "gui/Utils.h"

static Texture2D outerCircleTexture;
static Texture2D innerCircleTexture;

TachGauge::TachGauge(Vector2 center, float size, float maxValue)
    : m_center(center)
    , m_size(size)
    , m_maxValue(maxValue)
{
}

TachGauge::~TachGauge()
{
    UnloadTexture(outerCircleTexture);
    UnloadTexture(innerCircleTexture);
}

void TachGauge::initResources()
{
    Image img = LoadImageSvg("../resources/images/outerCircle.svg", m_size, m_size);
    outerCircleTexture = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImageSvg("../resources/images/radial gradient.svg", m_size + 200, m_size + 200);
    innerCircleTexture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void TachGauge::Draw()
{
    DrawCircleSector(m_center, m_size / 2.0f, 110.0f, 360.0f, 20, GetColor(GlobalVariables::orange));

    DrawTexture(outerCircleTexture, m_center.x - (m_size / 2), m_center.y - (m_size / 2), GetColor(GlobalVariables::black));
    DrawTexture(innerCircleTexture, m_center.x - (m_size / 2) - 100, m_center.y - (m_size / 2) - 100, GetColor(GlobalVariables::black));
}