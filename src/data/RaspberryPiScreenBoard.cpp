#include "Boards/BrytecBoard.h"

#include "BrytecConfigEmbedded/EBrytecApp.h"
#include "Deserializer/BinaryArrayDeserializer.h"
#include "Deserializer/BinaryPathDeserializer.h"
#include "data/GlobalInputs.h"
#include "data/GlobalOutputs.h"
#include "data/Gpio.h"
#include "data/communication/can/CanManager.h"
#include "data/communication/wifi/Server.h"
#include "data/screenboardrev2defs.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

namespace Brytec {

uint32_t configRequestedSize = 0;
std::vector<uint8_t> tempConfig;

std::filesystem::path configPath("BrytecConfig.btcfg");
BinaryPathDeserializer pathDeserializer(configPath);

static std::map<uint16_t, float*> outputIndexToValueMap;
static std::map<uint16_t, float*> inputIndexToValueMap;

BinaryDeserializer* BrytecBoard::getDeserializer()
{
    GlobalOutputs::setToDefaults();
    outputIndexToValueMap.clear();
    inputIndexToValueMap.clear();

    if (std::filesystem::exists(configPath)) {
        // Get newest from file
        pathDeserializer = BinaryPathDeserializer(configPath);
        return &pathDeserializer;
    }

    return nullptr;
}

void BrytecBoard::error(EBrytecErrors error)
{
    switch (error) {
    case EBrytecErrors::ModuleHeader:
        std::cout << "Module header is wrong" << std::endl;
        break;
    case EBrytecErrors::NodeGroupHeader:
        std::cout << "Node Group header is wrong" << std::endl;
        break;
    case EBrytecErrors::ModuleNotEnabled:
        std::cout << "This module is not enabled" << std::endl;
        break;
    case EBrytecErrors::AddNodeFailed:
        std::cout << "Failed to add node" << std::endl;
        break;
    case EBrytecErrors::NodeVectorOutOfSpace:
        std::cout << "Node Vector out of space" << std::endl;
        break;
    case EBrytecErrors::FailedToCreateNode:
        std::cout << "Failed to create node" << std::endl;
        break;
    case EBrytecErrors::NodeIndexOutOfBounds:
        std::cout << "Node index out of bounds" << std::endl;
        break;
    case EBrytecErrors::BadAlloc:
        std::cout << "Node group allocation failed" << std::endl;
        break;
    case EBrytecErrors::CanBufferFull:
        std::cout << "Can Buffer Full" << std::endl;
        break;

    default:
        std::cout << "Unknown Error" << std::endl;
        break;
    }
}

void BrytecBoard::setupCan(uint8_t index, CanSpeed::Types speed)
{
    CanManager::setup(index, speed);
}

void BrytecBoard::setupPin(uint16_t index, IOTypes::Types type)
{
    // Not used
}

void BrytecBoard::shutdownAllPins()
{
    GlobalOutputs::setToDefaults();
}

float BrytecBoard::getPinValue(uint16_t index, IOTypes::Types type)
{
    if (inputIndexToValueMap.find(index) != inputIndexToValueMap.end())
        return *inputIndexToValueMap[index];

    // Pin is not a named value
    return 0.0f;
}

float BrytecBoard::getPinVoltage(uint16_t index)
{
    // Not used
    return 0.0f;
}

float BrytecBoard::getPinCurrent(uint16_t index)
{
    // Not used
    return 0.0f;
}

void BrytecBoard::setPinValue(uint16_t index, IOTypes::Types type, float value)
{
    if (outputIndexToValueMap.find(index) != outputIndexToValueMap.end()) {
        *outputIndexToValueMap[index] = value;
    } else {
        // Pin is not a named value
    }
}

void BrytecBoard::sendCan(uint8_t index, const CanFrame& frame)
{
    CanManager::send(index, frame);
}

void BrytecBoard::sendBrytecCanUsb(const CanFrame& frame)
{
    UsbPacket packet;
    packet.set(frame);
    Server::send(packet);
}

void BrytecBoard::ReserveConfigSize(uint16_t size)
{
    configRequestedSize = size;
    tempConfig.reserve(size);
}

void BrytecBoard::updateConfig(uint8_t* data, uint32_t size, uint32_t offset)
{
    tempConfig.insert(tempConfig.begin() + offset, data, data + size);

    if (size + offset >= configRequestedSize) {
        // Write to file
        std::cout << "Writing brytec config to file" << std::endl;
        std::ofstream fout(configPath, std::ofstream::binary);
        fout.write((char*)tempConfig.data(), tempConfig.size());
        tempConfig.clear();
    }
}

uint32_t BrytecBoard::getTemplateSize()
{
    return sizeof(moduleTemplate);
}

void BrytecBoard::getTemplateData(uint8_t* dest, uint32_t offset, uint32_t length)
{
    if (offset > sizeof(moduleTemplate))
        return;

    memcpy(dest, &moduleTemplate[offset], length);
}

uint32_t BrytecBoard::getConfigSize()
{
    return pathDeserializer.getTotalLength();
}

void BrytecBoard::getConfigData(uint8_t* dest, uint32_t offset, uint32_t length)
{
    pathDeserializer.getRawData(dest, offset, length);
}

void BrytecBoard::AddedNamesNodeGroup(uint16_t index, std::string ngName)
{
    {
        auto it = GlobalOutputs::nameToValueMap.find(ngName);
        if (it != GlobalOutputs::nameToValueMap.end())
            outputIndexToValueMap[index] = it->second;
    }

    {
        auto it = GlobalInputs::nameToValueMap.find(ngName);
        if (it != GlobalInputs::nameToValueMap.end())
            inputIndexToValueMap[index] = it->second;
    }
}
}