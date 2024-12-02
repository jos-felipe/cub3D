#!/bin/bash

NAME=cub3D
ERR_FILE=/tmp/error.log

ERROR_INVALID_ARGS="Error
Invalid arguments. Try: ./cub3D with a map in format *.cub"
ERROR_FILE_EXT="Error
Invalid file extension. Must be .cub"
ERROR_FILE_OPEN="Error
Could not open the file"
ERROR_INVALID_MAP="Error
Map is not properly closed by walls"
ERROR_INVALID_TEXTURE="Error
Invalid texture path"
ERROR_INVALID_COLOR="Error
Invalid color format"
ERROR_INVALID_PLAYER="Error
Invalid player position or multiple players"
ERROR_MAP_CHARS="Error
Invalid characters in map"

# 0. Change to root directory
cd ../

# 1. Build the project
make clean && make

# 2. Test Area

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

echo "2. Invalid file extension"
./$NAME asset/map/misconfig/02-wrong_file_ext.cbb 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_FILE_EXT ]]; then
    echo "KO"
    echo "Actual:"
    echo "$ERR"
    echo "Expected:"
    echo "$ERROR_FILE_EXT"
    exit 1
else
    echo "OK"
fi

# 3. File open error
echo "3. File open error"
./$NAME non_existent_file.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_FILE_OPEN ]]; then
    echo "KO"
    echo "Actual:"
    echo "$ERR"
    echo "Expected:"
    echo "$ERROR_FILE_OPEN"
    exit 1
else
    echo "OK"
fi

# 4. Invalid map format
echo "4. Invalid map format"
./$NAME asset/map/misconfig/05-incomplete_map.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_MAP ]]; then
    echo "KO"
    echo "Actual:"
    echo "$ERR"
    echo "Expected:"
    echo "$ERROR_INVALID_MAP"
    exit 1
else
    echo "OK"
fi

# 5. Invalid texture path
echo "5. Invalid texture path"
./$NAME map_invalid_texture.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_TEXTURE ]]; then
    echo "KO"
    echo "Actual:"
    echo "$ERR"
    echo "Expected:"
    echo "$ERROR_INVALID_TEXTURE"
    exit 1
else
    echo "OK"
fi

# 6. Invalid color format
echo "6. Invalid color format"
./$NAME map_invalid_color.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_COLOR ]]; then
    echo "KO"
    echo "Actual:"
    echo "$ERR"
    echo "Expected:"
    echo "$ERROR_INVALID_COLOR"
    exit 1
else
    echo "OK"
fi

# 7. Invalid player position or multiple players
echo "7. Invalid player position or multiple players"
./$NAME map_invalid_player.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_PLAYER ]]; then
    echo "KO"
    echo "Actual:"
    echo "$ERR"
    echo "Expected:"
    echo "$ERROR_INVALID_PLAYER"
    exit 1
else
    echo "OK"
fi

# 8. Invalid characters in map
echo "8. Invalid characters in map"
./$NAME map_invalid_chars.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_MAP_CHARS ]]; then
    echo "KO"
    echo "Actual:"
    echo "$ERR"
    echo "Expected:"
    echo "$ERROR_MAP_CHARS"
    exit 1
else
    echo "OK"
fi

exit 0

exit 0
