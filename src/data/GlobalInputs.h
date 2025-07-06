#pragma once

#include <map>
#include <string>
#include <yaml-cpp/yaml.h>

struct GlobalInputs {

    static inline std::map<std::string, float> values;

    static inline float guageRightPanel = 0.0f;

    // Distance variables
    static inline double odometer = 0.0f;
    static inline double trip = 0.0f;

    static void loadDefaultValuesFromFile();
    static void loadOdometerFromFile();
    static void saveToFile();
    static void saveOdometerToFile();

    static void calculateOdometer(uint32_t timestepMs);

private:
    static void writeVariable(YAML::Emitter& out, std::string key, float value);
};