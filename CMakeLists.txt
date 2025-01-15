cmake_minimum_required(VERSION 3.10)

project(RaspberryPiScreen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (UNIX)
    set(PLATFORM SDL)
    set(OPENGL_VERSION "ES 2.0")
endif (UNIX)

add_executable(${PROJECT_NAME}
                src/data/communication/can/CanConnectionHandler.cpp
                src/data/communication/can/CanConnectionHandler.h
                src/data/communication/can/CanManager.cpp
                src/data/communication/can/CanManager.h
                src/data/communication/http/HttpConnectionHandler.cpp
                src/data/communication/http/HttpConnectionHandler.h
                src/data/communication/http/HttpServer.cpp
                src/data/communication/http/HttpServer.h
                src/data/communication/wifi/ConnectionHandler.cpp
                src/data/communication/wifi/ConnectionHandler.h
                src/data/communication/wifi/Server.cpp
                src/data/communication/wifi/Server.h
                src/data/DataThread.cpp
                src/data/DataThread.h
                src/data/GlobalInputs.h
                src/data/GlobalOutputs.h
                src/data/RaspberryPiScreenBoard.cpp
                src/data/screenboardrev2defs.h
                src/gui/Assets/AssetManager.cpp
                src/gui/Assets/AssetManager.h
                src/gui/Assets/Asset.h
                src/gui/components/RemoteCamera.cpp
                src/gui/components/RemoteCamera.h
                src/gui/components/UiComponents.cpp
                src/gui/components/UiComponents.h
                src/gui/input/TouchInput.cpp
                src/gui/input/TouchInput.h
                src/gui/panels/Panel.h
                src/gui/panels/GaugeWindow/EgtPanel.cpp
                src/gui/panels/GaugeWindow/EgtPanel.h
                src/gui/panels/GaugeWindow/RightMainPanel.cpp
                src/gui/panels/GaugeWindow/RightMainPanel.h
                src/gui/panels/GaugeWindow/RightMapPanel.cpp
                src/gui/panels/GaugeWindow/RightMapPanel.h
                src/gui/windows/CenterWindow.cpp
                src/gui/windows/CenterWindow.h
                src/gui/windows/GaugeWindow.cpp
                src/gui/windows/GaugeWindow.h
                src/gui/Utils.cpp
                src/gui/Utils.h
                src/main.cpp
                )

set(BrytecCustomConfigDir ${CMAKE_CURRENT_SOURCE_DIR}/src/data)
message(${CMAKE_CURRENT_SOURCE_DIR}/src/data)
add_subdirectory(src/BrytecConfigEmbedded)
add_subdirectory(vendor/raylib_multi_window_experimental)
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/asio)

target_include_directories(${PROJECT_NAME} PUBLIC "src")

# Common linked libraries
target_link_libraries(${PROJECT_NAME} PUBLIC 
                        raylib
                        fmt::fmt
                        asio
                        BrytecConfigEmbedded
                        )

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
                            opencv_imgproc
                            )
endif (UNIX)

if (WIN32)
    add_compile_definitions(PC_BUILD)
    set(openCvPath "C:/opencv")
    target_include_directories(${PROJECT_NAME} PUBLIC ${openCvPath}/build/include)
    target_link_directories(${PROJECT_NAME} PUBLIC ${openCvPath}/build/x64/vc16/lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE
                            opencv_world4100d.lib
                            )
endif (WIN32)