#pragma once

#include "data/communication/http/HttpConnectionHandler.h"
#include <asio.hpp>

using asio::ip::tcp;

class HttpServer {

public:
    HttpServer(asio::io_context& io_context);
    void handleAccept(std::shared_ptr<HttpConnectionHandler> connection, const asio::error_code& err);
    void checkConnection();
    bool isConnected();

private:
    void startAccept();

private:
    asio::io_context& m_io_context;
    tcp::acceptor m_acceptor;

private:
    static inline bool m_isWaitingForConnection = false;
    static inline std::weak_ptr<HttpConnectionHandler> m_connection;
};