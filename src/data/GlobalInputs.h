#pragma once

#include <map>
#include <string>

struct GlobalInputs {

    static inline float button0;

    static inline const std::map<std::string, float*> nameToValueMap = {
        { "button0", &button0 }
    };

    // Webpage
    static inline bool openCamera = false;
    static inline std::string cameraAddress;
};