#pragma once

#include "gui/components/RemoteCamera.h"
#include <map>
#include <string>

class CameraController {

public:
    CameraController();
    ~CameraController();
    static CameraController& get() { return *m_instance; }

    RemoteCamera& getCamera(std::string name);

private:
    static inline CameraController* m_instance = nullptr;
    std::map<std::string, RemoteCamera> m_cameras = {};
};