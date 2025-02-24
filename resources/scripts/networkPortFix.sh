#!/bin/bash

# Use this command to be able to use port 80 after binary is built
sudo setcap 'cap_net_bind_service=+ep' /home/pi/RaspberryPiScreen/build/RaspberryPiScreen