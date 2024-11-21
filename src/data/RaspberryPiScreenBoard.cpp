#include "Boards/BrytecBoard.h"

#include "BrytecConfigEmbedded/EBrytecApp.h"
#include "Deserializer/BinaryArrayDeserializer.h"
#include "Deserializer/BinaryPathDeserializer.h"
#include "data/GlobalVariables.h"
#include "data/communication/Server.h"
#include "data/screenboarddefs.h"
#include "data/screeninternaldefs.h"
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

static const std::map<std::string, float*> nameToValueMap = {

    { "rpm", &GlobalVariables::rpm },
    { "afr", &GlobalVariables::afr },
    { "afr2", &GlobalVariables::afr2 },
    { "showSecondAfr", &GlobalVariables::showSecondAfr },
    { "boost", &GlobalVariables::boost },
    { "gasLevel", &GlobalVariables::gasLevel },
    { "methLevel", &GlobalVariables::methLevel },
    { "gear", &GlobalVariables::gear },
    { "cts", &GlobalVariables::cts },
    { "oilPressure", &GlobalVariables::oilPressure },
    { "battery", &GlobalVariables::battery },
    { "lineTemp", &GlobalVariables::lineTemp },
    { "fuelPressure", &GlobalVariables::fuelPressure },
    { "methPressure", &GlobalVariables::methPressure },
    { "speed", &GlobalVariables::speed },
    { "useKph", &GlobalVariables::useKph },
    { "closedLoopComp", &GlobalVariables::closedLoopComp },
    { "showOdometer", &GlobalVariables::showOdometer },
    { "overDrive", &GlobalVariables::overDrive },
    { "parkNeutral", &GlobalVariables::parkNeutral },
    { "fanState", &GlobalVariables::fanState },
    { "leftTurn", &GlobalVariables::leftTurn },
    { "rightTurn", &GlobalVariables::rightTurn },
    { "parkingLights", &GlobalVariables::parkingLights },
    { "lowBeam", &GlobalVariables::lowBeam },
    { "highBeam", &GlobalVariables::highBeam },
    { "reverse", &GlobalVariables::reverse },
    { "showGear", &GlobalVariables::showGear },
    { "parkingBrake", &GlobalVariables::parkingBrake },
    { "revLimit", &GlobalVariables::revLimit },

    { "guageColor", &GlobalVariables::guageColor },

};

static std::map<uint16_t, float*> indexToValueMap;

BinaryDeserializer* BrytecBoard::getDeserializer()
{
    GlobalVariables::setToDefaults();
    indexToValueMap.clear();

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
    // TODO
}

void BrytecBoard::setupPin(uint16_t index, IOTypes::Types type)
{
    // Not used
}

void BrytecBoard::shutdownAllPins()
{
    GlobalVariables::setToDefaults();
}

float BrytecBoard::getPinValue(uint16_t index, IOTypes::Types type)
{
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
    if (indexToValueMap.find(index) != indexToValueMap.end()) {
        *indexToValueMap[index] = value;
    } else {
        // Pin is not a named value
    }
}

void BrytecBoard::sendCan(uint8_t index, const CanFrame& frame)
{
    // TODO
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
    auto it = nameToValueMap.find(ngName);
    if (it != nameToValueMap.end())
        indexToValueMap[index] = it->second;
}
}