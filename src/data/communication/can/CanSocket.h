#pragma once

#include "BrytecConfigEmbedded/Can/EBrytecCan.h"
#include "CanConnectionHandler.h"
#include <asio.hpp>

class CanSocket {

public:
    CanSocket(asio::io_context& io_context, std::string socketName);

private:
    asio::io_service& m_io_service;
    bool m_isOpen = false;

public:
    static void send(const Brytec::CanFrame& frame);

private:
    static inline std::weak_ptr<CanConnectionHandler> m_connection;
};