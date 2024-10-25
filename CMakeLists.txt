cmake_minimum_required(VERSION 3.10)

project(RaspberryPiScreen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SUPPORT_FILEFORMAT_SVG ON)

add_executable(${PROJECT_NAME}
                src/main.cpp
                src/gui/CenterWindow.cpp
                src/gui/CenterWindow.h
                src/gui/GaugeWindow.cpp
                src/gui/GaugeWindow.h
                )

add_subdirectory(vendor/raylib_multi_window_experimental)

# ///////////////////////////////
if (WIN32)

add_compile_definitions(PC_BUILD)

target_link_libraries(${PROJECT_NAME} PUBLIC 
                        raylib
                        )

endif (WIN32)
# ///////////////////////////////

# ///////////////////////////////
if (UNIX)

set(PLATFORM SDL)
set(OPENGL_VERSION "ES 2.0")

target_include_directories(${PROJECT_NAME} PUBLIC "/usr/include/opencv4")

target_link_libraries(${PROJECT_NAME} PRIVATE 
                        SDL2
                        raylib
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