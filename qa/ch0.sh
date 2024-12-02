#!/bin/bash

NAME=cub3D
ERR_FILE=/tmp/error.log

ERROR_INVALID_ARGS="Error
Invalid arguments. Try: ./cub3D with a map in format *.cub"
ERROR_FILE_EXT="Error\nInvalid file extension. Must be .cub\n"
ERROR_FILE_OPEN="Error\nCould not open the file\n"
ERROR_INVALID_MAP="Error\nMap is not properly closed by walls\n"
ERROR_INVALID_TEXTURE="Error\nInvalid texture path\n"
ERROR_INVALID_COLOR="Error\nInvalid color format\n"
ERROR_INVALID_PLAYER="Error\nInvalid player position or multiple players\n"
ERROR_MAP_CHARS="Error\nInvalid characters in map\n"

# 0. Change to root directory
cd ../

# 1. Build the project
make

echo "1. No arguments"
./$NAME 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_ARGS ]]; then
	echo "KO"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_ARGS"
	exit 1
else
	echo "OK"
fi

exit 0
