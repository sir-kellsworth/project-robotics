#!/bin/bash

pushd build

make && make upload-RoboticArm SERIAL_PORT=/dev/ttyACM0

popd
