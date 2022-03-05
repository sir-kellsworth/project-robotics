#!/bin/bash

git submodule sync
git submodule update --init --recursive

VENDOR_DIR="$(dirname $(readlink -f $0))/../vendor"
pushd $VENDOR_DIR

#now build vendor code
mkdir -p libfixmath/build
mkdir -p libfixmath/lib
pushd libfixmath/build

cmake ..
make
mv liblibfixmath.a ../lib/

popd

popd
