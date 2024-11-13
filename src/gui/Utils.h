#pragma once

#include <raylib.h>

namespace Utils {

Color getColorFromBrytec(const float& value);
float mapValue(float fromMin, float fromMax, float toMin, float toMax, float value, bool clamp = true);
}