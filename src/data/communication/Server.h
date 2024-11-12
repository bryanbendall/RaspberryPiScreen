#pragma once

#include "BrytecConfigEmbedded/Usb/UsbDefs.h"
#include "data/communication/ConnectionHandler.h"
#include <asio.hpp>

using asio::ip::tcp;

class Server {

public:
    Server(asio::io_service& io_service);
    void handleAccept(std::shared_ptr<ConnectionHandler> connection, const asio::error_code& err);
    void checkConnection();
    bool isConnected();

private:
    void startAccept();

private:
    asio::io_service& m_io_service;
    tcp::acceptor m_acceptor;

public:
    static void send(const Brytec::UsbPacket& packet);

private:
    static inline bool m_isWaitingForConnection = false;
    static inline std::weak_ptr<ConnectionHandler> m_connection;
};