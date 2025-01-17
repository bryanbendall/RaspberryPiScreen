#include "RemoteCamera.h"

#include <chrono>
#include <opencv2/core/utils/logger.hpp>

using namespace std::chrono_literals;

RemoteCamera::RemoteCamera()
{
}

RemoteCamera::~RemoteCamera()
{
    close();
}

void RemoteCamera::open(const std::string& address)
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    m_run = true;
    m_thread = std::thread([this, address]() {
        readCamera(address);
    });
}

void RemoteCamera::close()
{
    m_run = false;
    if (m_thread.joinable())
        m_thread.join();

    if (m_capture) {
        m_capture->release();
        delete m_capture;
        m_capture = nullptr;
    }
}

bool RemoteCamera::isOpen()
{
    if (m_capture)
        return m_run && m_capture->isOpened();

    return false;
}

Vector2 RemoteCamera::getSize()
{
    uint8_t readIndex = (m_writeFrameIndex + 1) % 2;
    return { (float)m_frame[readIndex].size().width, (float)m_frame[readIndex].size().height };
}

const void* RemoteCamera::getData()
{
    // TODO lock or copy data
    uint8_t readIndex = (m_writeFrameIndex + 1) % 2;
    return m_frame[readIndex].data;
}

void RemoteCamera::readCamera(const std::string& address)
{
    m_capture = new cv::VideoCapture(address);
    if (!m_capture->isOpened()) {
        std::cout << "Could not find camera" << std::endl;
        return;
    }

    std::cout << "Starting camera" << std::endl;

    while (m_run) {

        if (m_capture->isOpened()) {

            cv::Mat tempFrame;
            m_capture->read(tempFrame);
            cv::cvtColor(tempFrame, m_frame[m_writeFrameIndex], cv::COLOR_BGR2RGB);

            m_frameMutex.lock();

            m_writeFrameIndex = (m_writeFrameIndex + 1) % 2;

            m_frameMutex.unlock();
        }
        std::this_thread::sleep_for(1ms);
    }
}