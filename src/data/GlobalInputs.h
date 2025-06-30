#pragma once

#include <map>
#include <string>
#include <yaml-cpp/yaml.h>

struct GlobalInputs {

    static inline float guageRightPanel = 0.0f;
    static inline float centerScreenPanel = 0.0f;

    static inline float acOnTemp = 45.0f;
    static inline float acOffTemp = 40.0f;
    static inline float hvacFan = 0.0f;
    static inline float hvacLevel = 0.0f;
    static inline float acEnable = 0.0f;

    static inline float baseBoost = 0.0f;
    static inline float maxBoost = 0.0f;
    static inline float methEnable = 0.0f;

    static inline float primeGas = 0.0f;
    static inline float primeMeth = 0.0f;

    static inline float useKph = 0.0f;

    // Distance variables
    static inline double odometer = 0.0f;
    static inline double trip = 0.0f;

    static inline const std::map<std::string, float*> nameToValueMap = {
        { "guageRightPanel", &guageRightPanel },

        { "acOnTemp", &acOnTemp },
        { "acOffTemp", &acOffTemp },
        { "hvacFan", &hvacFan },
        { "hvacLevel", &hvacLevel },
        { "acEnable", &acEnable },

        { "baseBoost", &baseBoost },
        { "maxBoost", &maxBoost },
        { "methEnable", &methEnable },

        { "primeGas", &primeGas },
        { "primeMeth", &primeMeth },

        { "useKph", &useKph },
    };

    static void loadDefaultValuesFromFile();
    static void loadOdometerFromFile();
    static void saveToFile();
    static void saveOdometerToFile();

    static void calculateOdometer(uint32_t timestepMs);

private:
    static void writeVariable(YAML::Emitter& out, std::string key, float value);
};