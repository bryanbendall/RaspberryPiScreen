#pragma once

#include "BrytecConfigEmbedded/Usb/UsbDefs.h"
#include <asio.hpp>
#include <deque>
#include <iostream>
#include <thread>

using asio::ip::tcp;

class DataThread {

public:
    DataThread();
    ~DataThread();
    void run();
    void stop();

private:
    asio::io_context m_io_context;
    asio::io_context m_can_io_context;
    std::thread m_thread;
    bool m_run;
    std::deque<Brytec::UsbPacket> m_txPackets;
};