#pragma once

#include <mutex>
#include <opencv2/opencv.hpp>
#include <raylib.h>
#include <thread>

class RemoteCamera {

public:
    RemoteCamera();
    ~RemoteCamera();
    void open(const std::string& address);
    void close();
    bool isOpen();
    void updateTexture();
    Texture2D& getTexture() { return m_texture; }
    const Vector2& getSize() { return m_size; }

private:
    void setupTexture();
    void readCamera(const std::string& address);

private:
    Vector2 m_size;

    bool m_run;
    std::thread m_thread;

    cv::VideoCapture* m_capture = nullptr;
    std::mutex m_frameMutex;
    uint8_t m_writeFrameIndex = 0;
    cv::Mat m_frame[2];

    bool m_cameraFound = false;
    bool m_initalFrameRead = false;
    bool m_textureInitialized = false;
    Texture2D m_texture;
};