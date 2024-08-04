#!/usr/bin/env bash
echo "Updating Bullseye"
echo "Hold on ..."

cd ~/BLEtarget/sw/Bullseye

git pull

echo "Building the application"

mkdir -p build

cd build
cmake ..
make
