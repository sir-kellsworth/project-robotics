#!/bin/bash

mkdir build
pushd build

cmake ..
make -j16

popd
