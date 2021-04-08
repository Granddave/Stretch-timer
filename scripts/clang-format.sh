#!/usr/bin/env bash

set -e

cd "$(dirname "$0")/.."

SRC_DIRS="src"
FILES=$(find $SRC_DIRS -type f -regex ".*\.[ch]\(pp\)?$")

clang-format \
    $FILES \
    -i
