#include "CameraController.h"

CameraController::CameraController()
{
    m_instance = this;
}

CameraController::~CameraController()
{
}

RemoteCamera& CameraController::getCamera(std::string address)
{
    for (auto& cameraHandle : m_cameras) {
        if (cameraHandle.first == address)
            return cameraHandle.second;
    }

    // Create camera
    return m_cameras[address];
}