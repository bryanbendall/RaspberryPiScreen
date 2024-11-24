cmake_minimum_required(VERSION 3.10)

project(RaspberryPiScreen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (UNIX)
    set(PLATFORM SDL)
    set(OPENGL_VERSION "ES 2.0")
endif (UNIX)

add_executable(${PROJECT_NAME}
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
                src/gui/components/BoostGauge.cpp
                src/gui/components/BoostGauge.h
                src/gui/components/RemoteCamera.cpp
                src/gui/components/RemoteCamera.h
                src/gui/components/SmallGauge.cpp
                src/gui/components/SmallGauge.h
                src/gui/components/Speedometer.cpp
                src/gui/components/Speedometer.h
                src/gui/components/TachGauge.cpp
                src/gui/components/TachGauge.h
                src/gui/windows/CenterWindow.cpp
                src/gui/windows/CenterWindow.h
                src/gui/windows/GaugeWindow.cpp
                src/gui/windows/GaugeWindow.h
                src/gui/Utils.cpp
                src/gui/Utils.h
                src/main.cpp
                )

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