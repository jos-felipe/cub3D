#!/bin/bash

# Chapter 1: Window Management

NAME="cub3D"

ERR_FILE=$(mktemp /tmp/$NAME.XXXXXX) || {
    echo "Failed to create temporary file"
    exit 1
}
if [ ! -w ""$ERR_FILE"" ]; then
    echo "Temporary file is not writable"
    exit 1
fi

# 1. Build the project
make
if [ $? -ne 0 ]; then
	echo "Build failed"
	exit 1
fi

# 2. Test Arena
printf "\n\nChapter 1: Window Management\n\n" 

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
./$NAME asset/map/minimalist_map.cub 2> "$ERR_FILE" &

# Store the program's PID
cub3d_pid=$!

echo "Waiting for window to appear..."
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

ERR=$(cat "$ERR_FILE")
if [[ $ERR != "" ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo ""
	exit 1
else
	printf "OK\n"
fi

rm -f "$ERR_FILE"

echo "Test completed!"

exit 0
