#pragma once

#include <stdint.h>

struct GlobalVariables {

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
    static inline float reverse;
    static inline float showGear;
    static inline float parkingBrake;

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

    static void setToDefaults()
    {
        rpm = 0.0f;
        afr = 0.0f;
        afr2 = 0.0f;
        showSecondAfr = 0.0f;
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
        showOdometer = 1.0f;
        overDrive = 0.0f;
        parkNeutral = 0.0f;
        fanState = 0.0f;
        leftTurn = 0.0f;
        rightTurn = 0.0f;
        parkingLights = 0.0f;
        lowBeam = 0.0f;
        highBeam = 0.0f;
        reverse = 0.0f;
        showGear = 1.0f;
        parkingBrake = 0.0f;

        guageColor = 1216765.0f; // orange
    }
};