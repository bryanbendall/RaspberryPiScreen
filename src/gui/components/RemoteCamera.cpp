#include "RemoteCamera.h"

#include <chrono>

using namespace std::chrono_literals;

RemoteCamera::RemoteCamera()
{
}

RemoteCamera::~RemoteCamera()
{
    m_run = false;
    if (m_thread.joinable())
        m_thread.join();

    close();
}

void RemoteCamera::open()
{
    m_capture = new cv::VideoCapture("http://192.168.1.26:8080/stream.mjpeg");

    if (m_capture->isOpened()) {
        // std::cout << "Capture is opened" << std::endl;
        cv::Mat& frame = m_frame[m_writeFrameIndex];
        m_capture->read(frame);

        m_size = { (float)frame.size().width, (float)frame.size().height };

        // std::cout << "frame size - " << frame.size().width << " x " << frame.size().height << std::endl;
        // std::cout << "frame channels - " << frame.channels() << " depth - " << frame.depth() << std::endl;

        Image img = GenImageColor(frame.size().width, frame.size().height, WHITE);
        ImageFormat(&img, PIXELFORMAT_UNCOMPRESSED_R8G8B8);
        m_texture = LoadTextureFromImage(img);
        UpdateTexture(m_texture, frame.data);
        UnloadImage(img);

        m_writeFrameIndex += 1;

        m_run = true;
        m_thread = std::thread([this]() {
            readCamera();
        });

    } else {
        std::cout << "Could not open camera!" << std::endl;
    }
}

void RemoteCamera::close()
{
    m_capture->release();
    delete m_capture;
}

void RemoteCamera::updateTexture()
{
    if (!m_capture->isOpened())
        return;

    m_frameMutex.lock();

    uint8_t readIndex = (m_writeFrameIndex + 1) % 2;
    UpdateTexture(m_texture, m_frame[readIndex].data);

    m_frameMutex.unlock();
}

void RemoteCamera::readCamera()
{
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