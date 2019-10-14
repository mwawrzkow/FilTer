#!/bin/bash


sudo apttt-get update
sudo apt-get install cmake libboost-all-dev git

git clone https://github.com/jbeder/yaml-cpp.git yamllib

cd yamllib
mkdir build 
cd build 
cmake .. 
make && sudo make install

