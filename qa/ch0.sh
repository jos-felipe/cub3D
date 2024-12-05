#!/bin/bash

NAME=cub3D
ERR_FILE=$(mktemp /tmp/error.XXXXXX.log)

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
ERROR_INVALID_IDENTIFIER="Error
Invalid identifier"
ERROR_UNDEFINED_ERROR="Error
Undefined error"

# 0. Change to root directory
cd ../

# 1. Build the project
make
if [ $? -ne 0 ]; then
	echo "Build failed"
	exit 1
fi

# 2. Test Arena
printf "Chapter 0: Scene Description File\n\n" 

printf "A1. Few arguments: "
./$NAME 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_ARGS ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_ARGS"
	exit 1
else
    printf "OK\n"
fi

printf "A2. Too many arguments: "
./$NAME a b 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_ARGS ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_ARGS"
	exit 1
else
	printf "OK\n"
fi

printf "\nB1. Invalid file extension: "
./$NAME map.exe 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_FILE_EXT ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_FILE_EXT"
	exit 1
else
	printf "OK\n"
fi

printf "B2. Invalid file path: "
./$NAME .cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_FILE_EXT ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_FILE_EXT"
	exit 1
else
	printf "OK\n"
fi

printf "\nC1. Error file open: "
./$NAME inexistent.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_FILE_OPEN ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_FILE_OPEN"
	exit 1
else
	printf "OK\n"
fi

printf "\nD1. Empty file: "
./$NAME asset/map/misconfig/d1_empty_file.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_IDENTIFIER ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_IDENTIFIER"
	exit 1
else
	printf "OK\n"
fi

printf "D2. Only new line: "
./$NAME asset/map/misconfig/d2_only_new_line.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_UNDEFINED_ERROR ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_UNDEFINED_ERROR"
	exit 1
else
	printf "OK\n"
fi

printf "D3. Invalid identifier: "
./$NAME asset/map/misconfig/d3_invalid_identifier.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_IDENTIFIER ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_IDENTIFIER"
	exit 1
else
	printf "OK\n"
fi

printf "\nE1. Invalid texture: "
./$NAME asset/map/misconfig/e1_invalid_texture.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_TEXTURE ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_TEXTURE"
	exit 1
else
	printf "OK\n"
fi

printf "E2. Null texture: "
./$NAME asset/map/misconfig/e2_null_texture.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_TEXTURE ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_TEXTURE"
	exit 1
else
	printf "OK\n"
fi

printf "E3. Inexistent texture: "
./$NAME asset/map/misconfig/e3_inexistent_texture.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_TEXTURE ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_TEXTURE"
	exit 1
else
	printf "OK\n"
fi

printf "\nF1. Null color: "
./$NAME asset/map/misconfig/f1_null_color.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_COLOR ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_COLOR"
	exit 1
else
	printf "OK\n"
fi

printf "F2. Invalid color: "
./$NAME asset/map/misconfig/f2_invalid_color.cub 2> $ERR_FILE
ERR=$(cat $ERR_FILE)
if [[ $ERR != $ERROR_INVALID_COLOR ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_COLOR"
	exit 1
else
	printf "OK\n"
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
