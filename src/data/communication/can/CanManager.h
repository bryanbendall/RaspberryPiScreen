#pragma once

#include "BrytecConfigEmbedded/Can/EBrytecCan.h"
#include "BrytecConfigEmbedded/Can/ECanBus.h"
#include "BrytecConfigEmbedded/EBrytecConfig.h"
#include "CanConnectionHandler.h"
#include <asio.hpp>

class CanManager {

public:
    static void setup(uint8_t index, Brytec::CanSpeed::Types speed);
    static void close(uint8_t index);
    static void send(uint8_t index, const Brytec::CanFrame& frame);
    static std::string getSocketName(uint8_t index);
    static void poll();

private:
    static inline asio::io_context m_io_context;
    static inline std::shared_ptr<CanConnectionHandler> m_handlers[MAX_CAN_BUSES];
    static inline bool m_isOpen[MAX_CAN_BUSES] = { false };
};