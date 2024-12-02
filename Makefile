# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josfelip <josfelip@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 12:34:41 by josfelip          #+#    #+#              #
#    Updated: 2024/12/02 05:39:52 by josfelip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME = cub3D

# Target executable
NAME = ${PROJECT_NAME}
ARGS = maze.cub

# Compiler directives
CC = cc
CFLAGS = -Wall -Wextra -Werror
DFLAGS = -g3

# Directory structure
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include
LIBFT_DIR	= lib/libft

# Binaries for debugging purposes
ifdef WITH_DEBUG
  NAME = ${PROJECT_NAME}_debug
  CFLAGS = ${DFLAGS}
  OBJ_DIR = obj_debug
endif

# Source files by component
SRC_MAIN	=	main.c
SRC_CH0		=	ch0/a0_parse_scene.c \
				ch0/a1_check_file_extension.c \
		  		ch0/a2_parse_decorators.c \
		  		ch0/a3_parse_map.c \
		  		ch0/a4_validate_map.c \
				ch0/a9_safe_exit.c

# Combine all sources with their paths
SRC	=	$(addprefix $(SRC_DIR)/, $(SRC_MAIN)) \
		$(addprefix $(SRC_DIR)/, $(SRC_CH0))

# Generate object file paths, maintaining directory structure
OBJ	=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a

# Include paths
INC	= -I$(INC_DIR) -I$(LIBFT_DIR)

RM = rm -rf

# Default target
all: ${NAME}

# Link the program
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

# Compile libft
$(LIBFT):
	@make -C ${LIBFT_DIR} --no-print-directory
	
# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	
# Clean object files
clean:
	${RM} $(OBJ_DIR)
	${RM} $(OBJ_DIR)_debug
	@make -C $(LIBFT_DIR) clean --no-print-directory

# Clean everything
fclean: clean
	${RM} ${NAME}
	${RM} ${NAME}_debug
	@make -C ${LIBFT_DIR} fclean --no-print-directory

# Rebuild everything
re: fclean all

debug:
	@make WITH_DEBUG=TRUE --no-print-directory

# Check variable values
print:
	@echo "INCLUDE_PATH: ${INCLUDE_PATH}"
	@echo "SRC_PATH: ${SRC_PATH}"
	@echo "OBJ_PATH: ${OBJ_PATH}"


memcheck: all
	@valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./${NAME} ${ARGS}
	@sh qa/mem_check.sh
	
faultcheck: all
	@valgrind -s --track-origins=yes ./${NAME} ${ARGS}

run: all
	./${NAME} ${ARGS}

.PHONY: all libft clean fclean re debug print memcheck faultcheck run


