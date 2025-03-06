#pragma once

#include <map>
#include <stdint.h>
#include <string>

struct GlobalOutputs {

    static inline float rpm;
    static inline float afr;
    static inline float afr2;
    static inline float showSecondAfr;
    static inline float boost;
    static inline float gasLevel;
    static inline float methLevel;
    static inline float gear;
    static inline float cts;
    static inline float oilPressure;
    static inline float battery;
    static inline float lineTemp;
    static inline float fuelPressure;
    static inline float methPressure;
    static inline float speed;
    static inline float useKph;
    static inline float closedLoopComp;
    static inline float showOdometer;
    static inline float overDrive;
    static inline float parkNeutral;
    static inline float fanState;
    static inline float leftTurn;
    static inline float rightTurn;
    static inline float parkingLights;
    static inline float lowBeam;
    static inline float highBeam;
    static inline float fogLights;
    static inline float reverse;
    static inline float showGear;
    static inline float parkingBrake;
    static inline float revLimit;
    static inline float engineLight;

    static inline float acPress;
    static inline float ventTemp;
    static inline float acClutchStatus;

    static inline float screen1;
    static inline float screen2;

    // Variable colors
    static inline float guageColor;

    // Constant colors
    static inline uint32_t white = 0xE5E5E5FF;
    static inline uint32_t red = 0xB3272EFF;
    static inline uint32_t orange = 0xFD9012FF;
    static inline uint32_t gray = 0x817C83FF;
    static inline uint32_t green = 0x5ADA17FF;
    static inline uint32_t blue = 0x146AA1FF;
    static inline uint32_t black = 0x000000FF;

    static inline const std::map<std::string, float*> nameToValueMap = {
        { "rpm", &rpm },
        { "afr", &afr },
        { "afr2", &afr2 },
        { "showSecondAfr", &showSecondAfr },
        { "boost", &boost },
        { "gasLevel", &gasLevel },
        { "methLevel", &methLevel },
        { "gear", &gear },
        { "cts", &cts },
        { "oilPressure", &oilPressure },
        { "battery", &battery },
        { "lineTemp", &lineTemp },
        { "fuelPressure", &fuelPressure },
        { "methPressure", &methPressure },
        { "speed", &speed },
        { "useKph", &useKph },
        { "closedLoopComp", &closedLoopComp },
        { "fanState", &fanState },
        { "leftTurn", &leftTurn },
        { "rightTurn", &rightTurn },
        { "parkingLights", &parkingLights },
        { "lowBeam", &lowBeam },
        { "highBeam", &highBeam },
        { "fogLights", &fogLights },
        { "parkingBrake", &parkingBrake },
        { "revLimit", &revLimit },
        { "engineLight", &engineLight },

        { "acPress", &acPress },
        { "ventTemp", &ventTemp },
        { "acClutchStatus", &acClutchStatus },

        { "screen1", &screen1 },
        { "screen2", &screen2 },

        { "guageColor", &guageColor },

    };

    static void setToDefaults()
    {
        rpm = 0.0f;
        afr = 0.0f;
        afr2 = 0.0f;
        showSecondAfr = 1.0f;
        boost = 0.0f;
        gasLevel = 0.0f;
        methLevel = 0.0f;
        gear = 0.0f;
        cts = 0.0f;
        oilPressure = 0.0f;
        battery = 0.0f;
        lineTemp = 0.0f;
        fuelPressure = 0.0f;
        methPressure = 0.0f;
        speed = 0.0f;
        useKph = 0.0f;
        closedLoopComp = 0.0f;
        fanState = 0.0f;
        leftTurn = 0.0f;
        rightTurn = 0.0f;
        parkingLights = 0.0f;
        lowBeam = 0.0f;
        highBeam = 0.0f;
        fogLights = 0.0f;
        parkingBrake = 0.0f;
        revLimit = 8000.0f;
        engineLight = 0.0f;

        acPress = 0.0f;
        ventTemp = 0.0f;
        acClutchStatus = 0.0f;

        screen1 = 1.0f;
        screen2 = 1.0f;

        guageColor = 1216765.0f; // orange
    }
};