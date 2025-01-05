#include "GearIndicator.h"

#include "data/GlobalOutputs.h"
#include "gui/Assets/AssetManager.h"
#include "gui/Utils.h"
#include <fmt/format.h>
#include <string>

GearIndicator::GearIndicator(Vector2 position, int size)
    : m_position(position)
    , m_size(size)
{
}

GearIndicator::~GearIndicator()
{
}

void GearIndicator::draw()
{
    Font font = AssetManager::get().getFont("RussoOne-Regular.ttf", m_size);

    std::string lable = "E";
    int value = m_value;

    if (value == -2)
        lable = "P";

    if (value == -1)
        lable = "R";

    if (value == 0)
        lable = "N";

    if (value > 0)
        lable = fmt::format("{:d}", value);

    DrawTextEx(font, lable.c_str(), m_position, m_size, 0, Utils::getColorFromBrytec(GlobalOutputs::guageColor));
}