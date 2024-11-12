#include "Utils.h"

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

}