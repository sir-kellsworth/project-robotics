#!/bin/bash

mkdir -p build
pushd build

cmake \
  -DUSE_DEBUG=ON \
  -D ARDUINO_INSTALL_PATH=${HOME}/arduino-1.8.19 \
  -D ARDUINO_BOARD_OPTIONS_FILE=BoardOptions.cmake \
  -D CMAKE_TOOLCHAIN_FILE=../../Arduino-CMake-Toolchain/Arduino-toolchain.cmake \
  ..
make -j $(nproc)

popd
