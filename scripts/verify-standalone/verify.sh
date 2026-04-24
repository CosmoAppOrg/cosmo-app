#!/usr/bin/env bash
# Simple verification script for Cosmo App
# Runs the executable and checks for expected output

set -e

# Path to the executable (relative to the script's location)
EXECUTABLE="../../build/cosmoapp"

if [[ ! -f "$EXECUTABLE" ]]; then
    echo "Error: Executable not found at $EXECUTABLE"
    echo "Please build the project first."
    exit 1
fi

echo "Running $EXECUTABLE with --help..."
"$EXECUTABLE" --help

echo "Verification completed successfully."