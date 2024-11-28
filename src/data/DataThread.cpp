#include "DataThread.h"

#include "BrytecConfigEmbedded/EBrytecApp.h"
#include "data/communication/wifi/Server.h"

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
    Brytec::EBrytecApp::initalize();
    Server server(m_io_context);

    uint8_t count = 0;

    while (m_run) {
        m_io_context.poll();
        server.checkConnection();

        if (count >= 10) {
            Brytec::EBrytecApp::update(10);
            count = 0;
        } else {
            Brytec::EBrytecApp::processCanCommands();
        }

        std::this_thread::sleep_for(1ms);
        count++;
    }
}

void DataThread::stop()
{
    m_run = false;
    if (m_thread.joinable())
        m_thread.join();
}