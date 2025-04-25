#!/bin/bash

# Use default cmake if not set
if [ -z "$CMAKE_BIN" ]; then
    export CMAKE_BIN=cmake
fi

# Show CMake version
$CMAKE_BIN --version

if [ -d "build" ]; then
    echo "Removing existing build/ directory..."
    rm -rf build
fi

if [ -d "bin" ]; then
    echo "Removing existing bin/ directory..."
    rm -rf bin
fi

mkdir build
cd build

$CMAKE_BIN .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -G"Unix Makefiles"
    -DCMAKE_INSTALL_PREFIX=../bin \
