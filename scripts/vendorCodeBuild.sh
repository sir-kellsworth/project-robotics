#!/bin/bash

git submodule sync
git submodule update --init --recursive

VENDOR_DIR="$(dirname $(readlink -f $0))/../vendor"
pushd $VENDOR_DIR

#now build vendor code
mkdir -p libfixmath/build
mkdir -p libfixmath/lib
mkdir -p libfixmath/api
mkdir -p libfixmath/api/fixmath
pushd libfixmath/build

cmake ../source/
make
cp liblibfixmath.a ../lib/
cp ../source/libfixmath/* ../api/

popd

popd
