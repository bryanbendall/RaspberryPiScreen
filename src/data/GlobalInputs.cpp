#include "GlobalInputs.h"

#include "GlobalOutputs.h"
#include <filesystem>
#include <fstream>

static std::filesystem::path s_defaultValuesPath = "../resources/generated/DefaultInputs.yaml";
static std::filesystem::path s_odometerPath = "../resources/generated/Odometer.yaml";

void GlobalInputs::loadDefaultValuesFromFile()
{
    YAML::Node node;

    try {
        node = YAML::LoadFile(s_defaultValuesPath.string());
    } catch (YAML::BadFile) {
        return;
    }

    for (auto v : nameToValueMap) {
        if (node[v.first])
            *v.second = node[v.first].as<float>();
    }
}

void GlobalInputs::loadOdometerFromFile()
{
    YAML::Node node;

    try {
        node = YAML::LoadFile(s_odometerPath.string());
    } catch (YAML::BadFile) {
        return;
    }

    if (node["_odometer"])
        odometer = node["_odometer"].as<double>();
}

void GlobalInputs::saveToFile()
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    for (auto v : nameToValueMap)
        writeVariable(out, v.first, *v.second);

    out << YAML::EndMap;

    if (!std::filesystem::exists(s_defaultValuesPath.parent_path()))
        std::filesystem::create_directories(s_defaultValuesPath.parent_path());

    // Write to file
    std::ofstream fout(s_defaultValuesPath.string());
    fout << out.c_str();
    fout.close();
}

void GlobalInputs::saveOdometerToFile()
{
    YAML::Emitter out;
    out << YAML::BeginMap;

    // Odometer
    out << YAML::Key << "_odometer";
    out << YAML::Value << odometer;

    out << YAML::EndMap;

    if (!std::filesystem::exists(s_odometerPath.parent_path()))
        std::filesystem::create_directories(s_odometerPath.parent_path());

    // Write to file
    std::ofstream fout(s_odometerPath.string());
    fout << out.c_str();
    fout.close();
}

void GlobalInputs::calculateOdometer(uint32_t timestepMs)
{
    static float speed1 = 0.0f;
    static float speed2 = 0.0f;
    static double distanceTravelled = 0.0;
    static uint32_t timeSinceLastSave = 0;

    speed1 = GlobalOutputs::speed;
    timeSinceLastSave += timestepMs;

    // Skip if speed is too low so we don't get rounding errors
    if (speed1 > 1.0f || speed2 > 1.0f) {
        double elapsedHours = (double)timestepMs / 3.6e+6;
        distanceTravelled += ((speed1 + speed2) / 2.0) * elapsedHours;
        if (distanceTravelled > 0.1) {
            odometer += distanceTravelled;
            trip += distanceTravelled;
            distanceTravelled = 0.0;
        }
    }

    // Save every 5 minutes
    if (timeSinceLastSave > 300000) {
        saveOdometerToFile();
        timeSinceLastSave = 0;
    }

    speed2 = speed1;
}

void GlobalInputs::writeVariable(YAML::Emitter& out, std::string key, float value)
{
    out << YAML::Key << key;
    out << YAML::Value << value;
}