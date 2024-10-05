# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: recherra <recherra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 17:42:36 by recherra          #+#    #+#              #
#    Updated: 2024/10/05 17:42:48 by recherra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FRAMEWORKS=-lmlx -framework OpenGL -framework AppKit
FLAGS=-Wall -Wextra -fsanitize=address -g
SRC=map.c cube.c
OBJS=${SRC:.c=.o}
LIBFT=libft/libft.a
NAME=three_dee

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS} cubed.h
	cc ${OBJS} -o ${NAME} ${FLAGS} ${LIBFT} ${FRAMEWORKS}

${LIBFT}:
	make -C libft/

clean:
	make -C libft/ clean
	rm -rf ${OBJS}

fclean: clean
	make -C libft/ fclean
	rm ${NAME}

re: fclean all
