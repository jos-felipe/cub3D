# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 12:34:41 by josfelip          #+#    #+#              #
#    Updated: 2024/11/28 11:15:17 by josfelip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_NAME = cub3D

# Target executable
NAME = ${PROJECT_NAME}
ARGS =

# Compiler directives
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Binaries for debugging purposes
DFLAGS = -g3
ifdef WITH_DEBUG
  NAME = ${PROJECT_NAME}_debug
  CFLAGS = ${DFLAGS}
endif

# Header files
INCLUDE_DIR = include
INCLUDE_PATH = ${wildcard $(INCLUDE_DIR)/*.h}
INCLUDE = ${notdir $(INCLUDE_PATH)}

# Source files
SRC_DIR = src
SRC_PATH = ${wildcard $(SRC_DIR)/*.c}
SRC = ${notdir $(SRC_PATH)}

# Object files
OBJ_DIR = obj
ifdef WITH_DEBUG
  OBJ_DIR = obj_debug
endif
OBJ_PATH = ${addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o)}

LIBFT_DIR = lib/libft
LIBFT = libft.a
LIBFT_PATH = ${addprefix $(LIBFT_DIR), $(LIBFT)}

RM = rm -rf

# Default target
all: libft ${OBJ_DIR} ${NAME}

libft:
	@make -C ${LIBFT_DIR} --no-print-directory

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

# Compile source files into object files
${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${INCLUDE_PATH}
	${CC} ${CFLAGS} -I${INCLUDE_DIR} -c $< -o $@

# Compile main.c into main.o
$(OBJ_DIR)/main.o: main.c ${INCLUDE_PATH}
	${CC} ${CFLAGS} -I${INCLUDE_DIR} -c $< -o $@

# Link the executable
${NAME}: ${OBJ_PATH} $(OBJ_DIR)/main.o
	${CC} ${CFLAGS} -o ${NAME} ${OBJ_PATH} $(OBJ_DIR)/main.o -L $(LIBFT_DIR) -lft

# Clean object files
clean:
	${RM} ${OBJ_DIR}
	${RM} ${OBJ_DIR}_debug

# Clean executable, object files and library binaries
fclean: clean
	${RM} ${NAME}
	${RM} ${NAME}_debug
	@make fclean -C ${LIBFT_DIR} --no-print-directory

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


