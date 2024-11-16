#pragma once

#include <mutex>
#include <opencv2/opencv.hpp>
#include <raylib.h>
#include <thread>

class RemoteCamera {

public:
    RemoteCamera();
    ~RemoteCamera();
    void open();
    void close();
    bool isOpen() { return m_capture->isOpened(); }
    void updateTexture();
    Texture2D& getTexture() { return m_texture; }
    const Vector2& getSize() { return m_size; }

private:
    void readCamera();

private:
    Vector2 m_size;
    bool m_run;
    std::thread m_thread;
    cv::VideoCapture* m_capture;
    std::mutex m_frameMutex;
    uint8_t m_writeFrameIndex = 0;
    cv::Mat m_frame[2];
    Texture2D m_texture;
};