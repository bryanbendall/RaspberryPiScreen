#!/bin/bash

sudo apt-get update
pkgs=(git build-essential cmake libopencv-dev libdrm-dev libudev-dev libasound2-dev libdbus-1-dev libglfw3-dev libgles2-mesa-dev libgbm-dev libraspberrypi-bin libraspberrypi-dev)
sudo apt-get -y --ignore-missing install "${pkgs[@]}" 

git clone https://github.com/libsdl-org/SDL.git -b release-2.30.x
cd SDL
mkdir build
cd build
../configure --enable-video-kmsdrm --disable-video-x11
make
sudo make install
cd ../../

git clone --recursive https://github.com/bryanbendall/RaspberryPiScreen.git
