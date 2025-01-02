#!/bin/bash

# Chapter 1: Window Management - Leaks

NAME="cub3D"

LOG_FILE=$(mktemp /tmp/$LEAKS.XXXXXX) || {
    echo "Failed to create temporary file"
    exit 1
}
if [ ! -w ""$LOG_FILE"" ]; then
    echo "Temporary file is not writable"
    exit 1
fi

LEAKS="valgrind"
LFLAGS="--leak-check=full --show-leak-kinds=all --track-origins=yes --quiet --log-file=$LOG_FILE"

# 1. Build the project
make
if [ $? -ne 0 ]; then
	echo "Build failed"
	exit 1
fi

# 2. Test Arena
printf "\n\nChapter 1: Window Management - Leaks\n\n" 

printf "\nA1. Valid minimalist map: "

# Function to check if a command exists
check_command() {
    if ! command -v "$1" &> /dev/null; then
        echo "Error: $1 is not installed. Installing..."
        sudo apt-get update && sudo apt-get install -y "$1"
    fi
}

# Check if xdotool is installed
check_command xdotool

# Wait for the window to appear (adjust timeout if needed)
timeout=5
window_name="cub3D"

echo "Launching cub3D..."
# Launch your program in the background
$LEAKS $LFLAGS ./$NAME asset/map/minimalist_map.cub 2>/dev/null &

# Store the program's PID
cub3d_pid=$!

echo "Waiting for window to appear..."
sleep 10
window_id=""
elapsed=0

while [ -z "$window_id" ] && [ $elapsed -lt $timeout ]; do
    window_id=$(xdotool search --name "$window_name" 2>/dev/null)
    if [ -z "$window_id" ]; then
        sleep 1
        ((elapsed++))
    fi
done

if [ -z "$window_id" ]; then
    echo "Error: Window not found after $timeout seconds"
    kill $cub3d_pid 2>/dev/null
    exit 1
fi

echo "Window found! Sending ESC key..."
# Activate the window and send ESC key
xdotool windowactivate "$window_id"
sleep 1  # Wait a bit for window to activate
xdotool key Escape

# Wait for program to exit
wait $cub3d_pid

LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

rm -f "$LOG_FILE"

echo "Test completed!"

exit 0
