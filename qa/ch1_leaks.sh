#!/bin/bash

# Chapter 1: Window Management - Leaks

printf "\n\nChapter 1: Window Management - Leaks\n\n" 

# Function to check if a command exists
check_command() {
    if ! command -v "$1" &> /dev/null; then
        echo "Error: $1 is not installed. Installing..."
        sudo apt-get update && sudo apt-get install -y "$1"
    fi
}

# Check if required tools are installed
check_command valgrind
check_command xdotool

# Build the project
make
if [ $? -ne 0 ]; then
	echo "Build failed"
	exit 1
fi

# Start valgrind in background
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --suppressions=./mlx42.supp \
         --log-file=valgrind_report.txt \
         ./cub3D asset/map/minimalist_map.cub &

VALGRIND_PID=$!

# Wait for window to appear
window_name="cub3D"
timeout=15
elapsed=0
window_id=""

echo "Waiting for window to appear..."
while [ -z "$window_id" ] && [ $elapsed -lt $timeout ]; do
    window_id=$(xdotool search --name "^${window_name}$" 2>/dev/null)
    if [ -z "$window_id" ]; then
        sleep 1
        ((elapsed++))
    fi
done

if [ -z "$window_id" ]; then
    echo "Error: Window not found after $timeout seconds"
    kill $VALGRIND_PID 2>/dev/null
    exit 1
fi

# Send ESC key to close window
echo "Window found! Sending ESC key..."
xdotool windowactivate "$window_id"
sleep 1
xdotool key Escape

# Wait for valgrind to finish
wait $VALGRIND_PID

# Check if any leaks were found (excluding suppressed ones)
if grep -q "definitely lost: 0 bytes in 0 blocks" valgrind_report.txt; then
    echo "No memory leaks found!"
else
    echo "Memory leaks detected! Check valgrind_report.txt for details."
    echo "Summary of leaks:"
    grep "definitely lost:" valgrind_report.txt
    grep "indirectly lost:" valgrind_report.txt
    grep "possibly lost:" valgrind_report.txt
    grep "still reachable:" valgrind_report.txt
    exit 1
fi

exit 0