#pragma once

#include "BrytecConfigEmbedded/Usb/UsbDefs.h"
#include <asio.hpp>
#include <deque>
#include <memory>
#include <mutex>

using asio::ip::tcp;

class ConnectionHandler : public std::enable_shared_from_this<ConnectionHandler> {

public:
    ConnectionHandler(asio::io_service& io_service);
    static std::shared_ptr<ConnectionHandler> create(asio::io_service& io_service);
    tcp::socket& socket() { return m_socket; }
    void start();
    void send(const Brytec::UsbPacket& packet);

private:
    void handle_read(const asio::error_code& err, size_t bytes_transferred);
    void handle_write(const asio::error_code& err, size_t bytes_transferred);
    void startRead();
    void startWrite();
    void sendBytes();

private:
    tcp::socket m_socket;
    char m_readBuffer[1024];
    std::vector<uint8_t> m_readData;
    uint8_t m_writeBuffer[64];
    std::mutex m_txMutex;
    std::deque<Brytec::UsbPacket> m_txPackets;
};