echo "Updating Bullseye"
echo "Hold on ..."

cd ~/BLEtarget/sw/Bullseye

git pull
echo "Building the application"
if [[ -e ./build ]]; then
    rm -rf build
fi

mkdir build
cd build
cmake ..
make
