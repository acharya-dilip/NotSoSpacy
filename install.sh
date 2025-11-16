#!/bin/bash

#Installing dependencies
sudo pacman -S base-devel
sudo pacman -S cmake
sudo pacman -S gtk
sudo pacman -S gstreamer

#Some BS
echo "Yello You're prolly not gonna get hacked but let's find out!!"

#Building the actual C Program or complin it ig
cd build
cmake ..
cmake --build .