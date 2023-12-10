#!/bin/env bash

# export CC=gcc
# export CXX=g++

mkdir -p build && cd build
conan install .. --output-folder=. --build=missing --profile=default
cmake ..  -DCMAKE_BUILD_TYPE=Debug  -DCMAKE_C_COMPILER=${CC} -DCMAKE_CXX_COMPILER=${CXX} --preset conan-debug
 # -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake

cmake --build .
