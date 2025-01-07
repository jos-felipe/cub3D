# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ch1.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 08:32:16 by josfelip          #+#    #+#              #
#    Updated: 2025/01/07 09:32:29 by josfelip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

printf "\n\nChapter 1: Window Management - CI & Leaks\n\n" 

NAME="cub3D"

# Add debug information about environment
echo "Debug Info:"
echo "DISPLAY=$DISPLAY"
echo "XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR"
echo "XAUTHORITY=$XAUTHORITY"
echo "Running in CI: ${CI:-false}"

ERR_FILE=$(mktemp /tmp/$NAME.XXXXXX) || {
    echo "Failed to create temporary file"
    exit 1
}
if [ ! -w ""$ERR_FILE"" ]; then
    echo "Temporary file is not writable"
    exit 1
fi

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
check_command xvfb-run

# Check executable
make
if [ $? -ne 0 ]; then
	echo "Build failed"
	exit 1
fi

# Export required environment variables for X11
export DISPLAY=:99
export XAUTHORITY=/tmp/.Xauthority
export XDG_RUNTIME_DIR=/tmp/runtime-runner

# Run valgrind with Xvfb if in CI, otherwise run normally
if [ -n "$CI" ]; then
	xvfb-run -a -s "-screen 0 1280x1024x24" valgrind --leak-check=full \
					  --show-leak-kinds=all \
					  --track-origins=yes \
					  --suppressions=./mlx42.supp \
					  --log-file=valgrind_report.txt \
					  ./cub3D asset/map/minimalist_map.cub 2> "$ERR_FILE" &
else
	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --suppressions=./mlx42.supp \
			 --log-file=valgrind_report.txt \
			 ./cub3D asset/map/minimalist_map.cub 2> "$ERR_FILE" &
fi

VALGRIND_PID=$!
echo "Program started with PID: $VALGRIND_PID"

# Wait for window to appear
window_name="cub3D"
timeout=30
elapsed=0
window_id=""

echo "Waiting for window to appear..."
while [ -z "$window_id" ] && [ $elapsed -lt $timeout ]; do
    window_id=$(xdotool search --name "^${window_name}$" 2>/dev/null)
    if [ -z "$window_id" ]; then
         echo "Attempt $elapsed: Window not found yet..."
        # Check if process is still running
        if ! kill -0 $VALGRIND_PID 2>/dev/null; then
            echo "Error: Process died before window appeared"
            cat "$ERR_FILE"
            exit 1
        fi
		sleep 1
        ((elapsed++))
    fi
done

if [ -z "$window_id" ]; then
    echo "Error: Window not found after $timeout seconds"
    echo "Process status:"
    ps aux | grep $VALGRIND_PID
    echo "Error output:"
    cat "$ERR_FILE"
    kill $VALGRIND_PID 2>/dev/null
    exit 1
fi

# Send ESC key to close window
echo "Window found (ID: $window_id)! Sending ESC key..."
if [ -n "$CI" ]; then
    # Alternative way to close window in CI environment
    kill -SIGTERM $VALGRIND_PID
else
    xdotool windowactivate --sync "$window_id"
    sleep 1
    xdotool key --window "$window_id" Escape
fi

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

# Cleanup
rm -f "$ERR_FILE"
rm -f valgrind_report.txt

# Kill Xvfb if we're in CI environment
if [ -n "$CI" ]; then
	killall Xvfb
fi

echo "Test completed!"

exit 0