#!/bin/bash

# Chapter 0: Scene Description File - Leaks

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
printf "\n\nChapter 0: Scene Description File - Leaks\n\n" 

printf "A1. Few arguments: "
$LEAKS $LFLAGS ./$NAME 2>/dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "A2. Too many arguments: "
$LEAKS $LFLAGS ./$NAME a b 2>/dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "\nB1. Invalid file extension: "
$LEAKS $LFLAGS ./$NAME map.exe 2>/dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "B2. Invalid file path: "
$LEAKS $LFLAGS ./$NAME .cub 2>/dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "\nC1. Error file open: "
$LEAKS $LFLAGS ./$NAME inexistent.cub 2>/dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "\nD1. Empty file: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/d1_empty_file.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "D2. Only new line: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/d2_only_new_line.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "D3. Invalid identifier: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/d3_invalid_identifier.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "\nE1. Invalid texture: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/e1_invalid_texture.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "E2. Null texture: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/e2_null_texture.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "E3. Inexistent texture: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/e3_inexistent_texture.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "E4. Multiple textures: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/e4_texture_multiple.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "\nF1. Null color: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/f1_null_color.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "F2. Invalid color: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/f2_invalid_color.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "F3. Multiple colors: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/f3_color_multiple.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "\nG1. Invalid map format: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/g1_map_invalid_format.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "\nH1. No player: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/h1_player_zero.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

printf "H2. Multiple players: "
$LEAKS $LFLAGS ./$NAME asset/map/misconfig/h2_player_multiple.cub &> /dev/null
LOG=$(cat "$LOG_FILE")
if [[ "$LOG" ]]; then
	printf "MKO\n"
	echo "$LOG"
	exit 1
else
    printf "MOK\n"
fi

rm -f "$LOG_FILE"

exit 0
