#!/bin/bash

set -e

pushd ..

pushd Controller/BuildFiles
./build.sh
popd

pushd Simulator/BuildFiles
./build.sh
popd

pushd Arduino/RoboticArm
./build.sh
popd

popd
