#include "CanConnectionHandler.h"

CanConnectionHandler::CanConnectionHandler(asio::io_context& io_context)
    : m_stream(io_service)
{
}

std::shared_ptr<CanConnectionHandler> CanConnectionHandler::create(asio::io_context& io_context)
{
    return std::shared_ptr<CanConnectionHandler>(new CanConnectionHandler(io_service));
}

void CanConnectionHandler::start()
{
    startRead();
}

void CanConnectionHandler::send(const Brytec::CanFrame& frame)
{
    m_txMutex.lock();

    m_txPackets.push_back(packet);

    if (m_txPackets.size() == 1)
        sendBytes();

    m_txMutex.unlock();
}

void CanConnectionHandler::handle_read(const asio::error_code& err)
{
    if (!err) {

        Brytec::CanFrame frame;
        frame.id = m_recieveFrame.can_id;
        frame.dlc = m_recieveFrame.can_dlc;
        memcpy(frame.data, m_recieveFrame.data, 8);

        Brytec::EBrytecApp::canReceived(0, frame);

        startRead();

    } else {
        std::cerr << "error: " << err.message() << std::endl;
        m_socket.close();
    }
}

void CanConnectionHandler::handle_write(const asio::error_code& err)
{
    if (!err) {

        m_txMutex.lock();

        if (m_txFrames.size() > 0)
            sendFrame();

        m_txMutex.unlock();

    } else {
        std::cerr << "error: " << err.message() << std::endl;
        m_socket.close();
    }
}

void CanConnectionHandler::startRead()
{
    m_stream.async_read_some(
        asio::buffer(&rec_frame, sizeof(rec_frame)),
        std::bind(&ConnectionHandler::handle_read,
            shared_from_this(),
            asio::placeholders::error));
}

void CanConnectionHandler::startWrite()
{
    m_stream.async_write_some(
        asio::buffer(&frame, sizeof(frame)),
        std::bind(&ConnectionHandler::handle_write,
            shared_from_this(),
            asio::placeholders::error));
}

void CanConnectionHandler::sendFrame()
{
    if (m_txPackets.size() <= 0) {
        std::cout << "Trying to send a can frame from empty queue" << std::endl;
        return;
    }

    m_sendFrame.can_id = m_txFrames[0].id;
    m_sendFrame.can_dlc = m_txFrames[0].dlc;
    memcpy(m_sendFrame.data, m_txFrames[0].data, 8);

    m_txPackets.pop_front();

    startWrite();
}