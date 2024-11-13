#include "Utils.h"

#include <algorithm>
#include <stdint.h>

namespace Utils {

Color getColorFromBrytec(const float& value)
{
    Color color;

    uint32_t temp = (uint32_t)value;
    color.r = temp & 0xFF;
    color.g = (temp >> 8) & 0xFF;
    color.b = (temp >> 16) & 0xFF;
    color.a = 0xFF;

    return color;
}

float mapValue(float fromMin, float fromMax, float toMin, float toMax, float value, bool clamp)
{
    float x = fromMin;
    float y = toMin;
    float x1 = fromMax;
    float y1 = toMax;
    float sloap = (y - y1) / (x - x1);

    float angle = (sloap * (value - x1)) + y1;

    return std::clamp(angle, y, y1);
}
}