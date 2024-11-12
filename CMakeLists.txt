cmake_minimum_required(VERSION 3.10)

project(RaspberryPiScreen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# ///////////////////////////////
if (UNIX)

set(PLATFORM SDL)
set(OPENGL_VERSION "ES 2.0")

endif (UNIX)
# ///////////////////////////////

add_executable(${PROJECT_NAME}
                src/BrytecConfigEmbedded/Boards/BrytecBoard.h
                src/BrytecConfigEmbedded/Can/EBrytecCan.h
                src/BrytecConfigEmbedded/Can/EBrytecCan.cpp
                src/BrytecConfigEmbedded/Can/ECanBus.h
                src/BrytecConfigEmbedded/Can/ECanBus.cpp
                src/BrytecConfigEmbedded/Can/EPinStatusQueue.cpp
                src/BrytecConfigEmbedded/Can/EPinStatusQueue.h
                src/BrytecConfigEmbedded/Can/ECanCommandQueue.cpp
                src/BrytecConfigEmbedded/Can/ECanCommandQueue.h
                src/BrytecConfigEmbedded/Can/ECanHolleyBroadcastQueue.cpp
                src/BrytecConfigEmbedded/Can/ECanHolleyBroadcastQueue.h
                src/BrytecConfigEmbedded/Can/ECustomCanQueue.cpp
                src/BrytecConfigEmbedded/Can/ECustomCanQueue.h
                src/BrytecConfigEmbedded/Deserializer/BinaryArrayDeserializer.cpp
                src/BrytecConfigEmbedded/Deserializer/BinaryArrayDeserializer.h
                src/BrytecConfigEmbedded/Deserializer/BinaryDeserializer.h
                src/BrytecConfigEmbedded/Deserializer/BinaryBufferSerializer.cpp
                src/BrytecConfigEmbedded/Deserializer/BinaryBufferSerializer.h
                src/BrytecConfigEmbedded/Deserializer/BinaryPathDeserializer.cpp
                src/BrytecConfigEmbedded/Deserializer/BinaryPathDeserializer.h
                src/BrytecConfigEmbedded/Nodes/EAndNode.cpp
                src/BrytecConfigEmbedded/Nodes/EAndNode.h
                src/BrytecConfigEmbedded/Nodes/ECanBusInputNode.cpp
                src/BrytecConfigEmbedded/Nodes/ECanBusInputNode.h
                src/BrytecConfigEmbedded/Nodes/ECanBusOutputNode.cpp
                src/BrytecConfigEmbedded/Nodes/ECanBusOutputNode.h
                src/BrytecConfigEmbedded/Nodes/EColorNode.cpp
                src/BrytecConfigEmbedded/Nodes/EColorNode.h
                src/BrytecConfigEmbedded/Nodes/ECompareNode.cpp
                src/BrytecConfigEmbedded/Nodes/ECompareNode.h                
                src/BrytecConfigEmbedded/Nodes/EConvertNode.cpp
                src/BrytecConfigEmbedded/Nodes/EConvertNode.h
                src/BrytecConfigEmbedded/Nodes/ECounterNode.cpp
                src/BrytecConfigEmbedded/Nodes/ECounterNode.h
                src/BrytecConfigEmbedded/Nodes/ECurveNode.cpp
                src/BrytecConfigEmbedded/Nodes/ECurveNode.h
                src/BrytecConfigEmbedded/Nodes/EInterpolateNode.cpp
                src/BrytecConfigEmbedded/Nodes/EInterpolateNode.h
                src/BrytecConfigEmbedded/Nodes/EDelayNode.cpp
                src/BrytecConfigEmbedded/Nodes/EDelayNode.h
                src/BrytecConfigEmbedded/Nodes/EFinalValueNode.cpp
                src/BrytecConfigEmbedded/Nodes/EFinalValueNode.h
                src/BrytecConfigEmbedded/Nodes/EHolleyBroadcastNode.cpp
                src/BrytecConfigEmbedded/Nodes/EHolleyBroadcastNode.h
                src/BrytecConfigEmbedded/Nodes/EInitialValueNode.cpp
                src/BrytecConfigEmbedded/Nodes/EInitialValueNode.h
                src/BrytecConfigEmbedded/Nodes/EInvertNode.cpp
                src/BrytecConfigEmbedded/Nodes/EInvertNode.h
                src/BrytecConfigEmbedded/Nodes/EMapValueNode.cpp
                src/BrytecConfigEmbedded/Nodes/EMapValueNode.h
                src/BrytecConfigEmbedded/Nodes/EMathNode.cpp
                src/BrytecConfigEmbedded/Nodes/EMathNode.h
                src/BrytecConfigEmbedded/Nodes/ENodeGroupNode.cpp
                src/BrytecConfigEmbedded/Nodes/ENodeGroupNode.h
                src/BrytecConfigEmbedded/Nodes/EOnOffNode.cpp
                src/BrytecConfigEmbedded/Nodes/EOnOffNode.h
                src/BrytecConfigEmbedded/Nodes/EOrNode.cpp
                src/BrytecConfigEmbedded/Nodes/EOrNode.h
                src/BrytecConfigEmbedded/Nodes/EPIDNode.cpp
                src/BrytecConfigEmbedded/Nodes/EPIDNode.h
                src/BrytecConfigEmbedded/Nodes/EPinCurrentNode.cpp
                src/BrytecConfigEmbedded/Nodes/EPinCurrentNode.h
                src/BrytecConfigEmbedded/Nodes/EPushButtonNode.cpp
                src/BrytecConfigEmbedded/Nodes/EPushButtonNode.h
                src/BrytecConfigEmbedded/Nodes/ERacepakSwitchPanelNode.cpp
                src/BrytecConfigEmbedded/Nodes/ERacepakSwitchPanelNode.h
                src/BrytecConfigEmbedded/Nodes/ESwitchNode.cpp
                src/BrytecConfigEmbedded/Nodes/ESwitchNode.h
                src/BrytecConfigEmbedded/Nodes/EToggleNode.cpp
                src/BrytecConfigEmbedded/Nodes/EToggleNode.h
                src/BrytecConfigEmbedded/Nodes/ETwoStageNode.cpp
                src/BrytecConfigEmbedded/Nodes/ETwoStageNode.h
                src/BrytecConfigEmbedded/Nodes/EValueNode.cpp
                src/BrytecConfigEmbedded/Nodes/EValueNode.h
                src/BrytecConfigEmbedded/Usb/UsbDefs.cpp
                src/BrytecConfigEmbedded/Usb/UsbDefs.h                
                src/BrytecConfigEmbedded/Usb/ModuleCommand.cpp
                src/BrytecConfigEmbedded/Usb/ModuleCommand.h
                src/BrytecConfigEmbedded/Utils/ENodeConnection.h
                src/BrytecConfigEmbedded/Utils/ENodeDeserializer.cpp
                src/BrytecConfigEmbedded/Utils/ENodeDeserializer.h
                src/BrytecConfigEmbedded/Utils/ENodeGroup.cpp
                src/BrytecConfigEmbedded/Utils/ENodeGroup.h
                src/BrytecConfigEmbedded/Utils/ENodesVector.h
                src/BrytecConfigEmbedded/EBrytecApp.cpp
                src/BrytecConfigEmbedded/EBrytecApp.h
                src/BrytecConfigEmbedded/ENode.cpp
                src/BrytecConfigEmbedded/ENode.h
                src/BrytecConfigEmbedded/IOTypes.cpp
                src/BrytecConfigEmbedded/IOTypes.h
                src/data/communication/ConnectionHandler.cpp
                src/data/communication/ConnectionHandler.h
                src/data/communication/Server.cpp
                src/data/communication/Server.h
                src/data/RaspberryPiScreenBoard.cpp
                src/data/DataThread.cpp
                src/data/DataThread.h
                src/data/screenboarddefs.h
                src/data/screeninternaldefs.h
                src/gui/components/BarGauge.cpp
                src/gui/components/BarGauge.h
                src/gui/components/SmallGauge.cpp
                src/gui/components/SmallGauge.h
                src/gui/windows/CenterWindow.cpp
                src/gui/windows/CenterWindow.h
                src/gui/windows/GaugeWindow.cpp
                src/gui/windows/GaugeWindow.h
                src/gui/Utils.cpp
                src/gui/Utils.h
                src/main.cpp
                )

add_subdirectory(vendor/raylib_multi_window_experimental)
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/asio)

target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_include_directories(${PROJECT_NAME} PUBLIC "src/BrytecConfigEmbedded")

# Common linked libraries
target_link_libraries(${PROJECT_NAME} PUBLIC 
                        raylib
                        fmt::fmt
                        asio
                        )

# ///////////////////////////////
if (UNIX)

target_include_directories(${PROJECT_NAME} PUBLIC "/usr/include/opencv4")

target_link_libraries(${PROJECT_NAME} PRIVATE 
                        SDL2
                        GLESv2
                        EGL
                        pthread
                        rt
                        m
                        gbm
                        drm
                        dl
                        opencv_core
                        opencv_videoio
                        )

endif (UNIX)
# ///////////////////////////////

# ///////////////////////////////
if (WIN32)

add_compile_definitions(PC_BUILD)

endif (WIN32)
# ///////////////////////////////