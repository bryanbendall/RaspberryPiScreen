#include "CanManager.h"

#include <fmt/format.h>
#include <iostream>

void CanManager::setup(uint8_t index, Brytec::CanSpeed::Types speed)
{
    if (index > MAX_CAN_BUSES) {
        std::cout << "Max can buses exceded!" << std::endl;
        return;
    }

#ifndef PC_BUILD

    if (m_isOpen[index])
        close(index);

    int bitrate;
    switch (speed) {
    case Brytec::CanSpeed::Types::Speed_1MBps:
        bitrate = 1000000;
        break;
    case Brytec::CanSpeed::Types::Speed_500kBps:
        bitrate = 500000;
        break;
    case Brytec::CanSpeed::Types::Speed_250kBps:
        bitrate = 250000;
        break;
    case Brytec::CanSpeed::Types::Speed_200kBps:
        bitrate = 200000;
        break;
    case Brytec::CanSpeed::Types::Speed_125kBps:
        bitrate = 125000;
        break;
    case Brytec::CanSpeed::Types::Speed_100kBps:
        bitrate = 100000;
        break;
    case Brytec::CanSpeed::Types::Speed_50kBps:
        bitrate = 50000;
        break;
    case Brytec::CanSpeed::Types::Speed_20kBps:
        bitrate = 20000;
        break;
    }

    std::string socketName = getSocketName(index);

#if 0
    std::string systemCommand = fmt::format("sudo ip link set {:s} up type can bitrate {:d}", socketName, bitrate);
#else
    std::string systemCommand = fmt::format("sudo ip link set {:s} up", socketName);
#endif
    system(systemCommand.c_str());

    ifreq ifr;
    int natsock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (natsock < 0) {
        std::cout << "Socket creation failed" << std::endl;
        return;
    }

    strcpy(ifr.ifr_name, socketName.c_str());
    if (ioctl(natsock, SIOCGIFINDEX, &ifr) < 0) {
        std::cout << "Error in ioctl" << std::endl;
        return;
    }

    sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(natsock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cout << "Error in socket bind" << std::endl;
        return;
    }

    m_isOpen[index] = true;

    m_handlers[index] = CanConnectionHandler::create(m_io_context, natsock);
    m_handlers[index]->start();

#endif
}

void CanManager::close(uint8_t index)
{
    m_handlers[index].reset();

    std::string socketName = getSocketName(index);
    std::string systemCommand = fmt::format("sudo ip link set {:s} down", socketName);
}

void CanManager::send(uint8_t index, const Brytec::CanFrame& frame)
{
    if (index > MAX_CAN_BUSES) {
        std::cout << "Max can buses exceded!" << std::endl;
        return;
    }

    if (!m_isOpen[index])
        return;

    m_handlers[index]->send(frame);
}

std::string CanManager::getSocketName(uint8_t index)
{
    return fmt::format("vcan{:d}", index);
}

void CanManager::poll()
{
    m_io_context.poll();
}