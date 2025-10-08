#!/bin/bash
set -e  # Exit on error

# Default build type is Release
BUILD_TYPE="Release"

# If user passes -d, switch to Debug
if [ "$1" == "-d" ]; then
    BUILD_TYPE="Debug"
fi

# Create build directory if missing
mkdir -p build
cd build

# Configure CMake
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

# Build
cmake --build .

# Run program if executable exists
if [ -f "./Nxplore" ]; then
    echo "Running program..."
    ./Nxplore
fi
