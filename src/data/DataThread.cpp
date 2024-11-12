#include "DataThread.h"

#include "BrytecConfigEmbedded/EBrytecApp.h"
#include "data/communication/Server.h"

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

    while (m_run) {
        m_io_context.poll();
        server.checkConnection();
        Brytec::EBrytecApp::update(10);
        std::this_thread::sleep_for(10ms);
    }
}

void DataThread::stop()
{
    m_run = false;
    if (m_thread.joinable())
        m_thread.join();
}