#!/bin/bash

#Installing dependencies
sudo pacman -S base-devel
sudo pacman -S cmake
sudo pacman -S gtk
sudo pacman -S gstreamer

#Building the actual C Program or complin it ig
mkdir build
cd build
cmake ..
cmake --build .