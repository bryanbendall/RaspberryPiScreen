#include "CanConnectionHandler.h"

#include <BrytecConfigEmbedded/EBrytecApp.h>
#include <iostream>

CanConnectionHandler::CanConnectionHandler(asio::io_context& io_context, int natsock, uint8_t canIndex)
    : m_canIndex(canIndex)
#ifndef PC_BUILD
    , m_stream(io_context)
#endif
{
#ifndef PC_BUILD
    m_stream.assign(natsock);
#endif
}

std::shared_ptr<CanConnectionHandler> CanConnectionHandler::create(asio::io_context& io_context, int natsock, uint8_t canIndex)
{
    return std::shared_ptr<CanConnectionHandler>(new CanConnectionHandler(io_context, natsock, canIndex));
}

void CanConnectionHandler::start()
{
    startRead();
}

void CanConnectionHandler::send(const Brytec::CanFrame& frame)
{
#ifndef PC_BUILD
    m_txMutex.lock();

    m_txFrames.push_back(frame);

    if (m_txFrames.size() == 1)
        sendFrame();

    m_txMutex.unlock();
#endif
}

void CanConnectionHandler::handle_read(const asio::error_code& err)
{
#ifndef PC_BUILD
    if (!err) {

        Brytec::CanFrame frame;

        if (m_recieveFrame.can_id & CAN_EFF_FLAG) {
            frame.type = Brytec::CanFrameType::Ext;
            frame.id = m_recieveFrame.can_id & CAN_EFF_MASK;
        } else {
            frame.type = Brytec::CanFrameType::Std;
            frame.id = m_recieveFrame.can_id & CAN_SFF_MASK;
        }

        frame.dlc = m_recieveFrame.len;
        memcpy(frame.data, m_recieveFrame.data, 8);

        Brytec::EBrytecApp::canReceived(m_canIndex, frame);

        startRead();

    } else {
        std::cerr << "error: " << err.message() << std::endl;
        m_stream.close();
    }
#endif
}

void CanConnectionHandler::handle_write(const asio::error_code& err)
{
#ifndef PC_BUILD
    if (!err) {

        m_txMutex.lock();

        if (m_txFrames.size() > 0)
            sendFrame();

        m_txMutex.unlock();

    } else {
        std::cerr << "error: " << err.message() << std::endl;
        m_stream.close();
    }
#endif
}

void CanConnectionHandler::startRead()
{
#ifndef PC_BUILD
    m_stream.async_read_some(
        asio::buffer(&m_recieveFrame, sizeof(m_recieveFrame)),
        std::bind(&CanConnectionHandler::handle_read,
            shared_from_this(),
            asio::placeholders::error));
#endif
}

void CanConnectionHandler::startWrite()
{
#ifndef PC_BUILD
    m_stream.async_write_some(
        asio::buffer(&m_sendFrame, sizeof(m_sendFrame)),
        std::bind(&CanConnectionHandler::handle_write,
            shared_from_this(),
            asio::placeholders::error));
#endif
}

void CanConnectionHandler::sendFrame()
{
#ifndef PC_BUILD
    if (m_txFrames.size() <= 0) {
        std::cout << "Trying to send a can frame from empty queue" << std::endl;
        return;
    }

    if (m_txFrames[0].type == Brytec::CanFrameType::Ext) {
        m_sendFrame.can_id = m_txFrames[0].id & CAN_EFF_MASK;
        m_sendFrame.can_id |= CAN_EFF_FLAG;
    } else {
        m_sendFrame.can_id = m_txFrames[0].id & CAN_SFF_MASK;
    }

    m_sendFrame.len = m_txFrames[0].dlc;
    memcpy(m_sendFrame.data, m_txFrames[0].data, 8);

    m_txFrames.pop_front();

    startWrite();
#endif
}