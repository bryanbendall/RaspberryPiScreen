#!/bin/bash

pkgs=(git build-essential cmake libsdl2-dev libopencv-dev)
sudo apt-get -y --ignore-missing install "${pkgs[@]}" 

git clone --recursive https://github.com/bryanbendall/RaspberryPiScreen.git