# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josfelip <josfelip@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 12:34:41 by josfelip          #+#    #+#              #
#    Updated: 2024/07/01 09:24:55 by josfelip         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

INCLUDE_DIR = ./include/
INCLUDE = libft.h get_next_line_bonus.h
INCLUDE_PATH = $(addprefix $(INCLUDE_DIR), $(INCLUDE))

SRC_DIR = ./src/
SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_trashman.c get_next_line_bonus.c get_next_line_utils_bonus.c
SRC_PATH = $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR = ./obj/
OBJ_PATH = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf

all: ${OBJ_DIR} ${NAME}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o: ${SRC_DIR}%.c ${INCLUDE_PATH}
	${CC} ${CFLAGS} -I${INCLUDE_DIR} -c $< -o $@
	ar rc ${NAME} $@

${NAME}: ${OBJ_PATH}
	ar rc ${NAME} ${OBJ_PATH}

clean:
	${RM} ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re


