cmake_minimum_required(VERSION 3.10)

project(RaspberryPiScreen)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CUSTOMIZE_BUILD ON)
# set(SUPPORT_FILEFORMAT_SVG ON)

# ///////////////////////////////
if (UNIX)

set(PLATFORM SDL)
set(OPENGL_VERSION "ES 2.0")

endif (UNIX)
# ///////////////////////////////

add_executable(${PROJECT_NAME}
                src/main.cpp
                src/gui/windows/CenterWindow.cpp
                src/gui/windows/CenterWindow.h
                src/gui/windows/GaugeWindow.cpp
                src/gui/windows/GaugeWindow.h
                src/gui/components/BarGauge.cpp
                src/gui/components/BarGauge.h
                src/gui/components/SmallGauge.cpp
                src/gui/components/SmallGauge.h
                src/utils/OpenGlStencil.cpp
                src/utils/OpenGlStencil.h
                )

add_subdirectory(vendor/raylib_multi_window_experimental)

target_include_directories(${PROJECT_NAME} PUBLIC "src")

# ///////////////////////////////
if (UNIX)

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

# ///////////////////////////////
if (WIN32)

add_compile_definitions(PC_BUILD)

target_link_libraries(${PROJECT_NAME} PUBLIC 
                        raylib
                        )

endif (WIN32)
# ///////////////////////////////