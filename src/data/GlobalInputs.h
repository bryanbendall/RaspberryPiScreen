#pragma once

#include <map>
#include <string>

struct GlobalInputs {

    static inline float acOnTemp = 45.0f;
    static inline float acOffTemp = 40.0f;
    static inline float hvacFan = 0.0f;
    static inline float hvacLevel = 0.0f;
    static inline float acEnable = 0.0f;

    static inline float maxBoost = 0.0f;
    static inline float methEnable = 0.0f;

    static inline float primeGas = 0.0f;
    static inline float primeMeth = 0.0f;

    static inline const std::map<std::string, float*> nameToValueMap = {
        { "acOnTemp", &acOnTemp },
        { "acOffTemp", &acOffTemp },
        { "hvacFan", &hvacFan },
        { "hvacLevel", &hvacLevel },
        { "acEnable", &acEnable },

        { "maxBoost", &maxBoost },
        { "methEnable", &methEnable },

        { "primeGas", &primeGas },
        { "primeMeth", &primeMeth },
    };
};