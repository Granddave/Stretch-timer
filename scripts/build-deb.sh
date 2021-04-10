#!/usr/bin/env bash

set -e

cd "$(dirname "$0")/.."

BUILD_DIR="build-deb"

rm -rf $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
cmake --build . --target package -j 4
