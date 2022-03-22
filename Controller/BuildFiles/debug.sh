#!/bin/bash

mkdir build
pushd build

cmake -DUSE_DEBUG=ON ..
make -j${nproc}

popd
