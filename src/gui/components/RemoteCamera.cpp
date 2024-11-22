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

    if (IsTextureReady(m_texture))
        UnloadTexture(m_texture);

    m_cameraFound = false;
    m_initalFrameRead = false;
    m_textureInitialized = false;
    m_size = { 0.0f, 0.0f };
}

bool RemoteCamera::isOpen()
{
    if (m_capture)
        return m_run && m_capture->isOpened();

    return false;
}

void RemoteCamera::updateTexture()
{
    if (m_cameraFound && m_capture && !m_capture->isOpened())
        return;

    setupTexture();

    if (!m_textureInitialized)
        return;

    m_frameMutex.lock();

    uint8_t readIndex = (m_writeFrameIndex + 1) % 2;
    UpdateTexture(m_texture, m_frame[readIndex].data);

    m_frameMutex.unlock();
}

void RemoteCamera::setupTexture()
{
    if (m_textureInitialized || !m_initalFrameRead)
        return;

    m_frameMutex.lock();

    if (IsTextureReady(m_texture))
        UnloadTexture(m_texture);

    uint8_t readIndex = (m_writeFrameIndex + 1) % 2;
    m_size = { (float)m_frame[readIndex].size().width, (float)m_frame[readIndex].size().height };

    Image img = GenImageColor(m_frame[readIndex].size().width, m_frame[readIndex].size().height, WHITE);
    ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8);
    m_texture = LoadTextureFromImage(img);
    UpdateTexture(m_texture, m_frame[readIndex].data);
    UnloadImage(img);

    m_frameMutex.unlock();

    m_textureInitialized = true;
}

void RemoteCamera::readCamera(const std::string& address)
{
    m_capture = new cv::VideoCapture(address);
    if (!m_capture->isOpened()) {
        std::cout << "Could not find camera" << std::endl;
        return;
    }

    std::cout << "Starting camera" << std::endl;
    m_cameraFound = true;

    while (m_run) {

        if (m_capture->isOpened()) {

            cv::Mat tempFrame;
            m_capture->read(tempFrame);
            cv::cvtColor(tempFrame, m_frame[m_writeFrameIndex], cv::COLOR_BGR2RGB);

            m_frameMutex.lock();

            if (tempFrame.size().width != m_size.x || tempFrame.size().height != m_size.y)
                m_textureInitialized = false;

            m_writeFrameIndex = (m_writeFrameIndex + 1) % 2;

            m_frameMutex.unlock();

            m_initalFrameRead = true;
        }
        std::this_thread::sleep_for(1ms);
    }
}