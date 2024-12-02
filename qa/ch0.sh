#!/bin/bash

NAME=cub3D
ERR_FILE=/tmp/error.log

ERROR_INVALID_ARGS="Error
Invalid arguments"
ERROR_FILE_EXT="Error
Invalid file extension"
ERROR_FILE_OPEN="Error
Could not open file"
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

# 1. Clean and Build the project
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

# 5.1 Invalid texture path
echo "5a. Invalid texture path"
./$NAME asset/map/misconfig/08c-invalid_texture.cub 2> $ERR_FILE
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

# 5.2 Null texture path
echo "5b. Null texture path"
./$NAME asset/map/misconfig/08d-null_texture.cub 2> $ERR_FILE
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

# 6a. Invalid color format
echo "6a. Invalid color format"
./$NAME asset/map/misconfig/09-wrong_color_content.cub 2> $ERR_FILE
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

# 6b. Invalid color format
echo "6b. Null color field"
./$NAME asset/map/misconfig/09b-null_color_field.cub 2> $ERR_FILE
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
