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
    Vector2 getSize();
    const void* getData();

private:
    void readCamera(const std::string& address);

private:
    bool m_run;
    std::thread m_thread;

    cv::VideoCapture* m_capture = nullptr;
    std::mutex m_frameMutex;
    uint8_t m_writeFrameIndex = 0;
    cv::Mat m_frame[2];
};