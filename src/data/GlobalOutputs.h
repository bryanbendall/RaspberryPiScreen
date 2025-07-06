#pragma once

#include <map>
#include <stdint.h>
#include <string>

struct GlobalOutputs {

    static inline std::map<std::string, float> values;

    // Constant colors
    static inline uint32_t white = 0xE5E5E5FF;
    static inline uint32_t red = 0xB3272EFF;
    static inline uint32_t orange = 0xFD9012FF;
    static inline uint32_t gray = 0x817C83FF;
    static inline uint32_t green = 0x5ADA17FF;
    static inline uint32_t blue = 0x146AA1FF;
    static inline uint32_t black = 0x000000FF;

    static void setToDefaults()
    {
        for (auto& v : values)
            v.second = 0.0f;

        // Special
        values["guageColor"] = 1216765.0f; // orange
        values["screen1"] = 1.0f;
        values["screen2"] = 1.0f;
        values["revLimit"] = 8000.0f;
    }
};