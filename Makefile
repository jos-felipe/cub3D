# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 12:34:41 by josfelip          #+#    #+#              #
#    Updated: 2025/01/02 13:13:17 by josfelip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME = cub3D

# Target executable
NAME = $(PROJECT_NAME)

# Compiler directives
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -g3
LFLAGS	= -ldl -lglfw -pthread -lm

# Directory structure
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include
LIBFT_DIR	= lib/libft
LIBMLX_DIR	= lib/MLX42

# Binaries for debugging purposes
ifdef WITH_DEBUG
  NAME = $(PROJECT_NAME)_debug
  CFLAGS = $(DFLAGS)
  OBJ_DIR = obj_debug
endif

# Source files by component
SRC_MAIN	=	main.c

SRC_CH0		=	ch0/a0_parse_scene.c \
				ch0/a1_check_file_extension.c \
		  		ch0/a2_parse_decorators.c \
		  		ch0/a3_parse_map.c \
		  		ch0/a4_validate_map.c \
				ch0/a9_safe_exit.c \
				ch0/a5_debug_scene.c \

SRC_CH1		=	ch1/a0_init_window.c \
				ch1/a1_game_loop.c \
				ch1/a2_player.c \
				ch1/a3_input.c

# Combine all sources with their paths
SRC	=	$(addprefix $(SRC_DIR)/, $(SRC_MAIN)) \
		$(addprefix $(SRC_DIR)/, $(SRC_CH0))

# Generate object file paths, maintaining directory structure
OBJ	=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Chapter header files
HDR_CH = ch0_scene_description_file.h \
		 ch1_window.h

# Combine all headers with their paths
HDR	= $(addprefix $(INC_DIR)/, $(HDR_CH))

# Libraries
LIBFT	= $(LIBFT_DIR)/libft.a
LIBMLX	= $(LIBMLX_DIR)/build/libmlx42.a

# Include paths
INC	= -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(LIBMLX_DIR)/include

RM = rm -rf

# Default target
all: $(NAME)

# Link the program
$(NAME):  $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) $(OBJ) $(LIBFT) $(LIBMLX) $(LFLAGS) -o $(NAME)

# Compile libft
$(LIBFT):
	@make -sC $(LIBFT_DIR) --no-print-directory

# Compile libmlx
$(LIBMLX):
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build
	@make -sC $(LIBMLX_DIR)/build -j4 --no-print-directory
	
# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	
# Clean object files
clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJ_DIR)_debug

# Clean everything
fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME)_debug
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@if [ -d "$(LIBMLX_DIR)/build" ]; then \
		make -C $(LIBMLX_DIR)/build clean --no-print-directory; \
	fi

# Rebuild everything
re: fclean all

debug:
	@make WITH_DEBUG=TRUE --no-print-directory

.PHONY: all clean fclean re debug


