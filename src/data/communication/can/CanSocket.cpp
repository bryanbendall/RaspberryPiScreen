#include "CanSocket.h"

#include <iostream>

CanSocket::CanSocket(asio::io_context& io_context, std::string socketName)
{
    struct ifreq ifr;
    int natsock = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    strcpy(ifr.ifr_name, socketName.c_str());
    ioctl(natsock, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(natsock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cout << "Error in socket bind" std::endl;
        return;
    }

    m_isOpen = true;

    std::shared_ptr<CanConnectionHandler> connection = CanConnectionHandler::create(m_io_service);
    m_connection = connection;
    connection->start();
}

void CanSocket::send(const Brytec::CanFrame& frame)
{
    if (auto connection = m_connection.lock())
        connection->send(frame);
}