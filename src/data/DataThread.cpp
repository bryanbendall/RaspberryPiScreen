#include "DataThread.h"

#include "BrytecConfigEmbedded/EBrytecApp.h"
#include "data/GlobalInputs.h"
#include "data/ScreenControl.h"
#include "data/communication/can/CanManager.h"
#include "data/communication/http/HttpServer.h"
#include "data/communication/wifi/Server.h"
#include <chrono>

extern bool s_programming;

using namespace std::chrono_literals;

DataThread::DataThread()
{
    m_run = true;
    m_thread = std::thread([this]() {
        run();
    });
}

DataThread::~DataThread()
{
    stop();
}

void DataThread::run()
{
    GlobalInputs::loadDefaultValuesFromFile();
    GlobalInputs::loadOdometerFromFile();
    Brytec::EBrytecApp::initalize();
    Server server(m_io_context);
    HttpServer httpServer(m_io_context);
    ScreenControl screenControl;

    std::chrono::steady_clock::time_point lastUpdate = std::chrono::steady_clock::now();

    while (m_run) {
        m_io_context.poll();
        CanManager::poll();
        server.checkConnection();
        httpServer.checkConnection();

        auto now = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count();

        if (deltaTime >= 10.0f) {
            Brytec::EBrytecApp::update((uint32_t)deltaTime);
            screenControl.update();
            lastUpdate = now;
        } else {
            Brytec::EBrytecApp::processCanCommands();
        }

        if (!s_programming)
            std::this_thread::sleep_for(1ms);
    }

    GlobalInputs::saveOdometerToFile();
}

void DataThread::stop()
{
    m_run = false;
    if (m_thread.joinable())
        m_thread.join();
}