#!/bin/bash
# build_all.sh - builds SegLinux_Shell and all standalone commands

set -e  # exit if any command fails

echo "Building SegLinux_Shell core..."
make  # runs root Makefile

echo "Building standalone commands..."
(cd src/commands/standalone && make && make install)

echo "Build complete!"
