#pragma once

#include "BrytecConfigEmbedded/Can/EBrytecCan.h"
#include <asio.hpp>
#include <deque>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <memory>
#include <mutex>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>

class CanConnectionHandler : public std::enable_shared_from_this<CanConnectionHandler> {

public:
    CanConnectionHandler(asio::io_context& io_context);
    static std::shared_ptr<CanConnectionHandler> create(asio::io_context& io_context);
    void start();
    void send(const Brytec::CanFrame& frame);

private:
    void handle_read(const asio::error_code& err);
    void handle_write(const asio::error_code& err);
    void startRead();
    void startWrite();
    void sendFrame();

private:
    asio::posix::basic_stream_descriptor<> m_stream;
    struct can_frame m_sendFrame;
    struct can_frame m_recieveFrame;
    std::mutex m_txMutex;
    std::deque<Brytec::CanFrame> m_txFrames;
};