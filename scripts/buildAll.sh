#!/bin/bash

set -e

pushd ..

#first build vendor code
./scripts/vendorCodeBuild.sh

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
