#pragma once

#include <map>
#include <string>

struct GlobalInputs {

    static inline float button0;

    static inline float acOnTemp = 45.0f;
    static inline float acOffTemp = 40.0f;
    static inline float hvacFan = 0.0f;
    static inline float hvacLevel = 0.0f;
    static inline float acEnable = 0.0f;

    static inline const std::map<std::string, float*> nameToValueMap = {
        { "button0", &button0 },

        { "acOnTemp", &acOnTemp },
        { "acOffTemp", &acOffTemp },
        { "hvacFan", &hvacFan },
        { "hvacLevel", &hvacLevel },
        { "acEnable", &acEnable },
    };
};