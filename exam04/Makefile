# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mli <mli@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/11 12:06:29 by mli               #+#    #+#              #
#    Updated: 2020/09/29 12:22:41 by mli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

CC = gcc
CFLAGS = -Wall -Wextra -Werror

ifeq ($(f), f)
	CFLAGS += -fsanitize=address -g3
endif

SRCS_FILES = main.c getters.c

HEADER_FILES = microshell.h

OBJS_PATH = ./obj/
OBJS = ${addprefix ${OBJS_PATH}, ${SRCS_FILES:.c=.o}}

all: ${NAME}

$(NAME): ${OBJS_PATH} ${OBJS} ${HEADER_FILES}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

${OBJS_PATH}:
	@mkdir -p $@

${OBJS_PATH}%.o: %.c ${HEADER_FILES}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf ${OBJS_PATH}

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
