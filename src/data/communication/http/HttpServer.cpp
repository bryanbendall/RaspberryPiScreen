#include "HttpServer.h"

#include <iostream>

void HttpServer::startAccept()
{
    std::cout << "Waiting for http connection" << std::endl;

    m_isWaitingForConnection = true;

    std::shared_ptr<HttpConnectionHandler> connection = HttpConnectionHandler::create(m_io_context);
    m_connection = connection;

    m_acceptor.async_accept(connection->socket(),
        std::bind(&HttpServer::handleAccept, this, connection,
            asio::placeholders::error));
}

HttpServer::HttpServer(asio::io_context& io_context)
    : m_io_context(io_context)
    , m_acceptor(io_context, tcp::endpoint(tcp::v4(), 80))
{
    startAccept();
}

void HttpServer::handleAccept(std::shared_ptr<HttpConnectionHandler> connection, const asio::error_code& err)
{
    m_isWaitingForConnection = false;

    if (!err) {
        std::cout << "Http Connected" << std::endl;
        connection->start();
    } else {
        std::cout << err.message() << std::endl;
    }
}

void HttpServer::checkConnection()
{
    if (m_isWaitingForConnection)
        return;

    if (!isConnected())
        startAccept();
}

bool HttpServer::isConnected()
{
    auto connection = m_connection.lock();
    return (bool)connection;
}
