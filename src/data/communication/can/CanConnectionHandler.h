#pragma once

#include "BrytecConfigEmbedded/Can/EBrytecCan.h"
#include <asio.hpp>
#include <deque>
#include <memory>
#include <mutex>
#include <sys/types.h>

#ifndef PC_BUILD
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#endif

class CanConnectionHandler : public std::enable_shared_from_this<CanConnectionHandler> {

public:
    CanConnectionHandler(asio::io_context& io_context, int natsock);
    static std::shared_ptr<CanConnectionHandler> create(asio::io_context& io_context, int natsock);
    void start();
    void send(const Brytec::CanFrame& frame);

private:
    void handle_read(const asio::error_code& err);
    void handle_write(const asio::error_code& err);
    void startRead();
    void startWrite();
    void sendFrame();

private:
#ifndef PC_BUILD
    asio::posix::basic_stream_descriptor<> m_stream;
    can_frame m_sendFrame;
    can_frame m_recieveFrame;
    std::mutex m_txMutex;
    std::deque<Brytec::CanFrame> m_txFrames;
#endif
};