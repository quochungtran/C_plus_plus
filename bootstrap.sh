#!/bin/bash


if [ -z "$CMAKE_BIN" ]; then
    export CMAKE_BIN=cmake
fi

$CMAKE_BIN --version


rm -rf build
mkdir build
cd build


$CMAKE_BIN . \
      -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
      -DCMAKE_INSTALL_PREFIX=../bin \
      -G"Unix Makefiles" \
      ..