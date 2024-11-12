#include "Server.h"

#include "BrytecConfigEmbedded/EBrytecConfig.h"
#include <iostream>

void Server::startAccept()
{
    std::cout << "Waiting for connection" << std::endl;

    m_isWaitingForConnection = true;

    std::shared_ptr<ConnectionHandler> connection = ConnectionHandler::create(m_io_service);
    m_connection = connection;

    m_acceptor.async_accept(connection->socket(),
        std::bind(&Server::handleAccept, this, connection,
            asio::placeholders::error));
}

Server::Server(asio::io_service& io_service)
    : m_io_service(io_service)
    , m_acceptor(io_service, tcp::endpoint(tcp::v4(), BRYTEC_NETWORK_PORT))
{
    startAccept();
}

void Server::handleAccept(std::shared_ptr<ConnectionHandler> connection, const asio::error_code& err)
{
    m_isWaitingForConnection = false;

    if (!err) {
        std::cout << "Connected" << std::endl;
        connection->start();
    } else {
        std::cout << err.message() << std::endl;
    }
}

void Server::checkConnection()
{
    if (m_isWaitingForConnection)
        return;

    if (!isConnected())
        startAccept();
}

bool Server::isConnected()
{
    auto connection = m_connection.lock();
    return (bool)connection;
}

void Server::send(const Brytec::UsbPacket& packet)
{
    if (m_isWaitingForConnection)
        return;

    if (auto connection = m_connection.lock())
        connection->send(packet);
}