#!/bin/bash

# Chapter 0: Scene Description File

NAME=cub3D

ERR_FILE=$(mktemp /tmp/$NAME.XXXXXX) || {
    echo "Failed to create temporary file"
    exit 1
}
if [ ! -w ""$ERR_FILE"" ]; then
    echo "Temporary file is not writable"
    exit 1
fi

ERROR_INVALID_ARGS="Error
Invalid arguments"
ERROR_FILE_EXT="Error
Invalid file extension"
ERROR_FILE_OPEN="Error
Could not open file"
ERROR_INVALID_MAP="Error
Invalid map format"
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
printf "\n\nChapter 0: Scene Description File\n\n" 

printf "A1. Few arguments: "
./$NAME 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME a b 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME map.exe 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME .cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME inexistent.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME asset/map/misconfig/d1_empty_file.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME asset/map/misconfig/d2_only_new_line.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME asset/map/misconfig/d3_invalid_identifier.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME asset/map/misconfig/e1_invalid_texture.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME asset/map/misconfig/e2_null_texture.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME asset/map/misconfig/e3_inexistent_texture.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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

printf "E4. Multiple textures: "
./$NAME asset/map/misconfig/e4_texture_multiple.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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

printf "\nF1. Null color: "
./$NAME asset/map/misconfig/f1_null_color.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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
./$NAME asset/map/misconfig/f2_invalid_color.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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

printf "F3. Multiple colors: "
./$NAME asset/map/misconfig/f3_color_multiple.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
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

printf "\nG1. Invalid map format: "
./$NAME asset/map/misconfig/g1_map_invalid_format.cub 2> "$ERR_FILE"
ERR=$(cat "$ERR_FILE")
if [[ $ERR != $ERROR_INVALID_MAP ]]; then
	printf "KO\n"
	echo "Actual:"
	echo "$ERR"
	echo "Expected:"
	echo "$ERROR_INVALID_MAP"
	exit 1
else
	printf "OK\n"
fi

printf "G2. Valid minimalist map: "
./$NAME asset/map/g2_map_minimalist.cub 2> "$ERR_FILE"
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

exit 0
